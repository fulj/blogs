## 与systemd的deamon运行过程相关的目录简介
systemd 启动脚本配置文件在/usr/lib/systemd/system/ 与 /etc/systemd/system/目录下，还有哪些目录跟系统的daemon运行有关呢？
- /usr/lib/systemd/system/  
使用CentOS官方提供的软件安装后，默认的启动脚本配置文件都放在这里，这里的数据尽量不要修改，要修改时，请到/etc/systemd/system/下面修改比较好
- /run/systemd/system/  
系统执行过程中所产生的服务脚本,执行优先级比/usr/lib/systemd/system/高  
- /etc/systemd/system/  
管理员根据主机系统的需求所建立的执行脚本，其实这个目录有点像以前/etc/rc.d/rc5.d/Sxx 之类的功能，执行优先级又比/run/systemd/system/高
- /etc/sysconfig/\*  
几乎所有的服务都会将初始化的一些选项设置写入到这个目录，举例来说，mandb所要更新的man page索引中，需要加入的参数就写入到此目录下的man-db当中。而网络的设置则写在/etc/sysconfig/network-script/ 这个目录中  
- /var/lib/  
一些会产生数据的服务都会将它的数据写入到/var/lib/ 目录中。举例来说，数据库管理系统MariaDB的数据库默认就写入/var/lib/mysql/ 中  
- /run/  
放置了好多deamon的缓存，包括lock文件以及PID文件等。

我们知道systemd里面很多的本机会用到socket服务，里面可能会产生很多socket文件，那你怎么知道这些socket文件放置在哪里呢？很简单，还是通过systemctl来管理。
```
systemctl list-sockets
```
这样很清楚的就能够知道正在监听本地服务需求的socket文件所在位置了。  
- 网络服务于端口对应简介
如果你的主机提供很多网络服务，但是ip只有一个，所以就通过端口号（port）来实现。
```
[root@hadoop-master ~]# cat /etc/services | grep ssh
ssh             22/tcp                          # The Secure Shell (SSH) Protocol
ssh             22/udp                          # The Secure Shell (SSH) Protocol
x11-ssh-offset  6010/tcp                        # SSH X11 forwarding offset
```
## 关闭网络服务
：
