#include<stdlib.h>
//标准库函数头文件，包含malloc()、free()、rand()等
#include<stdio.h>
//标准输入输出头文件，包含printf()、scanf()

#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4 //不存在
#define Duplicate 5 //重复


typedef int ElemType;
typedef int Status;
//为数据类型int起别名，便于理解
