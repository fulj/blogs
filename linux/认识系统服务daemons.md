在Unix-like的系统中，你会常常听到daemon这个字眼！如何视察这些daemon开了多少ports。这些ports要如何关闭。还有知道这些port各代表的是什么服务吗？

从CentOS 7.x 这一版之后，传统的init已经舍弃，取而代之的是systemd这个家伙。与init有什么差异？如何管理不同种类的服务类型，以及如何取代原本的“执行等级”等等。
## 什么是daemon与服务（service）
一般来说，当我们以文字模式或图形模式完整开机进入Linux主机后，系统已经提供我们很多的服务了。包括打印服务、工作调度服务、邮件管理服务等等；那么这些服务是如何被启动的
### 早期System V 的 init 管理行为中daemon的主要分类（Optional）
我们启动系统服务的管理方式称为SysV的init脚本程序的处理方式！亦即系统核心第一只调用的程序是init，然后init去唤起所有的系统所需要的服务，不论是本机服务还是网络服务。  
基本上init的管理机制有几个特色如下：
- 服务的启动关闭与观察方式：所有的服务启动脚本放置在 /etc/init.d/下面，基本上都是使用 bash shell script所写成的脚本程序，需要启、关闭、重新启动、观察状态时，可以通过如下方式来处理：
  - 启动：/etc/init.d/deamon start
  - 关闭：/etc/init.d/deamon stop
  - 重新启动：/etc/init.d/deamon restart
  - 状态观察：/etc/init.d/daemon status
- 服务启动的分类：init服务的分类中，依据服务是独立启动或被一只总管程序管理的分为两大类
  - 独立启动模式（stand alone）：服务独立启动，该服务直接常驻于内存中，提供本机或用户的服务行为，反应速度快。
  - 总管程序（super daemon）：由特殊的xinetd或inetd这两个总管程序提供socket对应或port对应的管理。当没有用户要求某socket或port时，所需要的服务是不会被启动的。若有用户要求时，xinetd总管才会去唤醒想对应的服务程序。当该要求接受