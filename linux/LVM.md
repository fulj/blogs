# 逻辑卷轴管理员（Logical Volume Manager）
LVM的重点在于“可以弹性的调整filesystem的容量”，而并非性能或数据可靠性（RAID干的事情）。LVM可以整合多个实体partition在一起，让这些partitions看起来就像是一个磁盘一样。而且还可以在未来新增或移除其他实体partition到这个LVM管理的磁盘当中。

什么是LVM：PV，PE，VG，LV的意思
---
LVM将实体的partitions或disk通过软件组合成为一块看起来是独立的大磁盘（VG），然后将这块大磁盘再经过分区成为可使用分区（LV）

- Physical Volume, PV，实体卷轴  
    - 实际的partition或disk需要调整系统识别码（system id）成为8e（LVM的识别码），然后再经过pvcreate的指令将他转成LVM最底层的PV，之后才能将这些PV加以利用。调整system ID的方法就是通过gdisk。
- Volume Group， VG ，卷轴群组
    - 所谓的LVM大磁盘就是许多PV整合整这个VG的东西。VG就是LVM组合起来的大磁盘。
- Physical Extent，PE，实体范围区块
    - LVM默认使用4MB的PE区块，而LVM的LV在32位系统上最多仅能含有65534个PE（lvm1的格式）。因此默认LVM的LV会有4M\*65534/1024M=256G。PE是整个LVM最小的存储区块，我们文件数据都是借由写入PE来处理的。调整PE会影响到LVM的最大容量。不过在CentOS6.x以后，由于直接使用lvm2的各项功能格式，以及系统转为64位，因此这个限制已经不存在了。
- Logical Volume，LV，逻辑卷轴
    - 最终VG还会被切成LV，这个LV就是最后可以被格式化的使用类似分区的。PE是整个LVM的最小存储单位，那么LV的大小就与在此LV内的PE总数有关。为了方便使用者利用LVM管理。因此，LV的设备文件名通常指定为“/dev/vgname/lvname”的样式
    - 此外LVM弹性变更filesystem容量，如何做到？其实他是通过“交换PE来进行数据转换，将原本LV内的PE转义到其他设备中以降低LV容量，或将其他设备中的PE加到此LV中以加大容量