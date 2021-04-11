# Sublime3下的两款Markdown插件

## MarkdownEditing
语法高亮
## OmniMarkupPreviewer
预览
## 安装插件管理器
Sublime中的插件管理器Package Control

打开sublime控制台输入以下代码
```
import urllib.request,os,hashlib; h = 'eb2297e1a458f27d836c04bb0cbaf282' + 'd0e7a3098092775ccb37ca9d6b2e4b7d'; pf = 'Package Control.sublime-package'; ipp = sublime.installed_packages_path(); urllib.request.install_opener( urllib.request.build_opener( urllib.request.ProxyHandler()) ); by = urllib.request.urlopen( 'http://packagecontrol.io/' + pf.replace(' ', '%20')).read(); dh = hashlib.sha256(by).hexdigest(); print('Error validating download (got %s instead of %s), please try manual install' % (dh, h)) if dh != h else open(os.path.join( ipp, pf), 'wb' ).write(by)
```
## sublime控制台
ctrl+~ 或者 View -> Show Console

## 安装MarkdownEditing

ctrl+shift+p进入Sublime命令板，输入 package install 从列表中选择 install Package 然后回车。这时候Sublime开始请求远程插件仓库的索引，所以第一次使用可能会有一些小的延迟。

看到列表的更新之后输入 markdown ed，选择MarkdownEditing。插件安装完毕后需要重新启动Sublime插件才能生效。

快捷键
- command + option + k 插入链接 ??? win10 里面是啥
- win + shift + k 插入图片

## 安装 OmniMarkupPreviewer
Command +Option +O: 在浏览器中预览
ctrl +alt +O: 在浏览器中预览
