#include "Head.h"

//һԪ������ʽ����ʽ
//����
//����
//���
//����
//����
//���
//���



//����
typedef struct pNode {
	int coef;
	int exp;
	struct pNode *link;
}PNode;

typedef struct polynominal {
	PNode *head;
}Polynominal;


//��ʼ��
Status Init(Polynominal *pn)
{
	pn->head = (PNode*)malloc(sizeof(PNode));
	pn->head->link = NULL;
	return OK;
}

//����
Status Input(Polynominal *pn)
{
	int coef,exp;
	PNode *p,*q;
	printf("\n\n\n\n���������ʽ1�ĸ���ϵ���Ͷ�Ӧ�����Ĵ���(��'0 0'����)\n");
	printf("�밴�����Ӹߵ��������뽫ͬ������ϲ���\n");
	
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


//���
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

//����
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

//���
Status Add(Polynominal *pn1,Polynominal *pn2)
{
	PNode *p = pn1->head;
	PNode *q = pn2->head;
	PNode *t = p;//p��ǰһ���ڵ�
	PNode *u;//��ʱ�ڵ�
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

//����
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


//���
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

	printf("��˵Ľ��:");
	Output(&x);
	
	return OK;
}




