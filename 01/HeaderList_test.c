#include "HeaderList.c"
void main()
{
	int m,n;
	int x;
	HeaderList list;
	Init(&list);
	for(m=0,n=10;m<10&&n>0;m++,n--) Insert(&list,m-1,n);//����n������λ��m-1����
	Output(&list);
	Sort(&list);
	Invert(&list);
	Output(&list);
	Delete(&list,0);
	Find(list,0,&x);//��list������ҵ�0��Ԫ�ؼ�¼��x
	Destroy(&list);
	system("pause");
}
