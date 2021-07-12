
#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define Overflow 2			//上溢
#define Underflow 3			//下溢
#define NotPresent 4		//不存在
#define Duplicate 5			//重复

#define NoEdgeValue -1		//初始化时给数组赋值为-1

typedef int ElemType;
typedef int Status;
typedef int BOOL;

#define TRUE 1
#define FALSE 0

//结构体定义
typedef struct mGraph{
    ElemType **a;     //邻接矩阵
    int n;            //图的当前顶点数
    int e;            //图的当前边数
    ElemType noEdge;  //两顶点间无边时的值
}MGraph;


//初始化
Status Init(MGraph *mg, int nSize){//删除初始化赋值变量，使用宏定义
    int i,j;
    mg->n = nSize;               //初始化顶点数
    mg->e = 0;                   //初始化时没有边
    mg->noEdge = NoEdgeValue;    //初始化没有边时的取值，默认-1
    mg->a = (ElemType**)malloc(nSize*sizeof(ElemType *));  //生成长度为n的一维指针数组
    if(!mg->a) return ERROR;
    for(i=0; i < mg->n; i++){    //动态生成二维数组
        mg->a[i] = (ElemType*)malloc(nSize*sizeof(ElemType));
        for(j=0;j < mg->n; j++){
            mg->a[i][j] = mg->noEdge;
        }
    }
    return OK;
}


//撤销
void Destory(MGraph *mg){
    int i;
    for(i = 0;i < mg->n;i ++) free(mg->a[i]);
    free(mg->a);				//先释放一维数组,再释放指针数组
    printf("OK!\n");
	return;
}


//搜索
Status Exist(MGraph *mg, int u, int v){
	if(u<0 || v<0 || u > mg->n-1 || v>mg->n-1 || u==v || mg->a[u][v] == mg->noEdge){
		printf("ERROR\n"); 
		return ERROR;
	}
	printf("OK!\n"); 
    return OK;
}


//插入
Status Insert(MGraph *mg, int u, int v, ElemType w){
    if(u<0 || v<0 || u > mg->n-1 || v>mg->n-1 || u==v){
		printf("ERROR\n"); 
		return ERROR;
	}
    if(mg->a[u][v] != mg->noEdge) return Duplicate;  //若待插入边已存在,则返回出错信息
    mg->a[u][v] = w;                                 //插入新边
    mg->e++;                                       
    return OK;
}


//删除
Status Remove(MGraph *mg,int u,int v){
    if(u<0 || v<0 || u > mg->n-1 || v>mg->n-1 || u==v){
		 printf("ERROR!请正确表示边！\n"); 
		return ERROR;
	}
    if(mg->a[u][v] == mg->noEdge){
		 printf("NotPresent!!!\n"); 
		 return NotPresent;							  //若待删除边不存在,则返回出错信息
	}
    mg->a[u][v] = mg->noEdge;                         //删除边
    mg->e--;
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


//邻接矩阵的单一顶点DFS
void DFS(int v, int visited[], MGraph g){
    int j;
    printf("%d ",v);              //访问顶点v
    visited[v] = 1;               //为顶点v打上访问标记       
    for(j=0; j<g.n; j++){      //遍历v的邻接点
		if(!visited[j] && g.a[v][j]>=0){
			DFS(j,visited,g);
			break;//这一行可以不加的，但是为了测试生成一种森林，还是加上吧~
		}
    }
}


//邻接矩阵的全图DFS
void DFSGraph(MGraph g){
    int i;
    int *visited = (int*)malloc(g.n * sizeof(int)); //动态生成标记数组visted
    for(i=0; i<g.n; i++) visited[i] = 0;
    for(i=0; i<g.n; i++){     //逐一检查每个顶点,若未被访问,则调用DFS
        if(!visited[i]) DFS(i,visited,g);
		printf("\n");
    }
	printf("\n");
    free(visited);                       //释放visted数组
}


//邻接矩阵的单一顶点BFS
void BFS(int v,int visited[],MGraph g){
    int i;
	Queue q;
    Create(&q,g.n);                        //初始化队列
    visited[v] = 1;                        //为顶点v打上访问标记
    printf("%d ",v);                       //访问顶点v
    EnQueue(&q,v);                         //将顶点v放入队列
    while(!IsEmpty(&q)){
        Front(&q,&v);
        DeQueue(&q);                       //队首顶点出队列
        for(i=0; i<g.n; i++){				//遍历v的每一项
            if(!visited[i] && g.a[v][i]>=0){       //若未被访问且有权值,则将其访问并放入队列,注意这里判断的是g.a[v][i]二维数组
                visited[i] = 1;
                printf("%d ",i);
                EnQueue(&q,i);
            }
        }
    }
}


//邻接矩阵的全图BFS
void BFSGraph(MGraph g){
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
	printf("\n");
    free(visited);
}



int main(){
    MGraph g;
    int nSize, edge, u, v;
    ElemType w;
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

	for(i=0; i<nSize; i++){
		for(j=0; j<nSize; j++) printf("%d\t",g.a[i][j]);
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

	for(i=0; i<nSize; i++){
		for(j=0; j<nSize; j++) printf("%d\t",g.a[i][j]);
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

	for(i=0; i<nSize; i++){
		for(j=0; j<nSize; j++) printf("%d\t",g.a[i][j]);
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
