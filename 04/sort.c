#include<stdio.h>		//标准输入输出库
#include<stdlib.h>		//内含随机函数
#include<time.h>		//内含时间函数，用以优化随机数的生成


typedef int KeyType;	//关键字类型定为int型
typedef char DataType;	//其它数据内容定为char型
typedef int BOOL;

#define CASES	5		//算法个数
#define MAXSize 500     //关键字个数
#define TRUE 1
#define FALSE 0
#define TESTNUM 100	//测试次数

typedef struct entry{
	KeyType key;
	DataType data;
}Entry;
typedef struct list{
	int n;
	Entry D[MAXSize];
}List;




//公用函数
void Swap(List* list, int m, int n)				//与书本不同
{
	Entry temp;
	if(m != n){
		temp = list->D[m];
		list->D[m] = list->D[n];
		list->D[n] = temp;
	}
	return;
}

//简单选择排序SelectSort(与书本不同)
int FindMin(List list, int startIndex)
{
	int i,temp;
	for(i = startIndex, temp = startIndex; i<list.n; i++){
		if(list.D[temp].key > list.D[i].key) temp = i;
	}
	return temp;
}
void SelectSort(List* list)
{
	int i,startIndex;
	for(i = 0, startIndex = 0; i < list->n-1; i++, startIndex++)  Swap(list, i, FindMin(*list,startIndex));
	return;
}


//直接插入排序
void InsertSort(List* list){
	int i,j;
	Entry insertItem;
	for(i = 1; i< list->n; i++){
		insertItem = list->D[i];
		for(j = i-1; j >= 0; j--){
			if(insertItem.key < list->D[j].key) list->D[j+1] = list->D[j];
			else break;
		}
		list->D[j+1] = insertItem;
	}
	return;
}


//冒泡排序
void BubbleSort(List *list){
	int i, j;
	for(i = list->n-1; i > 0; i--){
		BOOL isSwap = FALSE;
		for(j = 0; j < i; j++){
			if(list->D[j].key > list->D[j+1].key){
				Swap(list, j, j+1);  //Swap()与书本不同
				isSwap  = TRUE;
			}
		}
		if(!isSwap) break;			//如果本趟没有交换元素，则排序完成。
	}
}


//快速排序算法
int Partition(List* list, int low, int high){
	int i=low, j=high+1;
	Entry pivot = list->D[low];
	do{
		do{i++;}while(i<=high  &&  list->D[i].key < pivot.key);
		do{j--;}while(i>=low  && list->D[j].key > pivot.key);
		if(i < j) Swap(list, i, j);		//Swap()与书本不同
	}while(i < j);
	Swap(list, low, j);
	return j;
}
void quickSort(List *list, int low, int high){
	int k;
	if(low < high){
		k = Partition(list, low, high);
		quickSort(list, low, k-1);
		quickSort(list, k+1, high);
	}
}
void QuickSort(List* list){
	quickSort(list, 0, list->n-1);
}


//两路合并算法
void Merge(List* list, Entry* temp, int low, int n1, int n2) {
	int i = low, j = low + n1;
	while (i <= low + n1 - 1 && j <= low + n1 + n2 - 1) {
		if (list->D[i].key <= list->D[j].key)
			*temp++ = list->D[i++];
		else *temp++ = list->D[j++];
	}
	//将剩余的添加进去，分为剩余D[i]序列或者D[j]序列
	while (i <= low + n1 - 1)
		*temp++ = list->D[i++];
	while (j <= low + n2 + n1 - 1)
		*temp++ = list->D[j++];
}
void MergeSort(List* list){
	Entry temp[MAXSize];
	int low, n1, n2, i, size = 1;
	//当剩余序列树大于1 <=> 序列大小size小于总数
	while(size < list->n){
		low = 0;
		//当存在一对序列时，合并
		while(low + size < list->n){
			n1 = size;
			//判断这对序列中后者的长度是否为size
			if(low +size*2 < list->n) n2 = size;
			else n2 = list->n-low-size;
			Merge(list, temp+low, low, n1, n2);
			low += n1 + n2;
		}
		//更新一次D[]数组顺序
		for(i = 0; i < low; i++)  list->D[i] = temp[i];
		//准备下一次合并
		size *= 2;
	}
}



//C语言随机数生成教程：
//http://c.biancheng.net/view/2043.html
//https://blog.csdn.net/qq_44620773/article/details/103985380

//结构体初始化报错原因：
//https://www.cnblogs.com/Fsiswo/p/9291458.html

//记录函数运行时间的方法：
//https://blog.csdn.net/y_dd6011/article/details/86408339

//若想将测试用时转换成s，使用CLK_TCK，说明如下：
//https://baike.baidu.com/item/CLK_TCK/2766625?fr=aladdin



int main(){
	List* list = (List*)malloc(sizeof(List));	//使用结构体指针需要分配空间，普通变量List list则不用。
	int i,j,k;		//循环用数
	int rnum;	//随机数载体
	clock_t start, stop;	//clock_t是clock()函数返回的变量类型 
	double duration;		//记录被测试函数运行的时间，以秒为单位

	//初始化
	list->n = MAXSize;
	printf("#define MAXSize %d\n#define TESTNUM %d\n",MAXSize,TESTNUM);
	

	//测试用时
	for(i = 1; i <= CASES; i++){
		//初始化
		srand((unsigned)time(NULL));//把它放到下面for(k)循环中试一下/坏笑

		start = clock();
		//重复生成随机数运行测试结果
		for (j=0; j<TESTNUM; j++){
			for(k = 0; k < list->n; k++){
				rnum = rand();
				list->D[k].key = rnum;

				//printf("%d\t",list->D[k].key);
				//if(!((k+1)%10)) printf("\n\n");			//!比%优先级高，记得加括号

				//这很可能是一个彩蛋
				//if(k%3 == 1)	list->D[k].data = rnum%2? 90:122;
				//else if(k%3 == 2)	list->D[k].data = rnum%2? 88:120;
				//else	list->D[k].data = rnum%2? 76:108;
			}
			switch(i){
				case 1: SelectSort(list); break;
				case 2: InsertSort(list); break;
				case 3: BubbleSort(list); break;
				case 4:  QuickSort(list); break;
				case 5:  MergeSort(list); break;
			}
		}
		stop = clock();

		duration =((double)(stop - start))/TESTNUM; //可以再除一个CLK_TCK，把单位从ms变成s
		switch(i){
			case 1: printf("\nSelectSort:\n"); break;
			case 2:	printf("\nInsertSort:\n"); break;
			case 3: printf("\nBubbleSort:\n"); break;
			case 4:  printf("\nQuickSort:\n"); break;
			case 5:  printf("\nMergeSort:\n"); break;
			}
		printf("ticks = %f\n", (double)(stop - start));
		//printf("duration = %6.2e\n", duration);

		//输出一下彩蛋吧
		//printf("\n神秘字符：\n");
		//for(k = 0; k < list->n; k++) printf("%c",list->D[k].data);
		//输出排序后结果
		//printf("\n\n排序后：\n");
		//for(k = 0; k < list->n; k++) {
		//	printf("%d\t",list->D[k].key);
		//	if(!((k+1)%10)) printf("\n\n");
		//}
		//printf("\n");
	}

	system("pause");
	return 0;
}


/*

COPY RIGHT BY touuu

Reference material:
Data-Structure for C of NJUPT (Edition2)
http://c.biancheng.net/view/2043.html
https://blog.csdn.net/qq_44620773/article/details/103985380
https://www.cnblogs.com/Fsiswo/p/9291458.html
https://blog.csdn.net/y_dd6011/article/details/86408339
https://baike.baidu.com/item/CLK_TCK/2766625?fr=aladdin

Thanks~

*/ 
