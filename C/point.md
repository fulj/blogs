## void 指针 
void指针指向void的指针是类型为void * 的指针。因为没有对象的类型是void，所以void * 称为万能指针。可以代表任何对象的指针，但不代表该对象的类型，若想获取内存中该对象的值需要将void指针转换为合适的对象指针。
```
void *memset(void *s, int c, size_t n);
struct Data {
/* ... */ record
}
memset(&record, 0, sizeof(record));
```
memset()将c的值赋值到从地址s开始的n个内存字节中。  
下面的调用会将0赋值到结构变量的record中的每个字节。  
实参&record具有struct Data * 类型。在调用过程中实参被转化成形参类型，即void *。
```
int * iPtr = malloc(1000 * sizeof(int))
```
编译器会在必要的地方把void指针转化为对象指针。例如 malloc返回一个void指针，然后再转换成int指针。  
## 初始化指针
具有动态存储周期的指针变量，开始是没有定义值的，除非他们声明同时进行显示的初始化。在语句块中定义的所有变量，只要没有被声明为static，就具有动态存储周期。所有指针在定义时如果没有初始化，则空指针默认作为他们的初始化值。  
指针如果不具有动态存储周期，则必须用常量表达式来初始化，例如取址运算的结果，或使用数据或函数名称。  
## 使用指针读取与修改变量
间接运算符*生成内存中的位置，该位置的地址存储在一个指针中。如果ptr是一个指针，那么\*ptr就是ptr所指向的对象（或函数）。也称解引用(dereferencing)一个指针。指针指向的内存位置被认为存储着一个对象，指针的类型决定了对象的类型。
```
double x,y, *ptr;
ptr = &x;
*ptr = 7.8;
*ptr *= 2.5;
y = *ptr + 0.5;
```
ptr具有double * 类型（读为”指向double的指针“）。因此，表达式*ptr 类型是double。间接运算符*必须匹配一个具有有效地址的指针。  
一个指针变量，其本身也是内存中的一个对象，也就是说，其他指针可以指向该指针。若想创建指向指针的指针，必须使用两个星号。
```
char c = 'A', *cPtr = &c, **cPtrPtr = &cPtr
```
*cPtrPtr生成char指针cPtr，**cPtrPtr的值是char变量c
```
#include <stdio.h>
typedef struct{
	long key;/* ... */
} Record;

_Bool newRecord(Record **ppRecord)
{
	*ppRecord = malloc(sizeof(Record));
	if(*ppRecord != NULL)
{
	return 1;
}
else
	return 0;
}
```
## 修改和比较指针  

除了使用赋值操作让一个指针引用一个给定的对象或函数，也可以使用算术运算符来修改一个对象指针。当进行指针算术运算(pointer arithmetic)，编译器会自动在运算中采用指针所指类型的空间大小。  

- 对一个指针执行整数加法和减法操作。
- 两个指针相减
- 比较两个指针
## 数组和指针的区别
初始化字符数组来存储字符串和初始化指针来指向字符串有何区别
*a  
### 指向函数的指针
声明函数指针  
```
double (*funcPtr)(double, double);
```
```
double result;
funcPtr = pow;

result = (*funcPtr)(1.5, 2.0);
result = funcPtr(1.5, 2.0);
```
如本例最后一行所示，当使用指针调用函数时可以不用间接运算符，因为函数调用运算符的左操作数具有函数指针类型

