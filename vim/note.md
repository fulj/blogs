现在vim配置基本上ok了  
代码补全:YouCompleteMe  
目录树:NERDTree  
语法检查:syntastic  
函数跳转到头文件中，光标选中头文件设置path,然后按gf，返回按ctrl-o
```
set path=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include
```
[一个大神的配置以及讲解很全](https://cloud.tencent.com/developer/article/1058322)  

- vim-startify
> It works without any configuration, but you might want to look into the documentation for further customization:
```
:h statify
:h statify-faq
```


- taglist
pre: taglist是依赖ctags的我mac中自带的有问题，要安装Exuberant ctags brew install就可以
1. download taglist (官网)(https://sourceforge.net/projects/vim-taglist/postdownload)
2. Download the taglist.zip file and unzip the files to the $HOME/.vim or the $HOME/vimfiles or the $VIM/vimfiles directory.
3. 安装ctags mac自带的ctags会报错
```
brew install ctags
```
4. 在我电脑上这样就可以用了

youtube useful plugin
https://www.youtube.com/watch?v=knSFZCKMy20
https://www.youtube.com/watch?v=ewT015uTBm8&t=63s

待解决的问题是c语言的头文件 vim怎么自动跳入
需要在vimrc中path中指定头文件目录



宏录制  视频最后  
https://www.bilibili.com/video/BV1Th411Z7Lw?from=search&seid=212973834581574170

啥意思？？
ctags -R --exclude=.git --exclude=log * 
$ echo 'alias ctags="`brew --prefix`/bin/ctags"' >> $HOME/.zshrc
$ exec $SHELL

$ brew --prefix
/usr/local  
因为我brew装的ctags 装在了/usr/local/bin/ctags


mac clang 标准头文件在哪里

ctags mac c 头文件 生成头文件的标签
https://blog.csdn.net/foreverling/article/details/80329586

cscope 这个插件看下是啥？

### To generate ctags for std header
```
ctags -R -f ~/.vim/sys_tags -I __THROW --extra=+f --languages=c --langmap=c:+.h --c-kinds=+px --fields=+aiKSz

ctags -R -f ~/.vim/sys_tags -I __THROW --extra=+f --languages=c --langmap=c:+.h --c-kinds=+px --fields=+aiKSz /Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include
set tags+=~/.vim/sys_tags
```
-f tagfile:Use the name specified by tagfile for the tag 

cscope : https://medium.com/@invisprints/vim-ctags-cscope-b9976c8c2e28

C 标准库辣么多。。。。有 glibc, msvc, bsd libc......
先找到你在用什么版本的 libc ，然后上网搜源码就是啦

一般操作系统是不会提供源码的，提供的都是二进制包
1. C 里面没有类，那是标准库。 C++才有类库
2. 你所调用的 C 代码一般是动态链接到 libc 的，你只能看到头文件里的函数声明，看不到实现。
OS X 用的 libc 在这里 https://opensource.apple.com/source/Libc/Libc-1082.20.4/。值得一提的是 OS X 底层基于 FreeBSD ，你也可以看未修改过的 FreeBSD 的 libc 代码 https://github.com/freebsd/freebsd/tree/master/lib/libc 。
vim 查找带空格的字符串要转义 :/\ kind\ \ \ 

:ptag test 支持tab补齐
:pc 关闭预览窗口
insert 模式下ctrl+n 可以补齐tag

:h usr_01.txt 帮助文档，不清楚这玩意是啥玩意

:tags 显示当前tags列表
ctrl+] 
ctrl+t 往回 逆向操作是 :tag
