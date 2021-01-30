## GCC
编译过程：预编译（preprocessing）、编译（compiling）、汇编（assembing）、链接（linking）  
预处理器cpp、汇编器as、连接器ld
### 预处理
-E选项保留预处理文件 -o选项导出到某个输出文件
```
gcc -E -o circle.i circle.c
```
-C 选项阻止预处理器删除源文件和头文件中的注释  
#### 常用选项
- -Dname[=definition] 
搭配源代码中的#ifdef name命令使用，可以实现条件式编译，如果没有指定一个替换的值，该宏被定义为值1
- -Uname
- -Idirectory[: directory[...]] 
- -iquote directory[:directory[...]]

## makefile
make命令执行时吗，需要一个Makefile文件，以告诉make命令需要怎么样的去编译和链接程序   
**示例** 
8个c文件3个头文件我们要写一个makefile来告诉make命令如何编译和链接这几个文件。  
1. 如果这个工程没有编译过，那么我们的所有c文件都要编译并被链接。
2. 如果这个工程的某几个c文件被修改，name我们只编译被修改的c文件，并链接目标程序。
3. 如果这个工程的头文件被修改了，那么我们需要编译引用了这几个头文件的c文件，并链接目标程序  
   
### makefile规则
```
target ...:prerequistes ...
	command
	...
	...
```
**target** 
可以是一个object file（目标文件） ，也可以是一个执行文件，还可以是一个标签（lable）。对于标签这种特性，在后续的”伪目标“章节中会有叙述  
**prerequistisites**
生成target所依赖的文件和/或target  
**command** 
改target要执行的命令（任意的shell命令） 
tartget这个或多个的目标文件依赖于prerequisites中的文件，其生成规则定义在command中  
`也就是说prerequisites中如果有一个以上的文件比target文件要新的话，command所定义的命令就会被执行` 


### 一个示例

```
edit :main.o kbd.o command.o display.o \
		insert.o search.o files.o utils.o
	cc -o edit main.o kbd.o files.o utils.o
main.o : main.c defs.h
	cc -c main.c
kbd.o : kbd.c defs.h command.h
	cc -c kbd.c
command.o : mannand.c defs.h command.h
	cc -c command.c
display.o : insert.c defs.h buffer.h
	cc -c display.c
insert.o : insert.c defs.h buffer.h
	cc -c insert.c
search.o : insert.c defs.h buffer.h
	cc -c search.c
files.o : files.c defs.h buffer.h
	cc -c files.c
utils.o : utils.c defs.h
	cc -c utils.c
clean :
	rm edit main.o kbd.o command.o display.o \
	 insert.o search.o files.o utils.o
```
内容保存在Makefile文件中然后再该目录下直接输入命令make就可以生成执行文件edit。  
如果要删除执行文件和所有的中间目标文件，那么，只要执行make clean就可以了。  
目标文件：执行文件edit和中间目标文件（*.o)  
依赖文件：就是冒号后面的那些.c 和 .h文件。依赖关键说明了目标文件是由哪些文件生成的。  
定义好依赖关系以后，后续一行定义了如何生成目标文件操作系统命令，一定要以一个Tab键开头。**make 会比较target文件和prerequisties文件的修改日期** 如果prerequisites文件的日期要比targets文件的日期要新，或者target不存在的话，那么，make就会执行后续定义的命令。    

需要说明的是clean不是一个target 他只是一个动作的名字，有点像c语言的lable一样，其冒号后面什么都没有，那么make就不会去找他的依赖性，也就不会自动执行后面的命令。要执行其后的命令，就要在make命令后明显的指出这个label的名字。  
我们可以在一个makefile中定义不用的编译或者是和编译无关的命令，如程序的打包，程序的备份等。  
### make是如何工作的
1. make会在当前目录下找Makefile或makefile文件
2. 如果找到，他会找文件中的第一个目标文件（target），例子中的edit，并把这个文件作为最终的目标文件。
3. 如果edit文件不存在或者edit所依赖的.o文件的修改时间比edit这个文件新，那么，他会执行后面所定义的命令来生成edit这个文件。
4. 如果edit所依赖的.o文件也不存在。那么make会在当前文件中找目标为.o文件的依赖性，如果找到再根据那一个规则生成.o文件。
5. 当然，你的C文件和H文件是存在的，于是make会生成.o文件，然后再用.o 文件生成make的终极任务，也就是edit。

make会一层一层去找依赖性，知道最终编译出第一个目标文件。
### makefile中使用变量
声明一个变量
```
objects = main.o kbd.o command.o display.o \
	insert.o search.o files.o utils.o
```
于是我们可以很方便的在我们的makefile中以$(object) 的方式来使用这个变量，
```
objects = main.o kbd.o command.o display.o \
	insert.o search.o files.o utils.o
edit : $(object) 
	cc -o edit $(object) 
clean : 
	rm edit $(objects)
```
### 让make自动推导
自动推导文件以及文件依赖关系后面的命令，于是没必要每个.o文件后面写上类似的命令。  
可以让make自动识别，并自己推导命令，
make看到.o文件，会自动把.c文件加在依赖关系中，并且cc -c 命令也会推导出来
```
objects = main.o kbd.o command.o display.o \
    insert.o search.o files.o utils.o

edit : $(objects)
    cc -o edit $(objects)

main.o : defs.h
kbd.o : defs.h command.h
command.o : defs.h command.h
display.o : defs.h buffer.h
insert.o : defs.h buffer.h
search.o : defs.h buffer.h
files.o : defs.h buffer.h command.h
utils.o : defs.h

.PHONY : clean
clean :
    rm edit $(objects)
```

这种方法也就是make的”隐晦规则“。上面的文件内容中，.PHONY表示clean是个伪目标文件

### 另类的makefiles
```
objects = main.o kbd.o command.o display.o \
    insert.o search.o files.o utils.o

edit : $(objects)
    cc -o edit $(objects)

$(objects) : defs.h
kbd.o command.o files.o : command.h
display.o insert.o search.o files.o : buffer.h

.PHONY : clean
clean :
    rm edit $(objects)
```
### makefile里有什么
1. 显示规则。
2. 隐晦规则。
3. 变量的定义。
4. 文件指示。包括三部分，一个是在Makefile中引用另一个Makefile；另一个是根据某些情况制定Makefile中有效部分；还有就是顶一个多行的命令。
5. 注释。
注意命令，必须以Tab键开始
### make的工作方式

1. 读入所有的makefile
2. 读入被include的其他makefile
3. 初始化文件中的变量。
4. 推导隐晦规则，并分析所有规则
5. 为所有的目标文件创建依赖关系链
6. 根据依赖关系，决定哪些目标需要重新生成。
7. 执行生成命令
## 书写规则
 规则包含两个部分，一个是依赖关系，一个是生成目标的方法。  
```
target : prerequisties
	command
	...

target : prerequistes ; command
	command
	...
```
### 在规则中使用通配符
make支持三个通配符：*, ? 和 ~
### 文件搜索
在一些大工程中，有大量的源文件，我们通常的做法是把这许多的源文件分类，并存放在不同的目录中。所以，当make需要去找寻文件的依赖关系时，你可以在文件中加上路径，但最好的方法是吧一个路径告诉make，让make在自动去找。

Makefile文件中的特殊变量VPATH就是完成这个功能的，没有这个变量make只会在当前目录中去找寻依赖文件和目标文件。如果定义了这个变量，那么make就会在当前目录找不到的情况下，到所指定的目录中寻找文件。
```
VPATH = src:.../headers
```
路径由冒号分割（当前目录永远是最高优先搜索的地方） 

另一个设置文件搜索路径的方法是使用make的vpath关键字（注意是小写）不是变量时关键字使用方式有三种  
**vpath <pattern> <directories>**   
为符合模式的文件指定搜索目录  
**vpath <pattern>** 
清除符合模式的文件的搜索目录  
**vpath**   
清除所有已被设置好了的文件搜索目录。  
### 多目标
```
bigoutput littleoutput : text.g
	generate text.g -$(subst output,,$@) > $@
```
上诉规则等价于：
```
bigoutput : text.g
	generate text.g -big > bigoutput
littleoutput : text.g
	generate text.g -little > littleoutput
```

### 静态模式
```
<target ...> : <target-pattern> : <prereq-patterns ...>
	<command>
	...
```
target 定义了一系列的目标文件，可以有通配符。是目标的一个集合。  
target-pattern是指明了target的模式，也就是目标集模式
prereq-pattern是目标的依赖模式，他对target-pattern形成的模式再进行一次依赖目标的定义。  

### 目标专用的变量赋值
target_list: [override]assigment
## A simple Makefile Tutorial 
Makefile are a simple way to origanize code compilation.  

**Makefile1** 
```
hellomake: hellomake.c hellofunc.c
     gcc -o hellomake hellomake.c hellofunc.c -I.
```
**Makefile2** 
```
CC=gcc
CFLAGS=-I.
hellomake: hellomake.o hellofunc.o
	$(CC) -o hellomake hellomake.o hellofunc.o
```
**Makefile 3** 
```
CC=gcc
CFLAGS=-I.
DEPS = hellomake.h
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
hellomake: hellomake.o hellofunc.o
	$(CC) -o hellomake hellomake.o hellofunc.o

```
**Makefile 4** 
```
CC=gcc
CFLAGS=-I.
DEPS=hellomake.o hellofunc.o
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(FLAGS)
hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
```
**Makefile 5** 
```
IDIR=../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LIBS=-lm
_DEPS=hellomake.h
DEPS=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
hellomake: $(OBJ)
	$(CC) -o $@ $^ S(CFLAGS) $(LIBS)
.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

```
So now you have a perfectly good makefile that you can modify to manage small and medium-sized software projects.You can add multiple rules to a makefile;you can even creat rules that call other rules.

