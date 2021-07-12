
#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define Overflow 2			//����
#define Underflow 3			//����
#define NotPresent 4		//������
#define Duplicate 5			//�ظ�

#define NoEdgeValue -1		//��ʼ��ʱ�����鸳ֵΪ-1

typedef int ElemType;
typedef int Status;
typedef int BOOL;

#define TRUE 1
#define FALSE 0

//�ṹ�嶨��
typedef struct mGraph{
    ElemType **a;     //�ڽӾ���
    int n;            //ͼ�ĵ�ǰ������
    int e;            //ͼ�ĵ�ǰ����
    ElemType noEdge;  //��������ޱ�ʱ��ֵ
}MGraph;


//��ʼ��
Status Init(MGraph *mg, int nSize){//ɾ����ʼ����ֵ������ʹ�ú궨��
    int i,j;
    mg->n = nSize;               //��ʼ��������
    mg->e = 0;                   //��ʼ��ʱû�б�
    mg->noEdge = NoEdgeValue;    //��ʼ��û�б�ʱ��ȡֵ��Ĭ��-1
    mg->a = (ElemType**)malloc(nSize*sizeof(ElemType *));  //���ɳ���Ϊn��һάָ������
    if(!mg->a) return ERROR;
    for(i=0; i < mg->n; i++){    //��̬���ɶ�ά����
        mg->a[i] = (ElemType*)malloc(nSize*sizeof(ElemType));
        for(j=0;j < mg->n; j++){
            mg->a[i][j] = mg->noEdge;
        }
    }
    return OK;
}


//����
void Destory(MGraph *mg){
    int i;
    for(i = 0;i < mg->n;i ++) free(mg->a[i]);
    free(mg->a);				//���ͷ�һά����,���ͷ�ָ������
    printf("OK!\n");
	return;
}


//����
Status Exist(MGraph *mg, int u, int v){
	if(u<0 || v<0 || u > mg->n-1 || v>mg->n-1 || u==v || mg->a[u][v] == mg->noEdge){
		printf("ERROR\n"); 
		return ERROR;
	}
	printf("OK!\n"); 
    return OK;
}


//����
Status Insert(MGraph *mg, int u, int v, ElemType w){
    if(u<0 || v<0 || u > mg->n-1 || v>mg->n-1 || u==v){
		printf("ERROR\n"); 
		return ERROR;
	}
    if(mg->a[u][v] != mg->noEdge) return Duplicate;  //����������Ѵ���,�򷵻س�����Ϣ
    mg->a[u][v] = w;                                 //�����±�
    mg->e++;                                       
    return OK;
}


//ɾ��
Status Remove(MGraph *mg,int u,int v){
    if(u<0 || v<0 || u > mg->n-1 || v>mg->n-1 || u==v){
		 printf("ERROR!����ȷ��ʾ�ߣ�\n"); 
		return ERROR;
	}
    if(mg->a[u][v] == mg->noEdge){
		 printf("NotPresent!!!\n"); 
		 return NotPresent;							  //����ɾ���߲�����,�򷵻س�����Ϣ
	}
    mg->a[u][v] = mg->noEdge;                         //ɾ����
    mg->e--;
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


//�ڽӾ���ĵ�һ����DFS
void DFS(int v, int visited[], MGraph g){
    int j;
    printf("%d ",v);              //���ʶ���v
    visited[v] = 1;               //Ϊ����v���Ϸ��ʱ��       
    for(j=0; j<g.n; j++){      //����v���ڽӵ�
		if(!visited[j] && g.a[v][j]>=0){
			DFS(j,visited,g);
			break;//��һ�п��Բ��ӵģ�����Ϊ�˲�������һ��ɭ�֣����Ǽ��ϰ�~
		}
    }
}


//�ڽӾ����ȫͼDFS
void DFSGraph(MGraph g){
    int i;
    int *visited = (int*)malloc(g.n * sizeof(int)); //��̬���ɱ������visted
    for(i=0; i<g.n; i++) visited[i] = 0;
    for(i=0; i<g.n; i++){     //��һ���ÿ������,��δ������,�����DFS
        if(!visited[i]) DFS(i,visited,g);
		printf("\n");
    }
	printf("\n");
    free(visited);                       //�ͷ�visted����
}


//�ڽӾ���ĵ�һ����BFS
void BFS(int v,int visited[],MGraph g){
    int i;
	Queue q;
    Create(&q,g.n);                        //��ʼ������
    visited[v] = 1;                        //Ϊ����v���Ϸ��ʱ��
    printf("%d ",v);                       //���ʶ���v
    EnQueue(&q,v);                         //������v�������
    while(!IsEmpty(&q)){
        Front(&q,&v);
        DeQueue(&q);                       //���׶��������
        for(i=0; i<g.n; i++){				//����v��ÿһ��
            if(!visited[i] && g.a[v][i]>=0){       //��δ����������Ȩֵ,������ʲ��������,ע�������жϵ���g.a[v][i]��ά����
                visited[i] = 1;
                printf("%d ",i);
                EnQueue(&q,i);
            }
        }
    }
}


//�ڽӾ����ȫͼBFS
void BFSGraph(MGraph g){
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
	printf("\n");
    free(visited);
}



int main(){
    MGraph g;
    int nSize, edge, u, v;
    ElemType w;
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

	for(i=0; i<nSize; i++){
		for(j=0; j<nSize; j++) printf("%d\t",g.a[i][j]);
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

	for(i=0; i<nSize; i++){
		for(j=0; j<nSize; j++) printf("%d\t",g.a[i][j]);
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

	for(i=0; i<nSize; i++){
		for(j=0; j<nSize; j++) printf("%d\t",g.a[i][j]);
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
