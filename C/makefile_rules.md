## 自动变量
- $@ 目标文件名
- $* 目标文件名的词干，也就是模式规则中%锁代表的部分
- $< 第一个依赖条件
- $^ 依赖条件列表，排除了重复元素。
- $? 比目标新的依赖条件列表
- $+ 依赖条件的完整列表，包括重复元素	
- \$% 如果目标是一个链接库成员，变量\$%会生成成员名称，不带有链接库文件名。而$@生成链接库文件名。

## 规则
**例1.1一个基本的makefile** 
```
CC=gcc
CFLAGS=-Werror -std=c99
LDFLAGS=-lm
circle: circle.o circulararea.o
	$(CC) $(LDFLAGS) -o $@ $^

circle.o : circle.c
	$(CC) $(CFLAGS) -o $@ -c $<

circulararea.o: circularare.c
	$(CC) $(CFLAGS) -o $@ -c $<
```
**执行命令** 
```
$ make -n -f Makefile19-1 circle

gcc -Wall -g -std=c99 -o circle.o -c circle.c
gcc -Wall -g -std=c99 -o circularare.o -c circulararea.c
gcc -lm -o circle circle.o circulararea.o
```
选项-n会输出执行的命令，当测试makefile时，该选项是不可或缺的。
## 模式化规则
通过模式化规则例1.1中最后两条规则可以用一下一条简单的规则替换
```
circulararea.o circle.o: %.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
```
模式规则一般语法
```
[target_list:] target_pattern:prerequistie_pattern
	[command-script]
```
**必须保证target_list中每个目标都匹配target_pattern** 不然make会报错
- 如果包含显式列表target_list那么该规则就是静态规则(static pattern rule)
- 如果省略了target_list那么称为隐式规则(implicit rule)，并且只要目标名称与target_pattern匹配,规则就会被应用到这个目标。  
例:
```
%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<
```
可以对某个对象显式处理，make会对显式的列入的目标应用静态规则，其他所有.o采用隐式规则。同样任一对象文件的隐式依赖条件不存在时，make会中止报错。
## 内置规则
不必告诉make如何进行标准操作，例如，把C源代码编译成对象文件；make对此有内置的默认规则，对别的标准操作也是如此。
**利用内置规则的makefile** 
```
CC=gcc
CFLAGS=-Werror -std=c99
OBJS=circle.o circulararea.o
circle: $(OBJS) -lm
```
执行命令
```
$ touch *.c; make circle

gcc -Werror -std=c99 -c -o circle.o circle.c
gcc -Werror -std=c99 -c -o circulararea.o circulararea.c
gcc circle.o circulararea.o /usr/lib/libm.so -o circle
```
在运行make时候加上-p选项，可以显示make的内置规则
## 变量
make采用一个规则时，他会计算包括目标，依赖条件和命令中的变量，GUN make中的变量有两种
- 递归展开(recursively expanded) 
	- 展开时，嵌套的变量引用都被存储下来直到变量的值被计算出来 
	- 赋值运算符为=
	```
	DEBUGFLAGS=$(CFLAGS) -ggdb -DDEBUG -Oo
	# make会逐字存储等号右边的字符序列；一直到在使用$(DEBUGFLAGS)时，
	嵌套的变量$(FLAGS)才会被展开
	```
	
- 简单展开(simple expanded)
	- 变量的引用会在赋值时立刻展开，并保存下来 
	- 赋值运算符为:=
	```
	OBJ=circle.o circulararea.o
	TESTOBJ := $(OBJ) profile.o
	# 直接展开，后续如果OBJ的值改变也不会影响TESTOBJ的值
	```
	
在命令中定义变量
```
$ make CFLAGS=-ffinite-math-only circlararea.o
# 命令中的变量会被makefile中带有override关键字的赋值操作所屏蔽
override CPPLFAGS=-DEBUG

```
**+=附加运算符（append operator)**    
将更多字符附加到一个变量现有值的后面  
**?= 条件赋值（condition assignment）**  
仅当变量本来没有值的情况下，才执行操作。
### 变量和空白符
### 目标专用的赋值变量
