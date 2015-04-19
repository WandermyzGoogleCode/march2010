

# 网页安全 #

## javascript ##

> 将恶意代码嵌入到js脚本中是最常用（也是最低级）的网页攻击手段。由于js本身在设计时已经有了很多安全方面的保护，因此用js可以造成的危害并不大（**现在有了AJAXh和HTTPRequest，还仍然是这样吗？待考证**）。理论上讲，JS无法对客户端或服务器端的文件进行直接的读写操作。

> 网页中的js脚本可以在客户端弹出各种消息框，还可以通过执行某些死循环操作搞垮用户的浏览器。目前我能想到的js直接威胁仅此而已。

> ### 防范措施 ###
> 网站开发者通常禁止用户在其网站上发布带有js脚本的内容以防止其给别的用户带来麻烦。简单的实现方法是将html字符转义。例如用户提交的字符串“`<javascript>`”会被转义成“`&lt;javascript&rt;`”，这样浏览器就会把“`<javascript>`”直接显示出来而不是去执行它后面的js代码。PHP中有现成的转义函数htmlspecialchars。

## 外部表格 ##
> 通常情况下，一个网站应该保证其接收到的表单都仅来自其自己的页面。

> ### 情景 ###
> 考虑这样一个例子（这个例子看起来比较脑残，但是当判断条件非常多的时候，其实是很容易犯这种错误的）：

> 页面`http://example.com/deliver.php`实现了发布留言的功能。如果用户已经通过该网站的login页面登录，则用户就可以发表留言，否则给出提示说请登录。此页面的逻辑大概是：
```
if(!$_POST['submit'])
{
	if(已登录)
	{
		echo '<form target="deliver.php?submit=1" method="POST">';
		echo '<input type="text" name="content/>';
		echo '<input type="submit">提交</input>';
		echo '</form>';
	}
	else
	{
		echo '请先登录！';
	}
}
else
{
	将用户提交的留言存入数据库;
}
```

> 对正常用户来说，这个留言板没有任何问题。实际上，上述逻辑基于一个假设：如果不给用户显示表单，用户就不可能提交数据。然而，我们可以简单地在自己的计算机上写一个HTML文件（外部表格）：
```
<form target="http://example.com/deliver.php?submit=1" method="POST">
<input type="text" name="content/>
<input type="submit">提交</input>
</form>
```
> 用浏览器打开这个文件，填好留言内容，点提交，留言就发布在example.com上了，完全用不着登录。

> ### 防范措施1：双重验证 ###
> 要想避免这种情况非常简单：在上述代码的“将用户提交的留言存入数据库;”前面加上一个判断即可。
```
if(未登录)
{
	echo '请先登录！';
	return;
}
```
> 从而服务器进行了两次权限验证。第一次确保了友好的用户体验，而第二次才真正实现了权限机制。

> ### 防范措施2：Form Hash ###
> 另一种防范措施是使用一种叫做Form Hash（Discuz是这么叫的）的技术。它实现起来比前者复杂，而其意义在于：
    1. 有模块性。整个网站只需实现一套Form Hash机制。即使程序员在双重验证方面有疏漏，Form Hash也会确保权限机制的健全。
    1. 在某些情形下（下一节）有不可替代性。
> Form Hash的基本原理是：网站根据当前登录用户的用户名、密码Hash值、当前时间戳及其它某些信息生成一个Hash值，称为Form Hash（记这个计算为formhash()函数）。formhash()所使用的信息能够保证在一定的时间段内，每个合法登录用户访问该网站的任何页面都会获得唯一且固定的Form Hash。在网站显示给用户的表单中，加入一个隐藏字段：
```
<input type="hidden" name="formhash" value="{FORMHASH}"/>
```
> 其中，{FORMHASH}是网站在将该表单呈现给用户时调用formhash()所得到的值。

> 当用户提交该表单后，服务器会再次调用formhash()，并验证其返回值与用户提交的表单中的formhash字段的数据是否相等。若不相等则认为是非法请求。

> 这样，如果恶意者想制作一个有效的外部表格，就必须在表单中写出正确的formhash。即使此人掌握服务器程序的所有源码（包括formhash()的具体算法），只要他无法以被攻击用户的身份登录网站，他就不可能使得外部表格的formhash与服务器产生的formhash()相等（即使他知道被攻击用户的用户名和密码Hash）。

> 通过合理的架构设计，Form Hash机制就可以方便地应用于整个网站，而不需要程序员在实现具体功能时考虑外部表格问题。

> 以上Form Hash的思想来自Discuz源码（是谁原创的就不知道了）。

## 自动执行的链接 ##
> 一个网站可以让用户不用点击某链接而自动执行该链接指向的文件吗？——可以
> 网站禁止用户发布js代码，用户还能通过发布某些代码而让链接自动执行吗？——可以
> ### 情景 ###
> 论坛`http://bbs.example.com`搞了个选举版主的投票，凡是登录用户都有权限参与投票。投票时只需点击竞选者头像旁边的“给TA投票”链接即可。这个链接的样子大概是：
```
 poll.php?target_uid=xxx
```
> 现在uid=23的竞选者想要拉票，于是他在论坛里发了一个帖子，帖子里贴了一张图片，图片的地址是：
```
 poll.php?target_uid=23
```
> 于是，论坛呈现给用户的HTML代码是
```
 <img src="poll.php?target_uid=23"/>
```
> 这不是一张图片！所以浏览器会显示一个小红叉。但是，这时候脚本poll.php已经执行了，并且为uid=23的用户添加了一票。

> 也就是说，只要看到这个小红叉的用户，都会被迫给23号用户投上一票！

> 在这种情况下，前面所说的“双重验证”法是失效的。因为此举并没有违背权限机制：看到小红叉的用户确实有权限给23号用户投票。

> ### 防范措施1：限制贴图格式 ###
> 最简单的防范措施就是通过正则表达式等方法检查用户指定的贴图地址。例如，只允许图片地址的扩展名为.jpg等。但是，这种简便方法是以牺牲论坛程序的功能为代价的。因为确实有一些图片是由服务器脚本自动生成的，其扩展名可以是.php、.asp等（只不过MIME类型是图片类型）。另外，也没人说过扩展名为.jpg的文件不能是PHP脚本。

> ### 防范措施2：Form Hash ###
> Form Hash可以较完美地解决这个问题。凡是网站中有“提交数据”性质的链接，在链接的查询字串里都加上Form Hash：
```
 poll.php?target_uid=xxx&formhash={FORMHASH}
```
> 由于用户在发帖时只能指定静态链接而不可能调用到服务器的formhash()函数，所以23号用户只能在图片链接里指定一个静态的formhash值。但是每个用户的formhash都是不一样的。这样，虽然用户看到小红叉时投票链接已经被自动执行了，但是提交到服务器上的请求是非法的，因为formhash不相符。

## 伪造HTTP头 ##
> 在HTTP协议中，HTTP头就是在实际的传输内容（例如服务器传给客户端一个HTML文件、或者客户端传给服务器一个POST或GET方法的请求）之前的一些东西。HTTP头里记录了很多重要的信息。例如，用户点击了一个链接后，传到服务器的HTTP请求中会包含该链接的引用页、用户的IP地址、操作系统和浏览器类型、Cookie等各种信息。从服务器返回的数据中，则包含返回文件的MIME类型（文本、图片、二进制文件之类的）等信息。

> 这些数据全部都是可以伪造的。服务器的任何通过HTTP头来对身份或合法性做出的判断都是不可靠的。（HTTPS不一定）

> （目前还没有想到什么很好的情景，因为大家都HTTPS了）

## ActiveX ##
> 微软的脑残加上用户的脑残就可以让浏览器运行任何可执行程序了，所以ActiveX能造成的危害性基本上unlimited，不多说了。

# 数据库安全 #

## SQL注入式攻击 ##

> SQL注入式攻击的在维基百科[SQL injection](http://en.wikipedia.org/wiki/SQL_injection)条目中讲得比较清楚了。简而言之，就是利用程序在构造SQL查询时的漏洞，通过提交一些特殊的字符串，和SQL查询中的“'”配对，然后再在后面加上危害性查询。

> 低版本的PHP & MySQL解决此问题的方法是强制给所有提交到服务器的数据（POST、GET、COOKIE）加上特殊符号的转义符（例如把“'” 变成“`'”）。高版本的PHP & MySQL以及.Net Framework & SQL Server等的解决方法是使用[参数化查询](http://en.wikipedia.org/wiki/SQL_injection#Parameterized_statements)。

> 总之，虽然SQL注入性攻击能产生很大的危害，但程序员只要在编程时稍微注意一下，就可以很容易地防范。

# HTTPS #
> 详细信息见Wiki [HTTPS](http://en.wikipedia.org/wiki/HTTPS)条目。

  * HTTPS就是将HTTP协议和SSL/TLS协议结合起来以实现数据的安全传送的协议。
  * 一个HTTPS连接是可信的，当前仅当以下四个条件同时成立：
    1. The user trusts the certificate authority to vouch only for legitimate websites without misleading names.
    1. The website provides a valid certificate (an invalid certificate shows a warning in most browsers), which means it was signed by a trusted authority.
    1. The certificate correctly identifies the website (e.g. visiting https://example and receiving a certificate for "Example Inc." and not anything else).
    1. Either the intervening hops on the Internet are trustworthy, or the user trusts the protocol's encryption layer (TLS or SSL) is unbreakable by an eavesdropper.

> 从这些条件来看，如果浏览器已经给出了“该网站的证书不受信任”的提示，而脑残用户依然忽略之并继续操作，HTTPS就基本上形同虚设了。也就是说HTTPS的安全性是需要以用户的判断和正确操作为前提的。（还不太肯定这一点）

  * （关于怎样搭建HTTPS服务器还没有调查）