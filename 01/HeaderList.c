#include "Head.h"


//����ͷ�ڵ�ĵ�����
//����
//��ʼ��
//����
//���
//ɾ��
//����
//����
//����
//����


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


// ����ͷ�������ʼ��
Status Init(HeaderList *list)
{
	list->head = (Node*)malloc(sizeof(Node));
	list->head->link = NULL;
	list->n = 0;
	return OK;
}

// ����ͷ���������
Status Insert(HeaderList *list, int i, ElemType t)//��t����i����
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

// ����ͷ��������� 
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

// ����ͷ������ɾ��
Status Delete(HeaderList *list,int i)//ɾ����i��
{
	Node *p,*q;
	int m;
	if(i<0 || i>=list->n)	return ERROR;
	else{
		p = list->head;
		for(m=0;m<i-1;m++) p = p->link; //ע����i-1ָ��Ҫɾ�����Ǹ���ǰһ��
		q = p->link;
		p->link = p->link->link;
		free(q);
		list->n--;
		return OK;
	}
}

// ����ͷ��������� 
Status Find(HeaderList list,int t,ElemType *x)//���ҵ�t��
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

// ����ͷ��������
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

// ����ͷ����������� 
Status Invert(HeaderList *list)//Ҫ�������µĴ洢�ռ�
{
	Node *p,*q;
	if(list->head->link == NULL)
	{
		printf("Invert() ERROR��������\n");
		return ERROR;
	}else if(list->head->link->link == NULL){
		printf("Invert() OK����1��\n");
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


//����ͷ�ĵ���������
Status Sort(HeaderList *list)
{
	Node *p,*q;
	ElemType temp;
	int m,n;

	printf("\n����ǰ��");
	Output(list);
	
	for(n=list->n;n>0;n--){
		p = list->head->link;//ָ��a1
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
	
		printf("\n�����");
		Output(list);
		return OK;
}
