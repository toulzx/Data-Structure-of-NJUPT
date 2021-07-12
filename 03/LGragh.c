#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#define ERROR 0
#define OK 1
#define Overflow 2      //上溢
#define Underflow 3     //下溢
#define NotPresent 4    //元素不存在
#define Duplicate 5     //有重复元素

typedef int ElemType;
typedef int Status;
typedef int BOOL;

#define TRUE 1
#define FALSE 0

//邻接表的结构体定义
typedef struct ENode{
    int adjVex;              //任意顶点u相邻的顶点
    ElemType w;              //边的权值
    struct ENode *nextArc;   //指向下一个边结点
}ENode;

typedef struct{
    int n;           //图的当前顶点数
    int e;           //图的当前边数
    ENode **a;       //一维数组指针
}LGraph;


//初始化
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

//撤销
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


//搜索
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


//插入
Status Insert(LGraph *lg,int u,int v,ElemType w){
    ENode *p;
    if(u<0 || v<0 || u>lg->n-1 || v>lg->n-1 || u==v){
		 printf("ERROR!请正确表示边！\n"); 
		return ERROR;
	}
    if(Exist(lg,u,v)) return Duplicate;       //若待插入边已存在,则返回出错信息
    p = (ENode*)malloc(sizeof(ENode));
    p->adjVex = v;
    p->w = w;
    p -> nextArc = lg->a[u];
    lg->a[u] = p;
    lg->e++;
    return OK;
}


//删除
Status Remove(LGraph *lg,int u,int v){
    ENode *p,*q;
    if(u<0 || v<0 || u>lg->n-1 || v>lg->n-1 || u==v){
		 printf("ERROR!请正确表示边！\n"); 
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


//循环队列的结构体定义
typedef struct{
    int front;
    int rear;
    int maxSize;    //最大容量
    ElemType *element;
}Queue;


//创建一个能容纳mSize个单元的空队列
void Create(Queue *Q,int mSize){
    Q->maxSize=mSize;
    Q->element=(ElemType*)malloc(sizeof(ElemType)*mSize);
    Q->front=Q->rear=0;
}


//判断队列是否为空,若是,则返回TRUE;否则返回FALSE
BOOL IsEmpty(Queue *Q){
    return Q->front==Q->rear;
}


//判断队列是否已满,若是,则返回TRUE,否则返回FALSE
BOOL IsFULL(Queue *Q){
    return (Q->rear+1)%Q->maxSize==Q->front;
}


//获取队头元素,并通过x返回.若操作成功,则返回TRUE,否则返回FALSE
BOOL Front(Queue *Q,ElemType *x){
    if(IsEmpty(Q))      //空队列处理
        return FALSE;
    *x=Q->element[(Q->front+1)%Q->maxSize];
    return TRUE;
}


//入队.在队列Q的队尾插入元素x(入队操作)。操作成功,则返回TRUE,否则返回FALSE
BOOL EnQueue(Queue *Q,ElemType x){
    if(IsFULL(Q))      //溢出处理
        return FALSE;
    Q->rear=(Q->rear+1)%Q->maxSize;
    Q->element[Q->rear]=x;
    return TRUE;
}


//出队.从队列Q中删除队头元素(出队操作)。操作成功,则返回TRUE,否则返回FALSE
BOOL DeQueue(Queue *Q){
    if(IsEmpty(Q)){   //空队列处理
        return FALSE;
    }
    Q->front=(Q->front+1)%Q->maxSize;
    return TRUE;
}

//单一顶点DFS
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


//全图DFS
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


//单一顶点BFS
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


//全图BFS
void BFSGraph(LGraph g){
    int i;
    int *visited = (int*)malloc(g.n * sizeof(int));  //动态生成visited数组
    for(i=0; i<g.n; i++){                         //初始化visited数组
        visited[i] = 0;
    }
    for(i=0; i<g.n; i++){                        //逐一检查每个顶点,若未被访问,则调用BFS
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

	//测试Init()
    printf("请输入邻接矩阵的阶/请输入节点个数：");
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
		printf("有向图or无向图？请输入1或0：");
		scanf("%d",&isMdg);
	}while(isMdg!=0 && isMdg!=1);

	do{
		printf("带权值or不带权值？请输入1或0：");
		scanf("%d",&haveWeight);
	}while(haveWeight!=0 && haveWeight!=1);

	printf("请输入边数：");
	scanf("%d",&edge);

	//测试Insert()
	printf("请根据需要修改邻接矩阵的值:\n");
	for(i=0; i<edge; i++){
		if(haveWeight == 0){
			w = 0;
			printf("请输入两个结点序号表示第%d条边",i);
			scanf("%d%d",&u,&v);
		}else{
			printf("请输入两个结点序号以及权值表示第%d条边",i);
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
	
	//测试Exist()
	do{
    printf("请输入要查找的边：");
	scanf("%d%d",&u,&v);
	}while(!Exist(&g,u,v));

	//测试Remove()
	do{
    printf("请输入要删除的边：");
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

	//测试DFSGraph()
	printf("DFS:\n");
    DFSGraph(g);

	//测试BFSGraph()
    printf("BFS:\n");
    BFSGraph(g);

    //测试Destroy()
	printf("已完成所有实验操作，现在销毁邻接矩阵：");    
	Destory(&g);

	system("pause");
    return 0;
}
