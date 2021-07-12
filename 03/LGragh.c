#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#define ERROR 0
#define OK 1
#define Overflow 2      //����
#define Underflow 3     //����
#define NotPresent 4    //Ԫ�ز�����
#define Duplicate 5     //���ظ�Ԫ��

typedef int ElemType;
typedef int Status;
typedef int BOOL;

#define TRUE 1
#define FALSE 0

//�ڽӱ�Ľṹ�嶨��
typedef struct ENode{
    int adjVex;              //���ⶥ��u���ڵĶ���
    ElemType w;              //�ߵ�Ȩֵ
    struct ENode *nextArc;   //ָ����һ���߽��
}ENode;

typedef struct{
    int n;           //ͼ�ĵ�ǰ������
    int e;           //ͼ�ĵ�ǰ����
    ENode **a;       //һά����ָ��
}LGraph;


//��ʼ��
Status Init(LGraph *lg,int nSize){
    int  i;
    lg->n = nSize;
    lg->e = 0;
    lg->a = (ENode**)malloc(nSize*sizeof(ENode*));
    if(!lg->a) return ERROR;
    else{
        for(i=0; i<lg->n; i++) lg->a[i]=NULL;
        return OK;
    }
}

//����
void Destory(LGraph *lg){
    int i;
    ENode *p,*q;
    for(i=0; i<lg->n; i++){
        p = lg->a[i];
        q = p;
        while(p){
            p = p->nextArc;
            free(q);
            q = p;
        }
    }
    free(lg->a);
	printf("OK!\n");
    return;
}


//����
Status Exist(LGraph *lg,int u,int v){
    ENode *p;
    if(u<0 || v<0 || u>lg->n-1 || v>lg->n-1 || u==v){
		printf("ERROR\n"); 
		return ERROR;
	}
    p = lg->a[u];
    while(p && p->adjVex != v){
        p = p->nextArc;
    }
    if(!p) return ERROR;
    else return OK;
}


//����
Status Insert(LGraph *lg,int u,int v,ElemType w){
    ENode *p;
    if(u<0 || v<0 || u>lg->n-1 || v>lg->n-1 || u==v){
		 printf("ERROR!����ȷ��ʾ�ߣ�\n"); 
		return ERROR;
	}
    if(Exist(lg,u,v)) return Duplicate;       //����������Ѵ���,�򷵻س�����Ϣ
    p = (ENode*)malloc(sizeof(ENode));
    p->adjVex = v;
    p->w = w;
    p -> nextArc = lg->a[u];
    lg->a[u] = p;
    lg->e++;
    return OK;
}


//ɾ��
Status Remove(LGraph *lg,int u,int v){
    ENode *p,*q;
    if(u<0 || v<0 || u>lg->n-1 || v>lg->n-1 || u==v){
		 printf("ERROR!����ȷ��ʾ�ߣ�\n"); 
		return ERROR;
	}
    p = lg->a[u];
    q = NULL;
    while(p && p->adjVex != v){
        q = p;
        p = p->nextArc;
    }
    if(!p) return NotPresent;
    if(q) q->nextArc = p->nextArc;
    else lg->a[u] = p->nextArc;
    free(p);
    lg->e --;
	printf("OK!!!\n"); 
    return OK;
}


//ѭ�����еĽṹ�嶨��
typedef struct{
    int front;
    int rear;
    int maxSize;    //�������
    ElemType *element;
}Queue;


//����һ��������mSize����Ԫ�Ŀն���
void Create(Queue *Q,int mSize){
    Q->maxSize=mSize;
    Q->element=(ElemType*)malloc(sizeof(ElemType)*mSize);
    Q->front=Q->rear=0;
}


//�ж϶����Ƿ�Ϊ��,����,�򷵻�TRUE;���򷵻�FALSE
BOOL IsEmpty(Queue *Q){
    return Q->front==Q->rear;
}


//�ж϶����Ƿ�����,����,�򷵻�TRUE,���򷵻�FALSE
BOOL IsFULL(Queue *Q){
    return (Q->rear+1)%Q->maxSize==Q->front;
}


//��ȡ��ͷԪ��,��ͨ��x����.�������ɹ�,�򷵻�TRUE,���򷵻�FALSE
BOOL Front(Queue *Q,ElemType *x){
    if(IsEmpty(Q))      //�ն��д���
        return FALSE;
    *x=Q->element[(Q->front+1)%Q->maxSize];
    return TRUE;
}


//���.�ڶ���Q�Ķ�β����Ԫ��x(��Ӳ���)�������ɹ�,�򷵻�TRUE,���򷵻�FALSE
BOOL EnQueue(Queue *Q,ElemType x){
    if(IsFULL(Q))      //�������
        return FALSE;
    Q->rear=(Q->rear+1)%Q->maxSize;
    Q->element[Q->rear]=x;
    return TRUE;
}


//����.�Ӷ���Q��ɾ����ͷԪ��(���Ӳ���)�������ɹ�,�򷵻�TRUE,���򷵻�FALSE
BOOL DeQueue(Queue *Q){
    if(IsEmpty(Q)){   //�ն��д���
        return FALSE;
    }
    Q->front=(Q->front+1)%Q->maxSize;
    return TRUE;
}

//��һ����DFS
void DFS(int v,int visited[],LGraph g){
    ENode *w;
    printf("%d ",v);
    visited[v] = 1;
    for(w=g.a[v]; w; w=w->nextArc){
        if(!visited[w->adjVex]){
            DFS(w->adjVex,visited,g);
        }
    }
}


//ȫͼDFS
void DFSGraph(LGraph g){
    int i;
    int *visited  = (int*)malloc(g.n * sizeof(int));
    for(i=0; i<g.n; i++){
        visited[i] = 0;
    }
    for(i=0; i<g.n; i++){
        if(!visited[i]){
            DFS(i,visited,g);
        }
    }
    free(visited);
}


//��һ����BFS
void BFS(int v,int visited[],LGraph g){
    ENode *w;
    Queue q;
    Create(&q,g.n);
    visited[v] = 1;
    printf("%d ",v);
    EnQueue(&q,v);
    while(!IsEmpty(&q)){
        Front(&q,&v);
        DeQueue(&q);
        for(w=g.a[v]; w; w=w->nextArc){
            if(!visited[w->adjVex]){
                visited[w->adjVex] = 1;
                printf("%d ",w->adjVex);
                EnQueue(&q,w->adjVex);
            }
        }
    }
}


//ȫͼBFS
void BFSGraph(LGraph g){
    int i;
    int *visited = (int*)malloc(g.n * sizeof(int));  //��̬����visited����
    for(i=0; i<g.n; i++){                         //��ʼ��visited����
        visited[i] = 0;
    }
    for(i=0; i<g.n; i++){                        //��һ���ÿ������,��δ������,�����BFS
        if(!visited[i]){
            BFS(i,visited,g);
        }
    }
    free(visited);
}



int main(){
    LGraph g;
    int nSize, edge, u, v;
    ElemType w;
	ENode *e;
	int i,j;
	int isMdg, haveWeight;

	//����Init()
    printf("�������ڽӾ���Ľ�/������ڵ������");
    scanf("%d",&nSize);

    if(Init(&g,nSize)) printf("Init() OK!\n");
	else {
		printf("Init() ERROR!\n");
		return 0;
	}

	for(i=0; i<g.n; i++){
		e = g.a[i];
		printf("%d\t",i);
		while(e){
			printf("%d ",e->adjVex);
			e = e->nextArc;
		}
		printf("\n");
	}

	do{
		printf("����ͼor����ͼ��������1��0��");
		scanf("%d",&isMdg);
	}while(isMdg!=0 && isMdg!=1);

	do{
		printf("��Ȩֵor����Ȩֵ��������1��0��");
		scanf("%d",&haveWeight);
	}while(haveWeight!=0 && haveWeight!=1);

	printf("�����������");
	scanf("%d",&edge);

	//����Insert()
	printf("�������Ҫ�޸��ڽӾ����ֵ:\n");
	for(i=0; i<edge; i++){
		if(haveWeight == 0){
			w = 0;
			printf("���������������ű�ʾ��%d����",i);
			scanf("%d%d",&u,&v);
		}else{
			printf("�����������������Լ�Ȩֵ��ʾ��%d����",i);
			scanf("%d%d%d",&u,&v,&w);
		}
		Insert(&g,u,v,w);
		if(!isMdg) Insert(&g,v,u,w);
	}

	for(i=0; i<g.n; i++){
		e = g.a[i];
		printf("%d\t",i);
		while(e){
			printf("%d ",e->adjVex);
			e = e->nextArc;
		}
		printf("\n");
	}
	
	//����Exist()
	do{
    printf("������Ҫ���ҵıߣ�");
	scanf("%d%d",&u,&v);
	}while(!Exist(&g,u,v));

	//����Remove()
	do{
    printf("������Ҫɾ���ıߣ�");
	scanf("%d%d",&u,&v);
	}while(!Remove(&g,u,v));

	for(i=0; i<g.n; i++){
		e = g.a[i];
		printf("%d\t",i);
		while(e){
			printf("%d ",e->adjVex);
			e = e->nextArc;
		}
		printf("\n");
	}

	//����DFSGraph()
	printf("DFS:\n");
    DFSGraph(g);

	//����BFSGraph()
    printf("BFS:\n");
    BFSGraph(g);

    //����Destroy()
	printf("���������ʵ����������������ڽӾ���");    
	Destory(&g);

	system("pause");
    return 0;
}
