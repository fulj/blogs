https://www.pianshen.com/article/2800297718/	
https://blog.csdn.net/bdss58/article/details/77929685

本机socket通讯时，用winshark抓不到任何数据包


tcp localhost 不走物理网卡而是走lo这一个虚拟网络接口，抓包选lo接口能抓到。

unix domain sockets vs. internet sockets

https://www.cnblogs.com/xiangtingshen/p/10923350.html
socket API原本是为网络通讯设计的，但后来在socket的框架上发展出一种IPC机
制，就是UNIX Domain Socket。虽然网络socket也可用于同一台主机的进程间通讯（通过
loopback地址127.0.0.1），但是UNIX Domain Socket用于IPC更有效率：不需要经过网络协
议栈，不需要打包拆包、计算校验和、维护序号和应答等，只是将应用层数据从一个进程拷
贝到另一个进程。这是因为，IPC机制本质上是可靠的通讯，而网络协议是为不可靠的通讯
设计的。UNIX Domain Socket也提供面向流和面向数据包两种API接口，类似于TCP和UDP，
但是面向消息的UNIX Domain Socket也是可靠的，消息既不会丢失也不会顺序错乱。
UNIX Domain Socket是全双工的，API接口语义丰富，相比其它IPC机制有明显的优越
性，目前已成为使用最广泛的IPC机制，比如X Window服务器和GUI程序之间就是通过UNIX
Domain Socket通讯的。
使用UNIX Domain Socket的过程和网络socket十分相似，也要先调用socket()创
建一个socket文件描述符，address family指定为AF_UNIX，type可以选择SOCK_DGRAM或

SOCK_STREAM，protocol参数仍然指定为0即可。
UNIX Domain Socket与网络socket编程最明显的不同在于地址格式不同，用结构体
sockaddr_un表示，网络编程的socket地址是IP地址加端口号，而UNIX Domain Socket的地
址是一个socket类型的文件在文件系统中的路径，这个socket文件由bind()调用创建，如果
调用bind()时该文件已存在，则bind()错误返回。
以下程序将UNIX Domain socket绑定到一个地址。

