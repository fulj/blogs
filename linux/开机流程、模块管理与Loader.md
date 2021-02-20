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