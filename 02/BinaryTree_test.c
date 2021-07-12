#include "BinaryTree.c" 
void main(){
	BinaryTree bt1;

	printf("��������������������룬��������#���棺\n");
	PreMakeTree(&bt1);

	PreOrderTree(bt1);
	printf("/nvoid PreOrder()OK!\n");
	InOrderTree(bt1);
	printf("/nvoid InOrder()OK!\n");
	PostOrderTree(bt1);
	printf("/nvoid PostOrder()OK!\n");

	printf("TreeSize is %d.\n",TreeSize(bt1));
	printf("TreeLeavesSize is %d.\n",TreeLeavesSize(bt1));

	TreeExchange(&bt1);
	PreOrderTree(bt1);
	printf("/nvoid PreOrder()OK!\n");

	system("pause");
	return;
}
