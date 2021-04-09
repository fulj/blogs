适配器模式
---
1. 类适配器 继承
2. 对象适配器 包装
3. 缺省适配模式 制造一个抽象类，给出所有方法的平庸的具体实现，这样从这个类继承下去的子类就不必实现所有的方法了	

### 优点
1. 更好的复用性和扩展性
### 缺点
过多的使用适配器，会让系统非常零乱，不易整体进行把握。比如，看到的是A接口，内部实现却是B接口的实现。因此如果不是很有必要，可以不适用适配器，而是直接对系统进行重构。

策略模式
---
策略模式不是如何实现算法，而是如何组织、调用这些算法

### 公有的行为
所有具体策略类都有的一些公有的行为，把这些公有的行尾放到共同的抽象策略类里面。当然这时候抽象策略类必须要用Java抽象类实现，而不能使用接口。

### 优点
1. 策略类的等级结构定义了一个算法或行为族。恰当使用继承可以把公共的代码移到父类里面，从而避免代码重复。
2. 避免使用多重条件(if-else)。多重条件语句不易维护
### 缺点
1. 客户端必须知道所有的策略类，并自行决定使用哪一个策略类。意味着客户端必须理解这些算法的区别，以便适时选择恰当的算法类。换言之，策略模式只适用于客户端知道算法或行为的情况。
2. 由于策略模式把每个具体的策略实现都单独封装成类，如果备选策略很多的话，那么对象的数目就会很可观。

桥梁模式
---
熟悉这个模式对于理解面向对象的设计原则，包括“开-闭”原则以及组合/聚合复用原则都很有帮助，理解好这两个原则有助于形成正确的设计思想和培养良好的设计风格。
桥梁模式的用意是“将抽象化(Abstraction)与实现化(Implementation)脱耦，使得两者可以独立的变化”。

- 抽象化
- 实现化
- 脱耦 
脱耦就是指在一个软件系统中抽象化和是鲜花之间使用聚合关系而不是继承关系，从而两者可以相对独立的变化。这就是桥梁模式的用意。

调停者模式
---
- 抽象调停者
- 具体调停者
- 抽象同事类
- 具体同事类
一个好的面向对象的设计可以使对象之间增加协作性，减少耦合度。一个深思熟虑的设计会把一个系统分解为一群相互写作的对象，然后给每一个对象以独特的责任，恰当的配置他们之间的写作关系，使他们可以一起工作。

### 优点
- 松耦合
- 集中控制交互
- 多对多变为1对多
### 缺点
调停者模式的缺点是，过度的集中化。如果同事对象的交互非常多，而且比较复杂，当这些复杂性全面集中到调停者的时候，会导致调停者对象变得十分复杂，而且难于管理和维护。

解释器模式
---
- 抽象表达式
- 终结符表达式
- 非终结符表达式
- 环境角色


访问者模式
---
- 抽象访问者
- 具体访问者
- 抽象节点
- 具体节点
- 结构对象