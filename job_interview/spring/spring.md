## 什么是spring 
Spring是一个轻量级的Java开发框架，为了解决企业级应用开发应用逻辑层和其他各层的耦合问题。为开发Java应用程序提供全面的基础架构支持。Spring负责基础架构，Java开发者可以专注应用程序的开发。其根本使命是解决企业级应用开发的复杂性，简化Java开发。

Spring可以做很多事情，为企业级开发提供了丰富的功能，这些功能底层都依赖于他的两个核心特性，也就是依赖注入（dependency injection，DI）和面向切面编程（aspect-oriented programming,AOP）

- 基于POJO的轻量级和最小侵入性编程
- 通过依赖注入和面向接口实现松耦合
- 基于切面和惯例进行声明式编程
- 通过切面和模板减少样板式代码

	
refresh
---

### prepareRefresh();

initPropertySources();

留给子类扩展
```
public class MyClassPathXmlApplicationContext extends ClassPathXmlApplicationContext {


    public MyClassPathXmlApplicationContext(String... configLocations){
        super(configLocations);
    }

    @Override
    protected void initPropertySources() {
        System.out.println("扩展initPropertySource");
        //这里添加了一个name属性到Environment里面，以方便我们在后面用到
        getEnvironment().getSystemProperties().put("name","bobo");
        //这里要求Environment中必须包含username属性，如果不包含，则抛出异常
        getEnvironment().setRequiredProperties("username");
    }
}

```

getEnvironment().validateRequiredProperties();

验证必要的属性是否已经设置


this.earlyApplicationEvents = new LinkedHashSet<ApplicationEvent>();



ConfigurableListableBeanFactory beanFactory = obtainFreshBeanFactory()

prepareBeanFactory(beanFactory)

postProcessBeanFactory(beanFactory)
用于扩展，子类继承重写该方法可获取beanFactory对象，对其进行一些前置操作

registerBeanPostProcessors(beanFactory)

initApplicationEventMulticaster()

- addApplicationListener
- addApplicationListenerBean
- void multicastEvent(ApplicationEvent event);

onRefresh()
子类实现

registerListeners()

finishBeanFactoryInitalization(beanFactory)

finishRefresh();

AbstractApplicationContext
---
MESSAGE_SOURCE_BEAN_NAME = "messageSource"
LIFECYCLE_PROCESSOR_BEAN_NAME = "lifecycleProcessor"
APPLICATION_EVENT_MULTICASTER_BEAN_NAME = "applicationEventMulticaster"


springboot启动流程
---

SpringBootAppliction注解
```
@Target
@Retention
@Documented
@Inherited
@SpringBootConfiguration // 继承了Configuration，表示当前是注解类
@EnableAutoConfiguration // 开启springboot的注解功能，springboot的四大神器之一，其借助@import的帮助
@ComponentScan(excludeFilters = { // 扫描路径设置（具体使用待确认）
@Filter(type = FilterType.CUSTOM, classes = TypeExcludeFilter.class),
@Filter(type = FilterType.CUSTOM, classes = AutoConfigurationExcludeFilter.class) })

```

springboot启动的时候会利用SPI原理找到 EventPublishingRunListener SpringApplicationRunListeners 启动监听并发射starting事件
接着是处理启动参数封装成ApplicationArguments，这里等下展开 -- todo

配置spring.beaninfo.ignore configureIgnoreBeanInfo(environment); 这个

打印Banner

创建上下文，一般我们常用的是AnnotationConfigServletWebServerApplicationContext todo 几个有什么区别


刷新容器 展开


1、创建SpringApplication，准备引导器、初始化器和应用监听器
```
	public SpringApplication(ResourceLoader resourceLoader, Class<?>... primarySources) {
		// 读取配置的吧
		this.resourceLoader = resourceLoader;
		Assert.notNull(primarySources, "PrimarySources must not be null");
		this.primarySources = new LinkedHashSet<>(Arrays.asList(primarySources));
		// 推测出web容器类型
		this.webApplicationType = WebApplicationType.deduceFromClasspath();

		// SPI 获取bootstrapRegistryInitializers 
		// private List<BootstrapRegistryInitializer> bootstrapRegistryInitializers
		this.bootstrapRegistryInitializers = getBootstrapRegistryInitializersFromSpringFactories();
		//private List<ApplicationContextInitializer<?>> initializers;
		setInitializers((Collection) getSpringFactoriesInstances(ApplicationContextInitializer.class));
		// private List<ApplicationListener<?>> listeners;
		setListeners((Collection) getSpringFactoriesInstances(ApplicationListener.class));
		this.mainApplicationClass = deduceMainApplicationClass();
	}
```
1.1、new SpringApplication(primarySources).run(args);
1.2、DefaultBootstrapContext bootstrapContext = new DefaultBootstrapContext();
1.3、this.bootstrapRegistryInitializers.forEach((initializer) -> initializer.initialize(bootstrapContext));
1.4、SpringApplicationRunListeners listeners = getRunListeners(args);
2、运行SpringApplication

2.1获取运行监听器。这个监听器在启动过程中会一直监听各种事件，如准备环境完成，容器完成，异常等等
SpringApplicationRunListeners listeners = getRunListeners(args);

2.2准备环境
ConfigurableEnvironment environment = prepareEnvironment(listeners, bootstrapContext, applicationArguments);
2.3 容器创建
context = createApplicationContext();
2.4 准备容器基本信息
prepareContext(bootstrapContext, context, environment, listeners, applicationArguments, printedBanner);
2.5 刷新容器（spring启动原理，核心是创建所有单实例bean，详情见Spring1–IOC）
refreshContext(context);
2.6 运行监听器.start
2.7 Runner.run
2.8 运行监听器.run(或者过程中异常就.failed)

#### 在启动的过程中通过spi ioc 实现了功能的可插拔，比如Logging Systems

log
---
SPI
# Logging Systems
org.springframework.boot.logging.LoggingSystemFactory=\
org.springframework.boot.logging.logback.LogbackLoggingSystem.Factory,\
org.springframework.boot.logging.log4j2.Log4J2LoggingSystem.Factory,\
org.springframework.boot.logging.java.JavaLoggingSystem.Factory



Spring Boot、Spring MVC、Spring有什么区别
---
Spring框架就想一个家族，有众多的衍生产品例如boot、security、jpa等等；他们的基础都是Spring的ioc和aop，ioc提供了依赖注入的容器，aop提供了面向切面编程的功能，然后在此基础上实现了其他衍生产品的高级功能。

Spring MVC提供了一种轻度耦合的方式来开发web应用；它是Spring的一个模块，是一个web框架；通过DispatcherServlet, ModelAndView 和 View Resolver，开发web应用变得很容易；解决的问题领域是网站应用程序或者服务开发——URL路由、Session、模板引擎、静态Web资源等等

Spring Boot实现了auto-configuration自动配置（另外三大神器actuator监控，cli命令行接口，starter依赖），降低了项目搭建的复杂度。它主要是为了解决使用Spring框架需要进行大量的配置太麻烦的问题，所以它并不是用来替代Spring的解决方案，而是和Spring框架紧密结合用于提升Spring开发者体验的工具；同时它集成了大量常用的第三方库配置(例如Jackson, JDBC, Mongo, Redis, Mail等等)，Spring Boot应用中这些第三方库几乎可以零配置的开箱即用(out-of-the-box)

Spring 是一个“引擎”;


Spring MVC 是基于Spring的一个 MVC 框架;


Spring Boot 是基于Spring4的条件注册的一套快速开发整合包。


### 麻烦讲一下springboot启动流程
好的，首先springboot是一个开箱即用的后台开发框架，他的启动过程主要包括初始化ioc容器已经web容器。
SpringBoot启动方法在SpringApplication类中的run方法
run方法里面首先进行了一些准备和初始化工作，包括记录启动时间打印banner信息，通过spi的方式读取spring.factories中的接口实现类创建和启动监听器，加载环境变量、配置容器参数。然后是创建ApplicationContext容器根据类型创建IOC容器。创建完容器接来下就是prepareContext()这一步也很关键，这一步读取我们配置的bean信息并解析成beandefinition对象，存放在一个map中，为之后创建bean实例提供各种属性信息。
根据当前最后是刷新容器然后通知监听器启动成功

如果想要在容器启动过程中进行扩宽spring也提供了相当多的扩展方法，

### 麻烦讲一下AOP
AOP是面向切面编程，可以说是OOP面向对象编程的补充和完善。AOP的关键单元是切面
AOP让你可以使用简单可插拔的配置，在核心逻辑之前之前，之后或周围动态添加横切关注点，让代码在变的易于维护
可以使用AspectJ注解风格或使用Spring XML配置风格、

jdk 代理
cglib 代理





















