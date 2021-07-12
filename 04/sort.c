#include<stdio.h>		//��׼���������
#include<stdlib.h>		//�ں��������
#include<time.h>		//�ں�ʱ�亯���������Ż������������


typedef int KeyType;	//�ؼ������Ͷ�Ϊint��
typedef char DataType;	//�����������ݶ�Ϊchar��
typedef int BOOL;

#define CASES	5		//�㷨����
#define MAXSize 500     //�ؼ��ָ���
#define TRUE 1
#define FALSE 0
#define TESTNUM 100	//���Դ���

typedef struct entry{
	KeyType key;
	DataType data;
}Entry;
typedef struct list{
	int n;
	Entry D[MAXSize];
}List;




//���ú���
void Swap(List* list, int m, int n)				//���鱾��ͬ
{
	Entry temp;
	if(m != n){
		temp = list->D[m];
		list->D[m] = list->D[n];
		list->D[n] = temp;
	}
	return;
}

//��ѡ������SelectSort(���鱾��ͬ)
int FindMin(List list, int startIndex)
{
	int i,temp;
	for(i = startIndex, temp = startIndex; i<list.n; i++){
		if(list.D[temp].key > list.D[i].key) temp = i;
	}
	return temp;
}
void SelectSort(List* list)
{
	int i,startIndex;
	for(i = 0, startIndex = 0; i < list->n-1; i++, startIndex++)  Swap(list, i, FindMin(*list,startIndex));
	return;
}


//ֱ�Ӳ�������
void InsertSort(List* list){
	int i,j;
	Entry insertItem;
	for(i = 1; i< list->n; i++){
		insertItem = list->D[i];
		for(j = i-1; j >= 0; j--){
			if(insertItem.key < list->D[j].key) list->D[j+1] = list->D[j];
			else break;
		}
		list->D[j+1] = insertItem;
	}
	return;
}


//ð������
void BubbleSort(List *list){
	int i, j;
	for(i = list->n-1; i > 0; i--){
		BOOL isSwap = FALSE;
		for(j = 0; j < i; j++){
			if(list->D[j].key > list->D[j+1].key){
				Swap(list, j, j+1);  //Swap()���鱾��ͬ
				isSwap  = TRUE;
			}
		}
		if(!isSwap) break;			//�������û�н���Ԫ�أ���������ɡ�
	}
}


//���������㷨
int Partition(List* list, int low, int high){
	int i=low, j=high+1;
	Entry pivot = list->D[low];
	do{
		do{i++;}while(i<=high  &&  list->D[i].key < pivot.key);
		do{j--;}while(i>=low  && list->D[j].key > pivot.key);
		if(i < j) Swap(list, i, j);		//Swap()���鱾��ͬ
	}while(i < j);
	Swap(list, low, j);
	return j;
}
void quickSort(List *list, int low, int high){
	int k;
	if(low < high){
		k = Partition(list, low, high);
		quickSort(list, low, k-1);
		quickSort(list, k+1, high);
	}
}
void QuickSort(List* list){
	quickSort(list, 0, list->n-1);
}


//��·�ϲ��㷨
void Merge(List* list, Entry* temp, int low, int n1, int n2) {
	int i = low, j = low + n1;
	while (i <= low + n1 - 1 && j <= low + n1 + n2 - 1) {
		if (list->D[i].key <= list->D[j].key)
			*temp++ = list->D[i++];
		else *temp++ = list->D[j++];
	}
	//��ʣ�����ӽ�ȥ����Ϊʣ��D[i]���л���D[j]����
	while (i <= low + n1 - 1)
		*temp++ = list->D[i++];
	while (j <= low + n2 + n1 - 1)
		*temp++ = list->D[j++];
}
void MergeSort(List* list){
	Entry temp[MAXSize];
	int low, n1, n2, i, size = 1;
	//��ʣ������������1 <=> ���д�СsizeС������
	while(size < list->n){
		low = 0;
		//������һ������ʱ���ϲ�
		while(low + size < list->n){
			n1 = size;
			//�ж���������к��ߵĳ����Ƿ�Ϊsize
			if(low +size*2 < list->n) n2 = size;
			else n2 = list->n-low-size;
			Merge(list, temp+low, low, n1, n2);
			low += n1 + n2;
		}
		//����һ��D[]����˳��
		for(i = 0; i < low; i++)  list->D[i] = temp[i];
		//׼����һ�κϲ�
		size *= 2;
	}
}



//C������������ɽ̳̣�
//http://c.biancheng.net/view/2043.html
//https://blog.csdn.net/qq_44620773/article/details/103985380

//�ṹ���ʼ������ԭ��
//https://www.cnblogs.com/Fsiswo/p/9291458.html

//��¼��������ʱ��ķ�����
//https://blog.csdn.net/y_dd6011/article/details/86408339

//���뽫������ʱת����s��ʹ��CLK_TCK��˵�����£�
//https://baike.baidu.com/item/CLK_TCK/2766625?fr=aladdin



int main(){
	List* list = (List*)malloc(sizeof(List));	//ʹ�ýṹ��ָ����Ҫ����ռ䣬��ͨ����List list���á�
	int i,j,k;		//ѭ������
	int rnum;	//���������
	clock_t start, stop;	//clock_t��clock()�������صı������� 
	double duration;		//��¼�����Ժ������е�ʱ�䣬����Ϊ��λ

	//��ʼ��
	list->n = MAXSize;
	printf("#define MAXSize %d\n#define TESTNUM %d\n",MAXSize,TESTNUM);
	

	//������ʱ
	for(i = 1; i <= CASES; i++){
		//��ʼ��
		srand((unsigned)time(NULL));//�����ŵ�����for(k)ѭ������һ��/��Ц

		start = clock();
		//�ظ�������������в��Խ��
		for (j=0; j<TESTNUM; j++){
			for(k = 0; k < list->n; k++){
				rnum = rand();
				list->D[k].key = rnum;

				//printf("%d\t",list->D[k].key);
				//if(!((k+1)%10)) printf("\n\n");			//!��%���ȼ��ߣ��ǵü�����

				//��ܿ�����һ���ʵ�
				//if(k%3 == 1)	list->D[k].data = rnum%2? 90:122;
				//else if(k%3 == 2)	list->D[k].data = rnum%2? 88:120;
				//else	list->D[k].data = rnum%2? 76:108;
			}
			switch(i){
				case 1: SelectSort(list); break;
				case 2: InsertSort(list); break;
				case 3: BubbleSort(list); break;
				case 4:  QuickSort(list); break;
				case 5:  MergeSort(list); break;
			}
		}
		stop = clock();

		duration =((double)(stop - start))/TESTNUM; //�����ٳ�һ��CLK_TCK���ѵ�λ��ms���s
		switch(i){
			case 1: printf("\nSelectSort:\n"); break;
			case 2:	printf("\nInsertSort:\n"); break;
			case 3: printf("\nBubbleSort:\n"); break;
			case 4:  printf("\nQuickSort:\n"); break;
			case 5:  printf("\nMergeSort:\n"); break;
			}
		printf("ticks = %f\n", (double)(stop - start));
		//printf("duration = %6.2e\n", duration);

		//���һ�²ʵ���
		//printf("\n�����ַ���\n");
		//for(k = 0; k < list->n; k++) printf("%c",list->D[k].data);
		//����������
		//printf("\n\n�����\n");
		//for(k = 0; k < list->n; k++) {
		//	printf("%d\t",list->D[k].key);
		//	if(!((k+1)%10)) printf("\n\n");
		//}
		//printf("\n");
	}

	system("pause");
	return 0;
}


/*

COPY RIGHT BY touuu

Reference material:
Data-Structure for C of NJUPT (Edition2)
http://c.biancheng.net/view/2043.html
https://blog.csdn.net/qq_44620773/article/details/103985380
https://www.cnblogs.com/Fsiswo/p/9291458.html
https://blog.csdn.net/y_dd6011/article/details/86408339
https://baike.baidu.com/item/CLK_TCK/2766625?fr=aladdin

Thanks~

*/ 
