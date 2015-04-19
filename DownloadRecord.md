# Introduction #

> 下载计数功能添加到了info.lives3.net/?op=60上。它指向web\_download.inc.php文件。
> 以后所有文件下载的链接请求可以发给info.lives3.net/?op=60，并传入要下载的文件名即可。

# Details #

## 功能 ##
> 它的功能很简单，就是根据name参数在$file\_dir文件夹下面查找文件，并返回给用户。同时像数据库插入一条log。

## 配置 ##
> $file\_dir 和 LOG\_WEB\_DOWNLOAD\_START 均定义在constant.inc.php中

> $file\_dir指向服务器存放下载文件的文件夹，该文件夹目前移至这里：/$HTTPDIR/../download
> 如果想添加下载文件，就请添加到这个目录下面吧。这样原先的下载路径就不可能直接访问到下载文件了。

> LOG\_WEB\_DOWNLOAD\_START的定义为14，参数为文件名。所以lives3\_logs表中logop=14的记录即为下载记录。

## 使用方法 ##
> 如果您想在blog或者网站的其他地方添加文件下载的链接，链接请采用如下方式：
> http://info.lives3.net/?op=60&name=fileName     其中fileName为download/目录下你想下载的文件名(大小写敏感)