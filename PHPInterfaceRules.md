# 目录结构 #
  * 整个PHP网站的目录结构为
    * library 存放函数和类定义文件。该文件夹中的文件被include之后，其内容不会被直接执行，因为这些文件中只包含函数或类定义。
    * include 存放会被其他文件include的文件。该文件夹中的文件被include之后，其内容会被直接执行，因为这些文件中存在写在函数或类定义之外的语句。
    * configuration 存放配置文件
    * index.php 根目录下唯一的PHP文件，也是唯一可直接由HTTP访问的文件。所有HTTP请求通过该文件分发到include中的各inc文件中。index.php的GET和POST接口见该文件的注释。
  * `http://server.lives3.net`（手机服务器端）和`http://info.lives3.net`（网页端）均会指向index.php。index.php将根据域名做第一级指令分类。index.php的GET查询中包含了第二级指令分类。

# 命名规范 #
  * 类定义文件：{class\_name}.class.php，存入library文件夹。
  * 函数定义文件：{file\_name}.func.php，存入library文件夹。
  * 被其他文件包含的文件：{file\_name}.inc.php，存入include文件夹。
  * 配置文件：{file\_name}.config.php，存入config文件夹
  * 类名、函数名和变量名的格式同JAVA。

# SVN #
  * 服务器上的SVN不知为什么连不上，我暂时把工程放在了https://march2010.googlecode.com/svn/trunk/phpsite
  * 请用eclipse的插件subclipse从上述地址checkout我们的工程。
  * 服务器上的SVN修复后，应该可以用subclipse提供的“切换/Switch”功能换到服务器的SVN上。