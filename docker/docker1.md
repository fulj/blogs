## Docker 守护进程
Docker守护进程是用户与Docker交互的枢纽。他控制着机器上的Docker访问权限，管理着容器与镜像的状态，同事代理着与外界的交互  

**允许其他人连接你的Docker守护进程，并执行操作** 

使用开放的TCP地址启动Docker守护进程，开放之前必须先停止正在运行的实例。
```
sudo service docker stop
# 或
systemctl stop docker
# 该方法查看是否停止成功
ps -ef | grep -E 'docker(d| -d daemon)\b' | grep -v grep
# 以下命令重启并向世界用户开放它
sudo docker daemon -H tcp://0.0.0.0:2375
# 可以从外部使用一下命令连接
docker -H tcp://<宿主机ip>:2375 <subcommand>
# 可设置DOCKER_HOST环境变量
export DOCKER_HOST=tcp://<host ip>:2375
docker <subcommand>
# 需要注意的是本地也要这么做，因为docker已经不在默认的位置监听了
```
**以守护进程方式运行容器**   

```
# 使用-d选项以守护进程方式运行容器。-i 赋予容器与Telnet会话交互的能力。
# -p 端口映射 --name 赋予容器一个名称 使用netcat(nc)在1234端口运行一个简单的监听应答服务器。
docker run -d -i -p 1234:1234 --name daemon ubuntu:14.04 nc -l 1234
```
现在可以使用telnet连接并发送消息。使用docker logs 命令可以看到容器已经接收该消息
```
$ telnet localhost 1234
	Trying ::1...
Connected to localhost.
Escape character is '^]'.
hello daemon
^]
telnet> q
Connection closed.
$ docker logs daemon
hello daemon
$docker rm daemon
daemon
```

docker 重启选项
| 策略                   | 描述           |
|------------------------|----------------|
| no                     | 不重启         |
| always                 | 总是重启       |
| unless-stopped         | 显示停止不重启 |
| on-failure[:max-retry] | 失败时重启     |
```
docker run -d --restart=always ubuntu echo done
```
这个命令的效果是不断的重启退出重启退出，容器id不变
```
docker run -d --restart=on-failure:10 ubuntu /bin/false
```
容器名称，Docker 会连接两个随机单词为容器命名。

**将Docker移动到不同分区** 

Docker 把所有与容器和镜像有关的数据存储在一个目录下。因为它可能会存储大量不同的镜像，所以这个目录可能会迅速变大！
1. 停止Docker守护进程，并使用-g标志指定新的位置来重启
```
dockerd -g /home/dockeruser/mydocker
```


**使用socat监控DockerAPI流量** 

用户将自己的请求与服务器套接字之间插入一个代理Unix域套接字去查看通过它的内容。注意，完成这一步需要root或sudo权限。  
创建代理  
```
socat -v UNIX-LISTEN:/tmp/dockerapi.sock,fork \
		  UNIX-CONNECT:/var/run/docker.sock &
```
> socat 是 增强版的netcat


