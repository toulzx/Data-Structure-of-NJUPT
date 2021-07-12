#include "Head.h"


//定义
//初始化
//插入
//输出
//查找
//删除
//撤销



// 线性表的顺序表定义
	typedef struct seqList
	{
		int n;
		int maxLength;
		ElemType *element;
	}SeqList;

// 顺序表的初始化
	Status Init(SeqList *list, int msize)
	{
		list->maxLength = msize;
		list->n = 0;
		list->element = (ElemType *)malloc(sizeof(ElemType)*msize);
		if(!list->element) 	return ERROR;
		else	return OK;
	}


// 顺序表的插入
	Status Insert(SeqList *list, int t, ElemType x)//插在i后，插入数x
	{
		int i=0;
		if(list->n == list->maxLength) 	return ERROR;
		if(t > list->n-1 || t<-1)	return ERROR;
		
		for(i = list->n - 1; i>t; i--) list->element[i+1] = list->element[i];
		list->element[t+1] = x;
		list->n++;
		return OK;
	}

// 顺序表的输出
	Status Output(SeqList list)
	{
		int i=0;
		if(list.n != 0)
		{
			for(i=0; i<list.n; i++) printf("%d ",list.element[i]);
			return OK;
		}else  return ERROR;
	}


	// 顺序表的查找
	Status Find (SeqList list, int i, ElemType *x)
	{
		if( i<0 || i>=list.n ) return ERROR;
		else{
			*x = list.element[i];
			return OK;
		}
	}

// 顺序表的删除
	Status Delete(SeqList *list, int t)
	{
		int i=0;
		if(!list->n)	return ERROR;
		if(t<0 || t>list->n-1) 	return ERROR;
		for(i=t+1; i<=list->n; i++) list->element[i-1] = list->element[i];
		list->n--;
		return OK;
	}

// 顺序表的撤销 
	void Destroy(SeqList *list)
	{
		list->n = 0;
		list->maxLength = 0;
		free(list->element);
	}
