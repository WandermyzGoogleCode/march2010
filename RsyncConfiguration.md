# Introduction #

This is a guide for deploy Rsync between windows server and Linux server.


# Details #

## rsync实现Linux下数据备份到Windows ##

### linux作为rsync的服务端 ###
  * 打开配置文件/etc/xinetd.d/rsyncd.conf(没有的话创建），修改相应的配置
```
 uid = root
 gid = root
 pid file = /var/run/rsyncd.pid
 lock file = /var/run/rsync.lock
 log file = /var/log/rsyncd.log
 use chroot = no
```
  * 注意这个用户id和组id，如果方便的话可以设置为root，这样rsync几乎可以读取任何文件和目录了，但是也带来安全隐患。建议设置成只能读取你要备份的目录和文件即可。
```
max connections = 4    #最大连接数 4
[www]                  #指定认证的备份模块名
path = /www            #需要备份的目录
comment = backup www
ignore errors          #忽略一些无关的IO错误
read nly = yes        #设置为只读（如果设为no的话，客户端可以上传文件）
list = no              #不允许列文件
auth users = root      #认证的用户名，如果没有这行，则表明是匿名
hosts allow = 192.168.1.222 #运行连接服务器的主机ip地址
secrets file = /etc/root.pass  #认证文件名，用来存放密码
```
  * 这一段修改完成
  * 注意：如果同时还需要备份其它目录的话，可以直接在备份文件的后面继续增加配置内容，例如：
```
[database]
path = /var
.....
```
  * 这样就可以同时备份多个目录了

  * 执行
```
ln -s /etc/xinetd.d/rsyncd.conf /etc/rsyncd.conf
```

  * 然后为备份模块设置密码文件，设置密码文件/etc/root.pass
```
vi /etc/root.pass
root:123456
```
  * 这样，为备份模块www的用户root设置了密码123456 ，注意，出于安全的目的，这个文件的属性必须为只读，否则rsync将拒绝运行
```
chmod 600 /etc/root.pass
```
  * 设置rsync服务在系统启动时自动运行，可以通过ntsysv来设置

  * 最后在服务器端我们需要启动rsync服务器：
```
service xinetd restart
[root@data ~]# netstat -nat|grep 873
```
  * 至此，服务器端配置完毕

  * 最后注意服务器端的防火墙设置


### windows客户端 ###
  * 在windows下安装cwRsync软件
  * 在windows下打开cmd窗口
```
 C:\Program Files\cwRsync\bin>rsync.exe -vrtopg root@192.168
.1.222::bak /cygdrive/f/bak --password-file=/cygdrive/f/root.pass
```
  * 说明：命令行中-vzrtopg里的v是verbose，z是压缩，r是recursive，topg都是保持文件原有属性如属主、时间的参数。--progress是指显示出详细的进度情况，--delete是指如果服务器端删除了这一文件，那么客户端也相应把文件删除，保持真正的一致。--exclude "count/" 表示不对count目录下的文件进行备份
  * ::bak 这是/etc/xinetd.d/rsyncd.conf文件中定义的模块名 /cygdrive/f/bak说明备份到windows下f盘下的bak目录下（此备份目录如果没有则自动创建）

  * --password-file是指定的密码文件
  * /cygdrive/f/root.pass指定密码文件存放在windows的f盘下的root.pass文件中 root.pass文件的内容为root的密码（只写密码即可）


### FAQ ###
  * Q：我需要在防火墙上开放哪些端口以适应rsync？
  * A：视情况而定
  * rsync可以直接通过873端口的tcp连接传文件，也可以通过22端口的ssh来进行文件传递，但你也可以通过下列命令改变它的端口：
```
rsync --port 8730 otherhost:: 或者 rsync -e ssh -p 2002 otherhost:
```
  * Q：我如何通过rsync只复制目录结构，忽略掉文件呢？
  * A：rsync -av --include **/ --exclude** source-dir dest-dir
  * Q：为什么我总会出现"Read-only file system"的错误呢？
  * A：看看是否忘了设"read nly = no"了
  * Q：为什么我会出现@ERROR: invalid gid的错误呢？
  * A：rsync使用时默认是用uid=nobody;gid=nobody来运行的，如果你的系统不存在nobody组的话，就会出现这样的错误，可以试试gid = nogroup或者其它
  * Q：绑定端口873失败是怎么回事？
  * A：如果你不是以root权限运行这一守护进程的话，因为1024端口以下是特权端口，会出现这样的错误。你可以用--port参数来改变。
  * Q：为什么我认证失败？
  * A：从你的命令行看，你用的是：
```
> bash$ rsync -a 144.16.251.213::test test
> Password:
> @ERROR: auth failed on module test
> I dont understand this. Can somebody explain as to how to acomplish this.
> All suggestions are welcome.
```
  * 应该是没有以你的用户名登陆导致的问题，试试
```
rsync -amax@144.16.251.213::testtest
rsync: read error: Connection reset by peer (104)
```
  * 我在服务器上查看日志，看到有这么一行：
```
rsync: unable to open configuration file "/etc/rsyncd.conf": No such file or directory
```
  * 于是我：
```
ln -s /etc/rsyncd/rsyncd.conf /etc/rsyncd.conf
```