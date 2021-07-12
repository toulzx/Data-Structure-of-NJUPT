
#include<stdlib.h>
//标准库函数头文件，包含malloc()、free()、rand()等
#include<stdio.h>
//标准输入输出头文件，包含printf()、scanf()
typedef char ElemType;


//结构体定义
typedef struct btnode{
	ElemType element;
	struct btnode *lChild;
	struct btnode *rChild;
}BTNode;

typedef struct binarytree{
	BTNode *root;
}BinaryTree;


//先序创建
BTNode* PreCreateBT(BTNode *btn){
	char ch = getchar();
	if(ch == '#'){
		btn = NULL;
	}else{
		btn = (BTNode*)malloc(sizeof(BTNode));
		btn->element = ch;//注意更改Head.h里面的ElemType类型
		btn->lChild = PreCreateBT(btn->lChild);
		btn->rChild = PreCreateBT(btn->rChild);
	}
	return btn;
}
void PreMakeTree(BinaryTree *bt){//要放在PreCreateBT()后面
	bt->root = PreCreateBT(bt->root);
}



//先序遍历
void PreOrder(BTNode *btn){//!!!!如果换成BinaryTree bt会怎样！！！！不行，递归的btn->lChild必须是地址
	if(btn){
		printf("%c ",btn->element);
		PreOrder(btn->lChild);
		PreOrder(btn->rChild);
	}
	return;
}
void PreOrderTree(BinaryTree bt){//书上是BinaryTree *bt
	PreOrder(bt.root);
}
//中序遍历
void InOrder(BTNode *btn){
	if(btn){
		InOrder(btn->lChild);
		printf("%c ",btn->element);
		InOrder(btn->rChild);
	}
	return;
}
void InOrderTree(BinaryTree bt){
	InOrder(bt.root);
}
//后序遍历
void PostOrder(BTNode *btn){
	if(btn){
		PostOrder(btn->lChild);
		PostOrder(btn->rChild);
		printf("%c ",btn->element);
	}
	return;
}
void PostOrderTree(BinaryTree bt){
	PostOrder(bt.root);
}


//二叉树结点个数
int Size(BTNode *btn){
	if(!btn) return 0;
	return Size(btn->lChild)+Size(btn->rChild)+1;
}
int TreeSize(BinaryTree bt){
	return Size(bt.root);
}


//二叉树叶节点个数
int LeavesSize(BTNode *btn){
	if(!btn) return 0;
	else if( btn->lChild || btn->rChild) return LeavesSize(btn->lChild)+LeavesSize(btn->rChild);
	else return 1;
}
int TreeLeavesSize(BinaryTree bt){
	return LeavesSize(bt.root);
}


//求二叉树的高度
int Depth(BTNode *btn) {
     int lh, rh;
     if (!btn) return 0;
     lh = Depth(btn->lChild) + 1;
     rh = Depth(btn->rChild) + 1;
     if (lh > rh) return lh;
     else return rh;
}
int TreeDepth(BinaryTree bt) { return Depth(bt.root); }



//交换所有子树
void Exchange ( BTNode * btn) {
	BTNode *temp;
    if(!btn) return;
    else if( btn->lChild != NULL || btn->rChild != NULL ) {
        temp = btn->lChild;
        btn->lChild = btn->rChild;
        btn->rChild = temp;
        Exchange ( btn->lChild );
        Exchange ( btn->rChild );
	}
}
void TreeExchange(BinaryTree *bt){
     Exchange(bt->root);//注意！！！不用return，这是功能型函数，而非求值型函数
}
