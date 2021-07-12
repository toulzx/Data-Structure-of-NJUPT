#include<stdlib.h>
//标准库函数头文件，包含malloc()、free()、rand()等
#include<stdio.h>
//标准输入输出头文件，包含printf()、scanf()...
#include<string.h>
//标准字符操作头文件，包含strcpy()...
#define MAXNUM 100
typedef char ElemType;

//定义
typedef struct htnode{
	ElemType element;
	int weight;
	struct htnode *lChild;
	struct htnode *rChild;
}HTNode;

typedef struct huffmantree{
	HTNode *root;
}HuffmanTree;


void TheYoungestTwo(int* T1,int* T2,HTNode* htntemps,int* htntemps_used){
	int i,temp;
	HTNode t1,t2,t3;
	printf("→找出最小权值的两棵树←\n");
	for(i=0;htntemps_used[i]!=0;i++){
		if(htntemps_used[i]==-1){
			//t1.element = htntemps[i].element;
			t1.weight = htntemps[i].weight;
			*T1=i;
			i++;
			break;
		}
	}
	for(;htntemps_used[i]!=0;i++){
		if(htntemps_used[i]==-1){
			//t2.element = htntemps[i].element;
			t2.weight = htntemps[i].weight;
			*T2=i;
			i++;
			break;
		}
	}	
	for(;htntemps_used[i]!=0;i++){
		if(htntemps_used[i] == 1)continue;
			if(htntemps[i].weight < t1.weight){
			if(t1.weight < t2.weight){//第一次不确定t1一定比t2小
				//t2.element = t1.element;
				t2.weight = t1.weight;
				*T2 = *T1;
			}
			//t1.element = htntemps[i].element;
			t1.weight = htntemps[i].weight;
			*T1 = i;
		}else if(htntemps[i].weight >= t1.weight && htntemps[i].weight < t2.weight){
			//t2.element = htntemps[i].element;
			t2.weight = htntemps[i].weight;
			*T2 = i;
		}else if(htntemps[i].weight >= t2.weight) continue;
		else printf("→出错了！\n");
	}
	if(t1.weight>t2.weight){
		t3.weight = t1.weight;
		t1.weight = t2.weight;
		t2.weight = t3.weight;
		//如果不输出下面注释的话上面三行其实没必要
		temp = *T1;
		*T1 = *T2;
		*T2 = temp;
	}
	printf("t1:[%d]%d\nt2:[%d]%d\n",*T1,t1.weight,*T2,t2.weight);
}

int isFinish(int* htntemps_used,int subLength){
	int i,t;
	for(i=0,t=0;i<subLength;i++){
	t += htntemps_used[i];
	}
	if(t==subLength) return 1;
	else return 0;
}

//输入
int Input(HTNode* htns, int *L){
	int i;
	for(i=0;i<*L;i++){
		scanf("%c%d",&htns[i].element,&htns[i].weight);//!!!htn->element需不需要取地址符？//////////////////////////////////////////////
		if(htns[i].element=='#' && htns[i].weight==0){
			*L = i-1;//下面记得判断以开始就输入#0的情况
			if(*L==-1 || L==0){
				printf("你玩我呢？\n");
				return -1;
			}
			break;
		}
	}
	printf("→输入结点←\n");
	for(i=0;i<=*L;i++){
		printf("%c%d\n",htns[i].element,htns[i].weight);
	}
	return *L;//返回元素个数-1
}

//创建哈夫曼树
HTNode* CreateHT(HTNode *htn,HTNode *htns,int subLength){
	int T1,T2;//记录最小权值的两个结点的下标
	HTNode htntemps[MAXNUM],htn1,htn2;//用于存放临时合成的树
	int htntemps_used[MAXNUM];
	//记录是否新生成的结点是否被使用了
	//下面循环初始化为0（未使用）-1(已使用) 1（已连接）
	int i;
	//数组初始化
	for(i=0;i<MAXNUM;i++){
		htntemps[i].element = NULL;
		htntemps[i].lChild = &htn1;
		htntemps[i].rChild = &htn2;
		htntemps[i].weight = 0;
	}
	for(i=0;i<MAXNUM;i++){
		htntemps_used[i] = 0;
	}

	//结点变树
	for(i=0;i<=subLength;i++){
		htntemps[i].element = htns[i].element;
		htntemps[i].weight = htns[i].weight;
		htntemps_used[i] = -1;
	}
	printf("→结点变树←\n");
	for(i=0;i<=subLength;i++){
		printf("%c%d\n",htntemps[i].element,htntemps[i].weight);
	}

	for(;!isFinish(htntemps_used,subLength);){
		subLength++;
		//找出最小权值的两棵树在数组里的下标值T1T2
		TheYoungestTwo(&T1,&T2,htntemps,htntemps_used);
		//连接树
		//htntemps[subLength].element = NULL;
		htntemps[subLength].weight = htntemps[T1].weight + htntemps[T2].weight;
		htntemps[subLength].lChild = &htntemps[T1];
		htntemps[subLength].rChild = &htntemps[T2];
		htntemps_used[T1] = 1;
		htntemps_used[T2] = 1;
		htntemps_used[subLength] = -1;
	}
	for(i=0;i<=subLength;i++){
		printf("(%d)%d ",htntemps_used[i],htntemps[i].weight);
	}
	return &htntemps[subLength];
}
//哈夫曼树的创建
void PreMakeTree(HuffmanTree *ht,HTNode *htns,int L){
	ht->root = CreateHT(ht->root,htns,L);
}


//哈夫曼编码//先序遍历
void Encode(HTNode *htn,int** code,int* I,int lr,int L,int i){
	int t;
	if(lr == -1) {for(t=*I;t<=L;t++) code[t][i]= -1;}
	else if(lr == 1) {for(t=*I;t<=L;t++) code[t][i]=1;}
	//↑编码时候0才表示左，这里使用-1是为了与之前规则统一
	if(htn->lChild) Encode(htn->lChild,code,I,-1,L,i+1); 
	if(htn->rChild) Encode(htn->rChild,code,++I,1,L,i+1);
	if(htn->lChild && htn->lChild) code[*I][i+1]=0;
	//参考示意图，属同一棵树的编码只编了出现的第一项，所以使用循环覆盖所有子树情况，
	//但一旦之前的编码长度比现在编码长度长，会导致编码结束后剩余部分非初始值（被以前的修改过）
	return;
}
void HTEncode(HuffmanTree *ht,int** code, int L){
	int I=0;//第几个编码
	int i=0;//编码录入时计数用
	int lr = 0;//左子树-1还是右子树1,初值0
	return Encode(ht->root,code,&I,lr,L,i);
}

//哈夫曼解码
//哈夫曼解码
void Decode(HTNode *htn,HuffmanTree* ht){
	int temp;
	if(htn->lChild || htn->rChild) scanf("%d",&temp);
	else{
			printf("%c",htn->element);
			Decode(ht->root,ht);
		}
	if(!temp)Decode(htn->lChild,ht);
	else Decode(htn->rChild,ht);
}

//先序遍历
void PrintHT(HTNode *btn){
	if(btn){
		printf("%d ",btn->weight);
		PrintHT(btn->lChild);
		PrintHT(btn->rChild);
	}
	return;
}

