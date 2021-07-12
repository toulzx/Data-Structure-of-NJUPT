
#include<stdlib.h>
//��׼�⺯��ͷ�ļ�������malloc()��free()��rand()��
#include<stdio.h>
//��׼�������ͷ�ļ�������printf()��scanf()
typedef char ElemType;


//�ṹ�嶨��
typedef struct btnode{
	ElemType element;
	struct btnode *lChild;
	struct btnode *rChild;
}BTNode;

typedef struct binarytree{
	BTNode *root;
}BinaryTree;


//���򴴽�
BTNode* PreCreateBT(BTNode *btn){
	char ch = getchar();
	if(ch == '#'){
		btn = NULL;
	}else{
		btn = (BTNode*)malloc(sizeof(BTNode));
		btn->element = ch;//ע�����Head.h�����ElemType����
		btn->lChild = PreCreateBT(btn->lChild);
		btn->rChild = PreCreateBT(btn->rChild);
	}
	return btn;
}
void PreMakeTree(BinaryTree *bt){//Ҫ����PreCreateBT()����
	bt->root = PreCreateBT(bt->root);
}



//�������
void PreOrder(BTNode *btn){//!!!!�������BinaryTree bt�����������������У��ݹ��btn->lChild�����ǵ�ַ
	if(btn){
		printf("%c ",btn->element);
		PreOrder(btn->lChild);
		PreOrder(btn->rChild);
	}
	return;
}
void PreOrderTree(BinaryTree bt){//������BinaryTree *bt
	PreOrder(bt.root);
}
//�������
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
//�������
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


//������������
int Size(BTNode *btn){
	if(!btn) return 0;
	return Size(btn->lChild)+Size(btn->rChild)+1;
}
int TreeSize(BinaryTree bt){
	return Size(bt.root);
}


//������Ҷ�ڵ����
int LeavesSize(BTNode *btn){
	if(!btn) return 0;
	else if( btn->lChild || btn->rChild) return LeavesSize(btn->lChild)+LeavesSize(btn->rChild);
	else return 1;
}
int TreeLeavesSize(BinaryTree bt){
	return LeavesSize(bt.root);
}


//��������ĸ߶�
int Depth(BTNode *btn) {
     int lh, rh;
     if (!btn) return 0;
     lh = Depth(btn->lChild) + 1;
     rh = Depth(btn->rChild) + 1;
     if (lh > rh) return lh;
     else return rh;
}
int TreeDepth(BinaryTree bt) { return Depth(bt.root); }



//������������
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
     Exchange(bt->root);//ע�⣡��������return�����ǹ����ͺ�����������ֵ�ͺ���
}
