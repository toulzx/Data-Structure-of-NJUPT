#include "Head.h"

//一元整数形式多项式
//创建
//输入
//输出
//插入
//撤销
//相加
//相乘



//定义
typedef struct pNode {
	int coef;
	int exp;
	struct pNode *link;
}PNode;

typedef struct polynominal {
	PNode *head;
}Polynominal;


//初始化
Status Init(Polynominal *pn)
{
	pn->head = (PNode*)malloc(sizeof(PNode));
	pn->head->link = NULL;
	return OK;
}

//输入
Status Input(Polynominal *pn)
{
	int coef,exp;
	PNode *p,*q;
	printf("\n\n\n\n请输入多项式1的各项系数和对应变量的次数(以'0 0'结束)\n");
	printf("请按次数从高到低排序，请将同次数项合并：\n");
	
	p = pn->head;
	do{
		q = (PNode*)malloc(sizeof(PNode));
		scanf("%d %d",&coef,&exp);
		if(!coef) break;
		q->coef = coef;
		q->exp = exp;
		q->link = NULL;
		p->link = q;
		p = p->link;
	}while(1);
	return OK;
}


//输出
static int onum = 1;

Status Output(Polynominal *pn)
{
	PNode *p;
	if(pn->head->link == NULL)return ERROR;
	else{
		p = pn->head->link;
		printf("\n\n	P%d(x)=",onum);
		onum++;
		printf("%dx^(%d)",p->coef,p->exp);
		p = p->link;
		while(p){
			if(p->exp != 0){
				if(p->coef > 0) printf("+%dx^(%d)",p->coef,p->exp);
				else printf("%dx^(%d)",p->coef,p->exp);
			}else{
				if(p->coef > 0) printf("+%d",p->coef);
				else printf("%d",p->coef);
			}
			p = p->link;
		}
		printf("\n");
	}
	return OK;
}

//撤销
Status Destroy(Polynominal *pn)
{
	PNode *p;
	while(pn->head->link){
		p = pn->head->link;
		pn->head->link = pn->head->link->link;
		free(p);
	}
	onum--;
	return OK;
}

//相加
Status Add(Polynominal *pn1,Polynominal *pn2)
{
	PNode *p = pn1->head;
	PNode *q = pn2->head;
	PNode *t = p;//p的前一个节点
	PNode *u;//临时节点
	p = p->link;
	q = q->link;

	while(q){
		if(p){
			if(p->exp == q->exp){	
				p->coef += q->coef;
				u = q;
				q = q->link;
				free(u);
				if(p->coef == 0){
					u = p;
					p = p->link;
					t->link = p;
					free(u);
				}else{
					t = p;
					p = p->link;
				}
			}else if(p->exp > q->exp){
				t = p;
				p = p->link;
			}else{
				t->link = q;
				q = q->link;
				t->link->link = p;
				t = t->link;
			}	
		}else {
			t->link = q;
			break;
		}
	}
	pn2->head->link = NULL;
	return OK;
}

//插入
Status Insert(Polynominal *pn,PNode *t)
{
	PNode *u = (PNode*)malloc(sizeof(PNode));
	PNode *v = pn->head;

	u->coef = t->coef;
	u->exp = t->exp;
	u->link = t->link;

	while(v->link) v= v->link;
	v->link = u;

	return OK;
}


//相乘
Status Mutiply(Polynominal *pn1,Polynominal *pn2)
{
	Polynominal x,y;
	PNode *p = pn1->head->link;
	PNode *q = pn2->head->link;
	PNode *t = (PNode*)malloc(sizeof(PNode));
	int m;

	Init(&x);
	Init(&y);
	
	while(q){
		t->exp = p->exp + q->exp;
		t->coef = p->coef * q->coef;
		t->link = NULL;
		Insert(&x,t);
		q = q->link;
	}
	p = p->link;

	while(p){
		q = pn2->head->link;
		while(q){
			t->exp = p->exp + q->exp;
			t->coef = p->coef * q->coef;
			t->link = NULL;
			Insert(&y,t);
			q = q->link;
		}
		p = p->link;
		Add(&x,&y);
	}

	printf("相乘的结果:");
	Output(&x);
	
	return OK;
}




