1. 侦测硬件并载入适当的驱动程序
2. 调用程序准备系统运行的环境

好处：  
1. 理解开机原理
2. 出现问题能够快速修复
3. 配置多重操作系统的多重开机问题（grub2开机管理程序（boot loader））

QA:  
1. 多重开机如何安装系统
2. root密码忘记，如何救援
3. 默认登录为图形界面，如何在开机时直接指定进入纯文本模式
4. /etc/fstab 设置错误，导致无法顺利挂载根目录如何修复你的/etc/fstab

开机管理程序：  
1. 早期Linux默认使用grub1或LILO，spfdisk
2. 目前各大Linux Distribution 的主流是 grub2

系统开机流程:
1. 载入BIOS 自检 获取第一个可开机设备
2. 读取第一个开机设备内MBR内的boot Loader （grub2，spfdisk等程序）
3. 依据boot loader的设置载入Kernel，Kernel会开始侦测硬件与载入驱动程序
4. 在硬件驱动成功后，Kernel会主动调用systemd程序，并以default.target流程开机
   1. systemd启动sysinit.target初始化系统及basic.target准备操作系统；
   2. systemd执行multi-user.target 下的本机与服务器服务；
   3. systemd执行multi-user.target 下的/etc/rc.d/rc.local文件；
   4. systemd执行multi-user.target 下的getty.target及登录服务；
   5. systemd执行graphical需要的服务；


概念：  
1. 分区表 GPT MBR
2. BIOS无论是传统的BIOS（legacy）还是UEFI都被简称为BIOS
3. BIOS是Basic input output system的缩写。是一段程序，会固化在一个只读存储器中，可以是ROM或者NvRAM我们称这个硬件叫BIOS芯片。我们平常说的BIOS是固化在BIOS芯片中的程序
4. CMOS是硬件，是一个随机存储器RAM，用于保存当前电脑的硬件配置信息，一般开机按F12进入BIOS可以修改CMOS硬件中的数据。CMO
5. S是一个RAM断电会导致数据丢失，所以主板上会有一个电池，在电脑关机后给CMOS供电。
6. BIOS和UEFI是固件接口标准，功能包括开机自检、启动流程（如何找到引导程序）、给操作系统和引导程序提供系统服务等。
7. MBR是引导扇区，包括最多446个字节的引导程序（通常是引导程序的前部）和MBR分区表，其中可以包括4个主分区。MBR中的引导加载程序（Boot loader）他的目的是加载（load）内核文件。
8. 启动方式是指如何主板上的固件在开机自检后找到引导程序，有Legacy模式（BIOS+MBR）和UEFI模式（UEFI+GPT）
9. https://zhuanlan.zhihu.com/p/36976698
10. 核心文件在/boot 中，取名为/boot/vmlinuz。核心模块在/lib/modules/目录内。/ 和 /lib 必须在同一partition内。开机过程中核心必须挂载根目录，才能读取核心模块提供载入驱动程序的功能。
11. USB、SATA、SCSI等磁盘设备的驱动程序通常都是以模块的方式来存在。

假设你的linux是安装在SATA磁盘上面，你可以通过BIOS的INT 13取得boot loader与kernel文件来开机，然后kernel会接管系统并侦测硬件以及挂载根目录来取得额外的驱动程序。可是！kernel根本不认识SATA磁盘，所以要载入SATA磁盘的驱动程序，否则无法挂载根目录。但是SATA的驱动程序在/lib/modules内你根本无法读取/lib/modules内的驱动程序。怎么办？可以通过虚拟文件系统来处理这个问题。  
虚拟文件系统(Initial RAM Disk 或 Initial RAM Filesystem) 一般使用的文件名为/boot/initrd 或 /boot/initramfs ，这个文件能够通过boot loader载入到内存中，然后解压并在内存中仿真成一个根目录，且该内存中的文件系统能够提供一支可执行的程序，通过该程序来载入开机过程中所需要的核心模块，这些模块通常是USB、RAID、LVM、SCSI等文件系统与磁盘接口的驱动程序。等载入完成，会帮助核心重新调用systemd来开始后续的正常开机流程。

lsinitrd /boot/initramfs-2.6.32-220.23.2.ali878.el6.x86_64.img


## 开机第一个程序systemd及使用default.target进入启动程序分析
内核加载完毕、进行完硬件检测与启动程序加载后，此时你的主机硬件已经ready了。此时内核调用第一个程序systemd。pstree 可看到 systemd的pid为1.systemd主要功能是准备软件执行的环境。包括系统的主机名、网络设置、语言设置、文件系统格式、以及其他服务的启动等。所有的操作都会通过systemd的默认启动服务集合 /etc/systemd/system/default.target来规划。  

可作为默认的操作环境(default.target)的主要有：multi-user.target 以及 graphical.target这两个。

```
ll -d /usr/lib/systemd/system/runlevel*.target | cut -c 40-
/usr/lib/systemd/system/runlevel0.target -> poweroff.target
 /usr/lib/systemd/system/runlevel1.target -> rescue.target
 /usr/lib/systemd/system/runlevel2.target -> multi-user.target
 /usr/lib/systemd/system/runlevel3.target -> multi-user.target
 /usr/lib/systemd/system/runlevel4.target -> multi-user.target
 /usr/lib/systemd/system/runlevel5.target -> graphical.target
 /usr/lib/systemd/system/runlevel6.target -> reboot.target
```
| SystemV    | systemd                             |
|------------|-------------------------------------|
| init 0     | systemctl poweroff                  |
| init 1     | systemctl rescue                    |
| init [234] | systemctl isolate multi-user.target |
| init 5     | systemctl isolate graphical.target  |
| init 6     | systemctl reboot                    |

#### systemd 的处理流程
当取的/etc/systemd/system/default.target 这个默认操作界面的设置之后，他会链接到/usr/lib/systemd/system/这个目录中去取得 multi-user.target 或 graphical.target 这两个其中一个，假设我们使用graphical.target 接下来systemd会去找两个地方的设置，即如下目录：
- /etc/systemd/system/graphical.target.wants/: 用户设置加载的unit
- /usr/lib/systemd/system/graphical.target.wants/: 系统默认加载的unit
```
[root@hadoop-master system]# cat /usr/lib/systemd/system/graphical.target
#  This file is part of systemd.
#
#  systemd is free software; you can redistribute it and/or modify it
#  under the terms of the GNU Lesser General Public License as published by
#  the Free Software Foundation; either version 2.1 of the License, or
#  (at your option) any later version.

[Unit]
Description=Graphical Interface
Documentation=man:systemd.special(7)
Requires=multi-user.target
Wants=display-manager.service
Conflicts=rescue.service rescue.target
After=multi-user.target rescue.service rescue.target display-manager.service
AllowIsolate=yes

# 表示 graphical.target 必须要完成 multi-user.target 之后才能进行，而进行完graphical.target之后还要启动display-manager.service才行。


[root@hadoop-master system]# cat /usr/lib/systemd/system/multi-user.target
#  This file is part of systemd.
#
#  systemd is free software; you can redistribute it and/or modify it
#  under the terms of the GNU Lesser General Public License as published by
#  the Free Software Foundation; either version 2.1 of the License, or
#  (at your option) any later version.

[Unit]
Description=Multi-User System
Documentation=man:systemd.special(7)
Requires=basic.target
Conflicts=rescue.service rescue.target
After=basic.target rescue.service rescue.target
AllowIsolate=yes

# 系统默认加载的unit有哪些
root@hadoop-master system]# ls /usr/lib/systemd/system/multi-user.target.wants
dbus.service  plymouth-quit.service       systemd-ask-password-wall.path  systemd-update-utmp-runlevel.service
getty.target  plymouth-quit-wait.service  systemd-logind.service          systemd-user-sessions.service

# 使用者自定义加载的unit又有哪些
[root@hadoop-master system]# ls /etc/systemd/system/multi-user.target.wants
atd.service     chronyd.service  irqbalance.service  mysqld.service          remote-fs.target        rsyslog.service   sm-client.service  tuned.service
auditd.service  crond.service    kdump.service       NetworkManager.service  rhel-configure.service  sendmail.service  sshd.service       vmtoolsd.service
```

通过上面的结果可得出multi-user.target 需要在basic.target 运行完毕才能加载上诉许多的unit，最终这些依赖关系可以用 systemctl list-dependencies graphical.target 这个命令来列出来。


## 各硬件设备在Linux中的名称
在linux中每个设备都被当做一个文件来对待
| 设备                      | 文件名                                                                              |
|---------------------------|-------------------------------------------------------------------------------------|
| SCSI、SATA、USB磁盘启动器 | /dev/sd[a-p] 因为都是使用SCSI模块驱动                                               |
| U盘                       | /dev/sd[a-p]                                                                        |
| Virtio接口                | /dev/vd[a-p] (用于虚拟机内)                                                         |
| 软盘驱动器                | /dev/fd[0-7]                                                                        |
| 打印机                    | /dev/lp[0-2] (25针打印机)<br>/dev/usb/lp[0-15]                                      |
| 鼠标                      | /dev/input/mouse[0-15] (通用)<br>/dev/psaux (PS/2接口)<br>/dev/mouse (当前鼠标)     |
| CD-ROM、DVD-ROM           | /dev/scd[0-1] (通用)<br> /dev/sr[0-1] (通用，CentOS常见)<br>/dev/cdrom (当前CD-ROM) |
| 磁带机                    | /dev/ht0 (IDE接口)<br> /dev/st0<br> (SATA/SCSI接口)<br> /dev/tape(当前磁带)         |
| IDE磁盘启动器             | /dev/hd[a-d] (旧式系统才有)                                                         |

磁盘：/dev/sd[a-p]  
IDE接口的磁盘启动器几乎淘汰，因此现在IDE接口的磁盘文件名也被模拟为/dev/sd[a-p]  
如果你的机器是跟互联网服务提供商ISP申请的云主机，这是可能得到的是虚拟机，为了加速，虚拟机内的磁盘是使用模拟器产生的，该模拟器产生的磁盘文件名可能为/dev/vd[a-p]系列的文件名

使用虚拟机学习  
windows建议 virtualBox  
linux 建议 KVM

QA:PC上有两个SATA磁盘一个USB磁盘，主板上有6个SATA插槽。SATA磁盘分别安装在SATA1、SATA5插槽上，请问这三个磁盘设备文件名是？  
使用检测到的顺序来命令，并非按实际插槽顺序，所以  
1. SATA1插槽上为 /dev/sda
2. SATA5插槽上为 /dev/sdb
3. USB磁盘（系统启动完成后被系统识别）为 /dev/sdc

通常分区最小单位也是文件系统的最下单位为柱面（Cylinder） 因为MBR分区表只有64个字节每组分区表占16个字节，因此记录的信息相当有限
但是GPT可达64位记录功能的分区表，可以使用扇区(Sector)号码来作为分区单位。
#### MBR 分区表的局限
1. 无法使用2.2T以上的磁盘容量
2. MBR只有一个区块（512字节）若被破坏，很难恢复
3. MBR内启动引导程序的只占446个字节，无法存储较多的程序代码
### GPT分区表
GPT(GUID partition table)  
过去一个扇区512字节，不过目前已有4k扇区出现，为了兼容所有磁盘，因此扇区的定义上面，大多会使用所谓的逻辑区块地址(Logical Block Address, LBA) GPT将磁盘所有区块LBA（默认512字节）来规划，第一个称为LBA0.

GPT使用34个LBA区块来记录分区信息。同时过去MBR只有一个区块，GPT除了前面的34个LBA之外，整个磁盘的最后34个LBA也拿来最为一个备份。

- LBA0（MBR箭筒区块）
前446字节，存储了第一阶段的启动引导程序。而在原本的分区表及录区内仅放入一个特殊标志，用来表示此磁盘为GPT格式。不懂GPT分区表的磁盘管理程序就不会认识这块磁盘。
- LBA1（GPT表头记录）
记录分区表本身的位置与大小，同时记录备份GPT分区的位置。还放置校验码（CRC32），
- LBA2-33（实际记录分区信息处）
每个LBA记录4组分区记录，总共可以记录4\*32=128组分区记录。每个LBA有512字节，每组记录有128字节。GPT在每组记录中提供了64位来记录开始/结束扇区号码，因此GPT单一分区，他的最大容量限制为 2^64\*512字节 = 2^63\*1k = 2^33TB = 8ZB 1ZB = 2^30TB


### 分区最大容量
- MBR  
MBR是为32位系统设计的，分区中逻辑地址以32位为二进制表示，所以最大只能表示2^32个地址，所以最大容量为2^32\*512字节（默认每个扇区大小）= 2T  
最新的硬盘厂商默认扇区4K，MBR可支持的最大容量为2^32\*4k=16T  
其实这种说法不严谨，准确来说，MBR分区表大嘴能容纳2T的主要原因是因为分区表中的本分区表之前使用的扇区数以及分区总扇区数这两个字段为4字节 4个字节可以表示 32位 也就是说可以表示的最大扇区数为2^32 每个标准扇区的容量为512字节，于是能表示的最大容量为2^32\*512
- GPT  
每个LBA记录4组分区记录，总共可以记录4\*32=128组分区记录。每个LBA有512字节，每组记录有128字节。GPT在每组记录中提供了64位来记录开始/结束扇区号码，因此GPT单一分区，他的最大容量限制为 2^64\*512字节 = 2^63\*1k = 2^33TB = 8ZB 1ZB = 2^30TB

### 文件系统 
- temfs  
tmpfs is used in Linux for /run, /var/run and /var/lock to provide very fast access for runtime data and lock files

it is set by default to use half your total RAM

resize it by /etc/fstab
```
tmpfs   /tmp    tmpfs   nodev,nosuid,size=2G     0  0
```

```
[root@hadoop-master dev]# df -T
Filesystem              Type     1K-blocks    Used Available Use% Mounted on
/dev/mapper/centos-root xfs       17811456 9717572   8093884  55% /
devtmpfs                devtmpfs    486708       0    486708   0% /dev
tmpfs                   tmpfs       498976       0    498976   0% /dev/shm
tmpfs                   tmpfs       498976   32928    466048   7% /run
tmpfs                   tmpfs       498976       0    498976   0% /sys/fs/cgroup
/dev/sda1               xfs        1038336  132472    905864  13% /boot
tmpfs                   tmpfs        99796       0     99796   0% /run/user/0
tmpfs                   tmpfs        99796       0     99796   0% /run/user/1000
```

/dev
---
/dev contains device files which are created and removed automatically bu the udev daemon, as hardware is added or removed etc.(devtmpfs is just a tmpfs that was created specially by the kernel early in the boot process, which contains the core devices precreated so that the boot process has something to work with before udevd is loaded.)

/dev/shm
---
/dev/shm is used by the POSIX shared memory facilities.

/run
---
/run contains resource locks and PID files etc. which are relevant to currently-running daemons. /var/run and /var/lock are symlinks back ro /run for compatibility reasons.

/media
---
/media contains the mount-points of removable media(e.g. optical discs and USB drives), which are created and removed automatically.

/sys/fs/cgroup
---
/sys/fs/cgroup contains details for cgroup system, which is used(mainly by systemd) to divide processes into groups for resource sharing etc.
