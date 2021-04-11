```
echo $PATH
/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin:/usr/X11R6/bin:/opt/python27/bin:/opt/satools:/root/bin

PATH="${PATH}:/root"

```
**创建链接文件**

- -l 创建实体链接（hard link）
- -s 则创建符号链接（symbolic link）
```
cp -s bashrc bashrc_slink
cp -l bashrc bashrc_hlink
```