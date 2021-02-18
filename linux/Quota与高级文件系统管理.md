# 磁盘配额（Quota）与高级文件系统
- 磁盘配额（Quota）

如果Linux系统有多个用户经常存取数据，为了维护所有用户在使用硬盘容量时的公平,磁盘配额（Quota）就是这么一款有用的工具。  
假设/home是一个独立的分区，这个分区有10GB，而/home下面有30个账号，也就是说每个账户会有333MB的空间才对，然而，有个用户在它的家目录下存放了很多电影，占了8GB的空间。便会造成其他用户的不便

quota 比较常使用的几个情况是：   
- 针对 www server，例如：每个人的网页空间的容量限制
- 针对 mail server，例如：每个人的邮件空间限制。
- 针对file server，例如：每个人最大的可用网络硬盘空间（教学环境中最常见）

上面是针对网络服务的设计，如果是针对Linux系统主机上面的设置那么使用的方向有下面这一些：  
- 限制某一群组所使用的最大磁盘配额（使用群组限制）：你可以将你的主机上的使用者分门别类，有点像是目前流行的付费与免付费会员制的情况
- 限制某一使用者的最大磁盘配额（使用者限制）：限制了群组之后，你也可以再继续针对个人来进行限制，使得同一群组之下还可以有更公平的分配！
- 限制某一目录（directory，project）的最大磁盘配额：在旧版的CentOS当中，使用的默认文件系统为EXT家族，这种文件系统的磁盘配额主要是针对整个文件系统来处理，所以大多针对“挂载点”进行设置。新的xfs可以使用project这种模式，这能够针对个别的目录（非文件系统）来设置磁盘配额。   
比较特别的是xfs的quota是整合到文件系统内，并不是其他的外挂的程序来管理，因此通过quota来直接回报磁盘使用率，要比unix工具俩的快速。  
举例来说，du 这东西会重新计算目录下的磁盘使用率，但xfs可以通过xfs_quota来直接回报各目录使用率，速度上快非常多。

**Quota的使用限制**   
- 在EXT文件系统家族仅能针对整个filesystem：EXT文件系统家族在进行quota限制的时候，他仅针对整个系统来设计，无法针对某一单个目录来设计他的磁盘配额。因此想使用不同的文件系统进行quota时，请先搞清楚该文件系统支持的情况。XFS已经可以使用project模式来设计不同目录的磁盘配额
- 核心必须支持quota：Linux核心必须有支持quota这个功能才行：如果使用CentOS7.x默认是成支持的。如果你是自行编译核心，那么请特别留意你是否已经真的打开了quota这个功能。
- 只对一般身份使用者有效：例如root就不能设置quota，因为整个系统所有的数据几乎都是他的
- 若启用SELinux，并所有目录均可设置quota：新版模式启用SELinux。该功能会加强某些细部的权限控制，因此默认情况下，quota只能针对/home进行设置。因此如果针对其他目录进行设置，需解开SELinux限制。


**Quota的设置项目**   
- 分别针对使用者、群组或个别目录（user，group&project）
- 容量限制或文件数量限制（block或inode）

**文件系统主要规划存放属性的inode与实际文件数据的block，Quota既然是管理文件系统，当然也可以管理inode或block**   
- 限制inode用量：管理使用者可以创建的“文件数量”
- 限制block用量：管理使用者磁盘容量的限制
- 柔性劝导与硬性规定（soft/hard）
	- hard：表示使用者绝对用量不会超过这个限制值，若超过会锁住用户磁盘使用权
	- soft：若超过soft且低于hard的限制每次使用者登陆系统，系统会主动发出磁盘即将爆满的警告讯息，且会给与一个宽限时间（grace time）若使用者在宽限时间倒数期间将容量再次低于soft限值之下，则宽限时间会停止。
	- 若超过宽限时间，那么soft限制值会即刻取代hard限值来作为quota的限制。

### 一个XFS文件系统的Quota范例
- 五个人账号分别是myquota1,myquota2,myquota3,myquota4,myquota5,密码都是password，所属群组是myquotagrp
- 账号的容量限制：五个用户磁盘使用量300MB（hard），文件数量不限制。超过250MB就予以警告（soft）
- 群组的限制（option 1）：由于系统里面还有其他用户存在，因此限制myquotagrp这个群组最多仅能使用1GB的容量。也就是说如果myquota1,myquota2,myquota3都用了280MB，那么其他两人最多只能使用（1000-280\*3=160MB）的磁盘容量了。这就是使用者与群组同事设置时会产生的后果
- 共享目录限制（option 2）：另一种设置方式，每个用户还是具有独立的容量限制，但是这个五个人的专题共享目录在/home/myquota这里，该目录设置为其他人没有任何权限的共享目录，仅myquotagrp群组有全部的权限。请注意群组限制于目录（directory/project）无法同时并存喔！
- 宽限时间设置：14天
```
# 制作账号
vim addaccount.sh
#!/bin/bash
groupadd myquotagrp
for usename in myquota1 myquota2 myquota3 myquota4 myquota5
do 
	user add -g myquotagrp $username
	echo "password" &#124; passwd --stdin $username
done
mkdir /home/myquota
chgrp myquotagrp /home/myquota
chmod 2770 /home/myquota
```

