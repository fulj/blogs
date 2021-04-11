- resourceLoader
- beanNameGenerator
- ApplicationContextInitializer
- ApplicationListener
- allowBeanDefinitionOverriding
- lazyInitialization
-
Aware 接口
---
BeanClassLoaderAware
void setBeanClassLoader(ClassLoader classLoader);

```
public ConfigurableApplicationContext run(String... args) {
		StopWatch stopWatch = new StopWatch();
		stopWatch.start();
		ConfigurableApplicationContext context = null;
		Collection<SpringBootExceptionReporter> exceptionReporters = new ArrayList<>();
		configureHeadlessProperty();
		// SpringApplicationRunListener spring.factor 文件中配置
		SprkingApplicationRunListeners listeners = getRunListeners(args);
		listeners.starting();// 通知监听器 starting
		try {
			ApplicationArguments applicationArguments = new DefaultApplicationArguments(args);
			// 根据pom文件的获取environment SERVLET new StandardServletEnvironment()
			ConfigurableEnvironment environment = prepareEnvironment(listeners, applicationArguments); // 监听器 environmentPrepared 事件
			configureIgnoreBeanInfo(environment);
			Banner printedBanner = printBanner(environment);
			context = createApplicationContext();
			exceptionReporters = getSpringFactoriesInstances(SpringBootExceptionReporter.class,
					new Class[] { ConfigurableApplicationContext.class }, context);
			prepareContext(context, environment, listeners, applicationArguments, printedBanner);
			refreshContext(context);
			afterRefresh(context, applicationArguments);
			stopWatch.stop();
			if (this.logStartupInfo) {
				new StartupInfoLogger(this.mainApplicationClass).logStarted(getApplicationLog(), stopWatch);
			}
			listeners.started(context); // 通知监听器 started
			callRunners(context, applicationArguments);
		}
		catch (Throwable ex) {
			handleRunFailure(context, ex, exceptionReporters, listeners); // 启动失败通知监听器 failed
			throw new IllegalStateException(ex);
		}

		try {
			listeners.running(context); // 通知监听器 running spring启动成功
		}
		catch (Throwable ex) {
			handleRunFailure(context, ex, exceptionReporters, null);
			throw new IllegalStateException(ex);
		}
		return context;
	}
```
SpringApplocationRunListeners
- log
- Listeners
