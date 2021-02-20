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
2. BIOS和UEFI是固件接口标准，功能包括开机自检、启动流程（如何找到引导程序）、给操作系统和引导程序提供系统服务等。
3. MBR是引导扇区，包括最多446个字节的引导程序（通常是引导程序的前部）和MBR分区表，其中可以包括4个主分区
4. 启动方式是指如何主板上的固件在开机自检后找到引导程序，有Legacy模式（BIOS+MBR）和UEFI模式（UEFI+GPT）
5. https://zhuanlan.zhihu.com/p/36976698