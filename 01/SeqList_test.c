#include "SeqList.c"

void main()
{
	int i; 
	ElemType x;
	SeqList list;

	Init(&list,10);
	for(i=0;i<10;i++) Insert(&list,i-1,i);//����i������λ��i-1����
	Find(list,1,&x);
	Output(list);
	printf("\na1��%d\n",x);
	Delete(&list,5);
	Destroy(&list);
	system("pause");
	return;
}


