#include<stdlib.h>
//��׼�⺯��ͷ�ļ�������malloc()��free()��rand()��
#include<stdio.h>
//��׼�������ͷ�ļ�������printf()��scanf()...
#include<string.h>
//��׼�ַ�����ͷ�ļ�������strcpy()...
#define MAXNUM 100
typedef char ElemType;

//����
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
	printf("���ҳ���СȨֵ����������\n");
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
			if(t1.weight < t2.weight){//��һ�β�ȷ��t1һ����t2С
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
		else printf("�������ˣ�\n");
	}
	if(t1.weight>t2.weight){
		t3.weight = t1.weight;
		t1.weight = t2.weight;
		t2.weight = t3.weight;
		//������������ע�͵Ļ�����������ʵû��Ҫ
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

//����
int Input(HTNode* htns, int *L){
	int i;
	for(i=0;i<*L;i++){
		scanf("%c%d",&htns[i].element,&htns[i].weight);//!!!htn->element�費��Ҫȡ��ַ����//////////////////////////////////////////////
		if(htns[i].element=='#' && htns[i].weight==0){
			*L = i-1;//����ǵ��ж��Կ�ʼ������#0�����
			if(*L==-1 || L==0){
				printf("�������أ�\n");
				return -1;
			}
			break;
		}
	}
	printf("���������\n");
	for(i=0;i<=*L;i++){
		printf("%c%d\n",htns[i].element,htns[i].weight);
	}
	return *L;//����Ԫ�ظ���-1
}

//������������
HTNode* CreateHT(HTNode *htn,HTNode *htns,int subLength){
	int T1,T2;//��¼��СȨֵ�����������±�
	HTNode htntemps[MAXNUM],htn1,htn2;//���ڴ����ʱ�ϳɵ���
	int htntemps_used[MAXNUM];
	//��¼�Ƿ������ɵĽ���Ƿ�ʹ����
	//����ѭ����ʼ��Ϊ0��δʹ�ã�-1(��ʹ��) 1�������ӣ�
	int i;
	//�����ʼ��
	for(i=0;i<MAXNUM;i++){
		htntemps[i].element = NULL;
		htntemps[i].lChild = &htn1;
		htntemps[i].rChild = &htn2;
		htntemps[i].weight = 0;
	}
	for(i=0;i<MAXNUM;i++){
		htntemps_used[i] = 0;
	}

	//������
	for(i=0;i<=subLength;i++){
		htntemps[i].element = htns[i].element;
		htntemps[i].weight = htns[i].weight;
		htntemps_used[i] = -1;
	}
	printf("����������\n");
	for(i=0;i<=subLength;i++){
		printf("%c%d\n",htntemps[i].element,htntemps[i].weight);
	}

	for(;!isFinish(htntemps_used,subLength);){
		subLength++;
		//�ҳ���СȨֵ������������������±�ֵT1T2
		TheYoungestTwo(&T1,&T2,htntemps,htntemps_used);
		//������
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
//���������Ĵ���
void PreMakeTree(HuffmanTree *ht,HTNode *htns,int L){
	ht->root = CreateHT(ht->root,htns,L);
}


//����������//�������
void Encode(HTNode *htn,int** code,int* I,int lr,int L,int i){
	int t;
	if(lr == -1) {for(t=*I;t<=L;t++) code[t][i]= -1;}
	else if(lr == 1) {for(t=*I;t<=L;t++) code[t][i]=1;}
	//������ʱ��0�ű�ʾ������ʹ��-1��Ϊ����֮ǰ����ͳһ
	if(htn->lChild) Encode(htn->lChild,code,I,-1,L,i+1); 
	if(htn->rChild) Encode(htn->rChild,code,++I,1,L,i+1);
	if(htn->lChild && htn->lChild) code[*I][i+1]=0;
	//�ο�ʾ��ͼ����ͬһ�����ı���ֻ���˳��ֵĵ�һ�����ʹ��ѭ�������������������
	//��һ��֮ǰ�ı��볤�ȱ����ڱ��볤�ȳ����ᵼ�±��������ʣ�ಿ�ַǳ�ʼֵ������ǰ���޸Ĺ���
	return;
}
void HTEncode(HuffmanTree *ht,int** code, int L){
	int I=0;//�ڼ�������
	int i=0;//����¼��ʱ������
	int lr = 0;//������-1����������1,��ֵ0
	return Encode(ht->root,code,&I,lr,L,i);
}

//����������
//����������
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

//�������
void PrintHT(HTNode *btn){
	if(btn){
		printf("%d ",btn->weight);
		PrintHT(btn->lChild);
		PrintHT(btn->rChild);
	}
	return;
}

