```
MANUAL SECTIONS
       The standard sections of the manual include:

       1      User Commands

       2      System Calls

       3      C Library Functions

       4      Devices and Special Files

       5      File Formats and Conventions

       6      Games et. Al.

       7      Miscellanea

       8      System Administration tools and Deamons

       Distributions customize the manual section to their specifics, which often include additional sections.
```
man socket时，会显示socket(2),这个2是什么意思呢？它不是指有几个参数，而是表示socket的所在章节，2就是系统调用。具体如下：

1-commands

2-system calls

3-libray calls

4-special files

5-file formats and convertions

6-games for linux

7-macro packages and conventions

8-system management commands

9-其他

 

解释一下

1是普通命令

2是系统调用，如open，write之类的（通过这个，至少可以很方便的查到调用这个函数，需要加什么头文件）

3是库函数，如printf,fread

4是特殊文件，也就是/dev下的各种设备文件

5是指文件的格式，比如passwd,就会说明这个文件中各个字段的含义

6是给游戏留的，又各游戏自己定义

7是附件还有一些变量，比如向environ这种全局变量在这里就有说明

8是系统管理用的命令，这些命令只能由root使用，如ifconing

 

想要指定section就直接在man的后面加上数字，比如：

man 1 ls

man 3 printf

等等

对于像open，kill这种既有命令，又有系统调用的来说，

man open

则显示的是open(1)，也就是从最前面的section开始，

如果想查看open系统调用的话，

就得man 2 open
