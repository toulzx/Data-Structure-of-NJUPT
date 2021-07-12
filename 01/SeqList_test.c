#include "SeqList.c"

void main()
{
	int i; 
	ElemType x;
	SeqList list;

	Init(&list,10);
	for(i=0;i<10;i++) Insert(&list,i-1,i);//插入i，插在位置i-1后面
	Find(list,1,&x);
	Output(list);
	printf("\na1是%d\n",x);
	Delete(&list,5);
	Destroy(&list);
	system("pause");
	return;
}


