- 研究RC、Service等配置文件的格式
- 熟悉kubectl的子命令
- 手工停止某个Service对应的容器进程，然后观察有什么现象发生。
- 修改RC文件，改变副本数量重新发布，观察结果

Kubernetes的基本概念和术语
---

资源：Node、Pod、Replication Controller、Service，几乎所有资源都可以通过Kubernetes提供的kuberctl工具（或者API编程调用）执行增、删、改、查等操作并将其保存在etcd中持久化存储。从这个角度来讲Kubernetes其实是一个高度自动化的资源控制系统，它通过跟踪对比etcd库里保存的”资源期望状态“与当前环境中的”实际资源状态“的差异来实现自动控制和自动纠错的高级功能。

声明一个Kubernetes资源对象的时候，需要注意一个关键属性：apiVersion。
```
apiVersion: v1
kind: Pod
metadata:
	name: myweb
	labels:
		name: myweb
spec:
	containers:
	- name: myweb
	  images: kubeguide/tomcat-app:v1
	  ports:
	  - containerPort: 8080
```
可以看到pod这种资源对象属于v1这个核心API

### Master
Master 负责整个集群的管理和控制，基本上Kubernetes所有的控制命令都发给他，它负责具体的执行过程。建议高可用部署3台，因为是整个集群的首脑，宕机则集群内容器应用的管理都将失效。

Master上运行的关键进程：  
- Kubernetes API Server(kube-apiserver): 提供HTTP REST服务的关键进程，是Kubernetes里所有资源的增、删、改、查等操作的唯一入口，也是集群控制的入口程序
- Kubernetes Controller Manager（kube-controller-manager）：Kubernetes所有资源对象自动化控制中心，资源对象的大总管。
- Kubernetes Scheduler（kube-scheduler）：负责资源调度（Pod调度）的进程，相当于公交公司的”调度室“
- etcd服务，所有资源对象的数据都被保存在etcd中
### Node
除了Master Kubernetes集群中的其他节点就是node，可以是一台虚拟机可以是一台物理主机，是Kubernetes集群工作负载节点。每个node都会被Master分配一些工作负载（Docker容器），当某个node宕机时候其上的工作负载会被master转移到其他节点上。

Node上运行的关键进程
- kubelet：负责Pod对应容器的创建、启停等任务，同时与Master密切协作，实现集群管理的基本功能。
- kube-proxy：实现Kubernetes Service的通信与负载均衡机制的重要组件
- Docker Engine（docker）：Docker引擎，负责本机的容器创建工作和管理工作。

Node可以在运行期间动态增加到Kubernetes集群中，前提是这个节点上已经正确安装、配置和启动了上述关键进程，在默认情况下kubelet会向Master注册自己，并上报自生的情报，好让Master高效均衡的资源调度。

```
kubectl get nodes
kubectl descrbe node k8s-node-1
```
### Pod
Pause的好处：

- Pause的状态代表整个容器组的状态
- Pod里的多个业务容器共享Pause容器的IP，共享Pause容器挂接的Volume，简化了业务容器之间的通信问题，以及文件共享问题
- Kubernetes为每个Pod分配唯一的IP地址，称之为Pod IP, 一个Pod里的多个容器共享Pod IP地址。Kubernetes要求底层网络支持集群内任意两个Pod之间的TCP/IP直接通信，这通常采用虚拟二层网络技术来实现，例如Flannel、Open vSwitch等，因此，一个Pod里的容器与另外Pod容器能够直接通信

### Replication Controller
- 期待的pod数量
- 用于筛选目标Pod的Label Selector
- 当Pod的副本数量小于预期数量是，用于创建新Pod的Pod模板（template）

在我们定义了一个RC并将其提交到Kubernetes集群中后，Master上的Controller Manager组件就得到通知，定期巡检系统当前存活的目标Pod，并确保目标Pod实例的数量刚好等于此RC的期望值，如果有过多的Pod副本运行，系统就会停掉一些Pod，否则系统会再创建一些pod。通过RC Kubernetes实现了用户应用集群的高可用性，并且大大减少了系统管理员在传统IT环境中需要完成的许多手工运维工作（如主机监控脚本、应用监控脚本、故障恢复脚本等）。

此外，在运行时，我们可以通过修改RC的副本数量，来实现Pod的动态缩放（Scaling）可以通过执行kubectl scale命令来一键完成
```
kubectl scale rc redis-slave --replicas=3
```
kubectl 还提供了stop和delete命令来一次性删除RC和RC控制的全部Pod

很容易实现滚动升级 每停止一个旧版本的pod就创建一个新版本的pod

Replication Controller由于与Kubernetes代码模块中的Replication Controller同名，同时 ”Replication Controller“ 无法精确的表达其本意，所以在Kubernetes1.2中改名为Relication Set 官方解释其为下一代的RC

当然我们很少单独使用Replica Set，它主要被Deployment这个高层次的资源对象所使用，而形成一套Pod创建、删除、更新的编排机制。我们在使用Deployment时，无需关心它是如何创建和维护Reploca Set的，这一切都是自动发生的。

Replica Set 和 Deployment这两个重要的资源对象逐步代替了之前RC的作用，是Kubernetes1.3里Pod自动扩容（缩容）这个告警功能实现的基础

RC（Replica Set）一些基本的特性和作用
- 定义RC实现Pod的创建及副本数量的自动控制
- 在RC里包括完整的Pod定义模板
- RC通过Label Seletor机制实现对Pod副本的自动控制
- 通过改变RC副本数量可以实现Pod的扩容和缩容
- 通过改变RC里Pod模板中的镜像版本，可以实现Pod的滚动升级

### Deployment
- 创建一个Deployment对象来生成对应的Replica Set并完成Pod副本的创建
- 检查Deployment的状态来看部署动作是否完成
- 更新Deployment以创建新的Pod
- 如果当前Deployment不稳定，则回滚到一个早先的Deployment版本
- 暂停Deployment以以便于一次性修改多个PodTemplateSpec的配置项，之后再恢复Deployment，进行新的发布。
- 扩展Deployment以应对高负载
- 查看Deployment的状态，以此作为发布是否成功的指标
- 清理不再需要的旧版本ReplicaSets


