1. 自动化管理重要数据
   - 查询日志文件、追踪流量、监控使用者使用主机状态、主机各项硬件设备状态、主机软件更新查询
   
2. 追踪与管理系统的重要工作
3. 简单入侵侦测功能
4. 连续指令单一化
5. 简易的数据处理
6. 跨平台支持与学习历程较短

There are various operators supported by each shell.
- Arithmetic Operators
- Relational Operators
- Boolean Operators
- String Operators
- File Test Operators

Boutne shell didn't originally have any mechanism to perform simple arithmetic operations but it uses external programs, either **awk or expr**

The following example shows how to add two numbers 
```
#!/bin/sh
val=`expr 2+2`
echo "Total value: $val"
```
```
$ ./test.sh
Total value : 4
```
The follwing points need to be considered while coding  
- 2+2 is not correct; it should be written as 2 + 2.
- The complete expression should be enclosed between ``, called the backtick.

Arithmetic Operators
---
Assume variable a holds 10 and variable b holds 20 then show example

| Operator          | Description | Example                        |
| ----------------- | ----------- | ------------------------------ |
| +(Addition)       |             | `expr $a + $b` will give 30    |
| -(Subtraction)    |             | `expr $a - $b` will give 10    |
| *(Multiplication) |             |                                |
| /(Division)       |             |                                |
| %(Modulus)        |             |                                |
| =(Assignment)     |             |                                |
| ==(Equality)      |             | [ $a == $b ] will return false |
| !=(Not Equality)  |             | [ $a != $b ] will return true  |

It is very important to understand that all the conditional expressions should be inside square around them for example [ $a == $b ] is correct whereas, [$a==$b] is incorrect.
 
Relational Operators
---
| Operator | Description | Example                   |
| -------- | ----------- | ------------------------- |
| -eq      |             | [ $a -eq $b ] is not true |
| -ne      |             | [ $a -ne $b ] is true     |
| -gt      |             | [ $a -gt $b ] is not true |
| -lt      |             | [ $a -lt $b ] is true     |
| -ge      |             |                           |
| -le      |             |                           |

Boolean Operator
---
| Operator | Description         | Example                              |
| -------- | ------------------- | ------------------------------------ |
| !        |                     | [ !false ] is true                   |
| -o       | This is logical OR  | [ $a -lt 20 -o $b -gt 100 ] is true  |
| -a       | This is logical AND | [ $a -lt 20 -a $b -gt 100 ] is false |

String Operator
---
Assume variable a holds "abc" and variable b holds "efg" then -   
Show Examples  
| Operator | Description                                                                 | Example                 |
| -------- | --------------------------------------------------------------------------- | ----------------------- |
| =        |                                                                             | [ $a = $b ] is not true |
| !=       |                                                                             | [ $a != $b ] is true    |
| -z       | Checks if the given string operand size is zero                             | [ -z $a ] is not true   |
| -n       | Checks if the given string operand size is non-zero                         | [ -n $a ] is not false  |
| str      | Checks if str is not the empty string; if it is empty;then it returns false | [ $a ] is not false     |

File Test Operators
---
