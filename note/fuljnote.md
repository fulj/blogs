[Inter-process communication in Linux:Sockets and signals](https://opensource.com/article/19/4/interprocess-communication-linux-networking)  
Sockets are a special file type, similar to TCP/IP socket, providing inter-process networking protected by file system's access control.

For example, when you open a listening socket in one terminal with netcat:  
```
nc -lU socket.sock
```
then send data from another terminal by:  
```
echo mytext | nc -U socket.sock
```
mytext appears in the first terminal.
By default nc stops listening after an End-of-File character.

硬链接  
ln a b  : 表示创建了一个硬链接 ls -i inode是一样的，  
- 文件具有相同的inode及data block    
软链接
ln -s a c : 表示创建了一个软链接 innode是不一样的
- 软链接实际上是一个独立的文件有自己的inode
