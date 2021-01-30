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

