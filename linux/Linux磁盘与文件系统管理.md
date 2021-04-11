[TOC]
创建文件系统，包括分区、格式化、与挂载

扇区(Sector):最小的物理存储单位 有512B 与4KB 两种格式。

柱面(Sylinder):以前分区的最小单位，现在扇区是分区的最小单位。

分区表：MBR GPT 两种格式

超级区块：记录此文件系统的整体信息，包括inode与数据区块的总量、使用量、剩余量、以及文件系统的格式与相关信息等；  
inode：记录文件的属性，每一个文件占用一个inode，同事记录此文件的数据所在的区块号码  
数据区块：实际记录文件的内容，若文件太大时，会占用多个区块。  

没有inode与数据区块都由编号。

有inode称为索引式文件系统（indexed allocation）。U盘使用FAT格式的文件系统，没有办法将这个文件的所有区块在一开始就读出来只能1->7->4->16一个一个地将区块读出来。需碎片整理。

文件系统一开始就将inode与数据区规划好，除非重新格式化（resize2fs等命令修改其大小），否者inode与数据区块固定后就不再变动。
# ext2 文件系统
ext2文件系统格式化的时候区分多个区块群组（block group），每个区块群组都由独立的inode，数据区块，超级区块

数据区块（data block）
---
ext2 文件系统支持的区块大小有1K、2K以及4K三种。每个区块内最多可以放置一个文件的数据。格式化的时候区块大小就固定了，且每个区块都由编号，方便inode记录。区块大小与单一文件大小和最大文件系统总量的关系  
| Block大小          | 1KB  | 2KB   | 4KB  |
|--------------------|------|-------|------|
| 最大单一文件限制   | 16GB | 256GB | 2TB  |
| 最大文件系统总容量 | 2TB  | 8TB   | 16TB |

inode table(inode 表)
---
- 该文件的读写属性(rwx)
- 该文件的拥有者用户组(owner, group)
- 该文件大小
- 该文件建立或状态改变时间(ctime)
- 最近一个读取时间(atime)
- 最近修改时间(mtime)
- 定义文件特性的标识(flag)，如SetUID
- 该文件真正内容的指向(pointer)
- 每个inode大小128B(ext4与xfs可设置到256B)
- 系统读取文件时需要找到inode判断权限和用户是否符合
- 文件系统能创建的文件数量与inode数量有关

Superblock（超级区块）
---
- 数据区块与inode的总量
- 未使用与已使用的inode与数据块数量
- 数据区块与inode大小（数据块为1、2、4K，inode为128B或256B）
- 文件系统挂载时间、最近一次写入数据时间、最近一次检验磁盘（fsck）的时间等文件系统相关信息。
- 一个有效位数值，若此文件系统已被挂载，则有效位为0，若未被挂载，则有效位为1；

Filesystem Description(文件系统描述说明)
---
这个区段可以描述每个区块群组的开始于结束的区块，以说明每个区段（超级区块、对照表、inode对照表、数据区块）分别介于那个一个区块之间，这部分可以用dumpe2fs来观察

区块对照表（block bitmap）
---
inode对照表（inode bitmap）
---

# 与目录树的关系

目录
---
文件系统会分配一个inode与至少一个区块给该目录。inode记录相关权限与属性，并可记录分配到的区块号码。  
区块记录这个目录下的文件名与该文件占用的inode号码数据。
```
# 查看inode号码	
ls -li
```

# 磁盘的分区、格式化、检验与挂载

XFS文件系统 mkfs.xfs
---
```
mkfs.xfs /dev/sdd1	
blkid /dev/sdd1
```

xfs 可以使用多个数据流来读写系统，以增加速度，因此那个agcount可以跟CPU的内核来做搭配

XFS文件系统for RAID性能优化（Optional）
---

# 文件系统挂载与卸载
mount   
unmount 

# 设置启动挂载

启动挂载/etc/fstab 及 /etc/mtab  
/etc/fatab是启动时的配置文件，实际文件系统的挂载是记录到/etc/mtab 与 /proc/mounts这两个文件中的。

loop挂载，镜像文件不刻录就挂载使用。

大文件制作loop设备文件
---
dd 可以用来建立空文件  
dd if=/dev/zero of /srv/loopdev bs=1M count=512  
mkfs.xfs -f /srv/loopdev  
blk /srv/loopdev  
mount -o loop UUID="" /mnt  
df /mnt  
写入文件/etc/fstab


/dev/mapper/xxx 和 LVM有关
