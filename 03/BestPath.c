#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#define ERROR 0
#define OK 1
#define Overflow 2     //��ʾ����
#define Underflow 3    //��ʾ����
#define NotPresent 4   //��ʾԪ�ز�����
#define Duplicate 5    //��ʾ���ظ�Ԫ��
#define INT_MAX 99999
typedef int ElemType;
typedef int Status;


//�ڽӾ���Ľṹ�嶨��
typedef struct{
    ElemType **a;     //�ڽӾ���
    int n;            //������
    int e;            //����
    ElemType noEdge;  //��������ޱ�ʱ��ֵ
}mGraph;


//�ڽӾ���ĳ�ʼ��
Status Init(mGraph *mg,int nSize,ElemType noEdgeValue){
    int i,j;
    mg->n = nSize;               //��ʼ��������
    mg->e = 0;                   //��ʼ��ʱû�б�
    mg->noEdge = noEdgeValue;    //��ʼ��û�б�ʱ��ȡֵ
    mg->a = (ElemType**)malloc(nSize*sizeof(ElemType *));  //���ɳ���Ϊn��һάָ������
    if(!mg->a) return ERROR;
    for(i=0; i<mg->n; i++){   //��̬���ɶ�ά����
        mg->a[i] = (ElemType*)malloc(nSize*sizeof(ElemType));
        for(j=0; j<mg->n; j++){
            mg->a[i][j] = mg->noEdge;  //��ʼ��ʱȨ�ض���Ϊ-1
        }
    }
    return OK;
}


//�ڽӾ���ĳ���
int Destory(mGraph *mg){
    int i;
    for(i=0; i<mg->n; i++){
        free(mg->a[i]);  //�ͷ�n��һά����Ĵ洢�ռ�
    }
    free(mg->a);         //�ͷ�һά����Ĵ洢�ռ�
    return 1;
}


//�ڽӾ���ıߵ�����
Status Exist(mGraph *mg,int u,int v){
    if(u<0 || v<0 || u>mg->n-1 || v>mg->n-1 || u==v || mg->a[u][v] == mg->noEdge) return ERROR;
    return OK;
}


//�ڽӾ���ıߵĲ���
Status Insert(mGraph *mg,int u,int v,ElemType w){
    if(u<0 || v<0 || u>mg->n-1 || v>mg->n-1 || u==v) return ERROR;
    if(mg->a[u][v] != mg->noEdge) return Duplicate;  //����������Ѵ���,�򷵻س�����Ϣ
    mg->a[u][v] = w;                                 //�����±�
    mg->e ++;                                        //����һ����
    return OK;
}


//�ڽӾ���ıߵ�ɾ��
Status Remove(mGraph *mg,int u,int v){
    if(u<0 || v<0 || u>mg->n-1 || v>mg->n-1 || u==v) return ERROR;
    if(mg->a[u][v] == mg->noEdge) return NotPresent;  //����ɾ���߲�����,�򷵻س�����Ϣ
    mg->a[u][v] = mg->noEdge;                         //ɾ����
    mg->e --;
    return OK;
}


//ѡ����С��d[i]
int Choose(int d[],int n,int s[]){
    int i,minpos;
    ElemType min;
    min = INT_MAX;//�����ֵ
    minpos = -1;
    for(i=0; i<n; i++){
        if(d[i]<=min && !s[i]){ 
            min = d[i];
            minpos = i;
        }
    }
    return minpos;
}


//Dijkstra�㷨
Status Dijkstra(mGraph g,int v,int d[],int path[]){
    int i,k,w,distance = 0;
    int *s;
    if(v < 0||v > g.n-1){
        return ERROR;
    }
    s = (int*)malloc(g.n*sizeof(int));
    for(i=0; i<g.n; i++){      //��ʼ��
        s[i] = 0;                 //��ʾ����i�Ƿ���s��
        d[i] = g.a[v][i];         //v��i�ľ���
        if(i != v && d[i] < INT_MAX){
            path[i] = v;          //��ʶָ��i��Դ��v
        }
        else path[i] = -1;
    }
    s[v] = 1;                     //����vΪԴ��,��ԭ��v���뼯��S
    printf("%d ",v);              //���Դ��0
    d[v] = 0;
    for(i=1; i<=g.n-1; i++){   //����n-1�����·��,<��Ϊ<=
        k = Choose(d,g.n,s);      //��ǰ·�������k
        s[k] = 1;                 //��k���뼯��S��
        printf("%d ",k);
        for(w=0; w<g.n; w++){  //����d��path
            if(!s[w] && d[k]+g.a[k][w] < d[w]){
                d[w] = d[k] + g.a[k][w];
                distance = d[w];  //����min����
                path[w] = k;
            }
        }
    }
    printf("\nThe shortest distance:%d\n ",distance);
    return OK;
}



int main(){
    mGraph g;
    int nSize,edge,u,v;
	int i,j;
    int d[100];
    int path[100];
    ElemType w;
	int isMdg, haveWeight;

	printf("#��ͨ�����·��#\n");
    printf("�������ڽӾ���Ľ�/������ڵ������");
    scanf("%d",&nSize);

	//����Init()
    Init(&g,nSize,INT_MAX);//INT_MAX��ʾ�����

	for(i=0; i<nSize; i++){
		for(j=0; j<nSize; j++) printf("%10d\t",g.a[i][j]);
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
		for(j=0; j<nSize; j++) printf("%10d\t",g.a[i][j]);
		printf("\n");
	}

	//����Dijkstra()
    Dijkstra(g,0,d,path);
    
	//����Destroy()
	printf("���������ʵ����������������ڽӾ���");    
	Destory(&g);

	system("pause");
    return 0;
}
