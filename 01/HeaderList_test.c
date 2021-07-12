#include "HeaderList.c"
void main()
{
	int m,n;
	int x;
	HeaderList list;
	Init(&list);
	for(m=0,n=10;m<10&&n>0;m++,n--) Insert(&list,m-1,n);//插入n，插在位置m-1后面
	Output(&list);
	Sort(&list);
	Invert(&list);
	Output(&list);
	Delete(&list,0);
	Find(list,0,&x);//在list里面查找第0个元素记录在x
	Destroy(&list);
	system("pause");
}
