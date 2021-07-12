#include "Head.h"


//带表头节点的单链表
//定义
//初始化
//插入
//输出
//删除
//查找
//撤销
//逆置
//排序


typedef struct node
{
	ElemType element;
	struct node *link;
}Node;
typedef struct headerList 
{
	Node *head;
	int n;
}HeaderList;


// 带表头单链表初始化
Status Init(HeaderList *list)
{
	list->head = (Node*)malloc(sizeof(Node));
	list->head->link = NULL;
	list->n = 0;
	return OK;
}

// 带表头单链表插入
Status Insert(HeaderList *list, int i, ElemType t)//把t插在i后面
{
	Node *p,*q;
	int m;
	if( i<-1 || i>list->n-1 )	return ERROR;

	p = list->head;
	for(m=0;m<=i;m++)  p=p->link;

	q = (Node*)malloc(sizeof(Node));
	q->element = t;
	q->link = p->link;
	p->link = q;
	
	list->n++;

	return OK;
}

// 带表头单链表输出 
Status Output(HeaderList *list)
{
	Node *p;
	int i=0;
	if(!list->n)	return ERROR;
	p=list->head->link;
	for(i=1;i<=list->n;i++){
		printf("%d\n",p->element);
		p=p->link;
	}
	return OK;
}

// 带表头单链表删除
Status Delete(HeaderList *list,int i)//删除第i个
{
	Node *p,*q;
	int m;
	if(i<0 || i>=list->n)	return ERROR;
	else{
		p = list->head;
		for(m=0;m<i-1;m++) p = p->link; //注意是i-1指向要删除的那个的前一个
		q = p->link;
		p->link = p->link->link;
		free(q);
		list->n--;
		return OK;
	}
}

// 带表头单链表查找 
Status Find(HeaderList list,int t,ElemType *x)//查找第t个
{
	Node *p = list.head;
	int i;
	if(t<0 || t>=list.n)	return ERROR;
	else{
		for(i=0;i<t;i++) p = p->link;
		*x = p->element;
		return OK;
	}
}

// 带表头单链表撤销
Status Destroy(HeaderList *list)
{
	Node *p = list->head;
	while(p){
		list->head = p->link;
		free(p);
		p = list->head;
	}
	return OK;
}

// 带表头单链表的逆置 
Status Invert(HeaderList *list)//要求不引入新的存储空间
{
	Node *p,*q;
	if(list->head->link == NULL)
	{
		printf("Invert() ERROR：不存在\n");
		return ERROR;
	}else if(list->head->link->link == NULL){
		printf("Invert() OK：才1个\n");
		return OK;
	}else{
		p = list->head->link;
		q = list->head->link->link;
		p->link = NULL;
		while(q!=NULL){
			list->head->link = q; 
			q = q->link;
			list->head->link->link = p;
			p = list->head->link;
		}
		printf("Invert() OK\n");
		return OK;
	}
}


//带表头的单链表排序
Status Sort(HeaderList *list)
{
	Node *p,*q;
	ElemType temp;
	int m,n;

	printf("\n排序前：");
	Output(list);
	
	for(n=list->n;n>0;n--){
		p = list->head->link;//指向a1
		q = p->link;
		for(m=1;m<n;m++){
			if(p->element > q->element){
				temp = p->element;
				p->element = q->element;
				q->element = temp;
			}
			p = p->link;
			q = q->link;
		}
	}
	
		printf("\n排序后：");
		Output(list);
		return OK;
}
