docker的很多镜像不带ssh服务

创建一个带有SSH服务的镜像，两种方法：
- 基于docker commit命令创建
- 基于Dockerfile创建

### 基于commit命令创建
ubuntu 为啥一定要 apt-get update一下？
```
sed -r 's/session required pam_loginuid.so/#session required pam_loginuid.so/g' /etc    /pam.d/sshd
```





