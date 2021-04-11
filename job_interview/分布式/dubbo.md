大系统拆分成多个功能模块给用户提供服务，拆分的这么多服务需要一个治理---dubbo

基于访问压力的调度中心，能够帮我们实时的监控这些数据，动态的调度，提供资源的利用率。在访问压力大的时候 -- 流动计算架构

通讯 序列化 反序列化

注册中心  负载均衡

灰度调度 -- 运行期间流量调度

可视化服务治理与运维


dubbo
--- 
dubbo是阿里开源的RPC分布式服务框架，现已成为Apache基金会的项目。内部使用了netty、zookeeper，保证高性能以及高可用性
核心配置 dubbo:service dubbo:reference dubbo:protocol dubbo:application dubbo:registry

### Provider上可以配置的Consumer端的属性有哪些
timeout、retries、loadbalance、actives 消费者端，最大并发限制

### Dubbo启动时如果依赖的服务不可用会怎样？
Dubbo缺省会在启动时检查依赖的服务是否可用，不可用时会抛出异常，阻止Spring初始化完成，默认check="true"

### Dubbo推荐使用的序列化框架
Hessian Duddo FastJson java 自带序列化
### Dubbo 模