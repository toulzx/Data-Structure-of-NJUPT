#include "HuffmanTree.c"
void main(){
	HuffmanTree ht1;
	HTNode htns[MAXNUM],htn1,htn2;
	int** code;
	int i,m,n;
	int L=MAXNUM;

	//初始化
	for(i=0;i<MAXNUM;i++){
		htns[i].element = NULL;
		htns[i].lChild = &htn1;
		htns[i].rChild = &htn2;
		htns[i].weight = NULL;
	}

	printf("请输入编码与其对应权值，每组之间无间隔，结束以'#0'为标识，示例：C5B3A2D7E9F12#0\n");

	L=Input(htns,&L);
	if(L==-1){
		printf("INPUT()WRONG!!!");
		return;
	}
		
	PreMakeTree(&ht1,htns,L);
	printf("创建哈夫曼树成功！\n");

	PrintHT(ht1.root);

	code=(int**)malloc((L+1)*sizeof(int*));
	for(i=0;i<(L+1);i++) code[i]=(int*)malloc(MAXNUM*sizeof(int));
	for(m=0;m<L+1;m++){
		for(n=0;n<MAXNUM;n++) code[m][n] = 0;//表示未存放//数组初始化
	}
	for(m=0;m<L+1;m++){
		for(n=0;n<MAXNUM;n++) printf("%d",code[m][n]); 
		printf("\n");
	}
		
	HTEncode(&ht1,code,L);
	printf("→编码←\n");
	for(m=0;m<(L+1);m++){
		for(n=0;n<MAXNUM;n++) if(code[m][n]==-1)printf("0");else if(code[m][n]==1) printf("1");
		printf("\n");
	}
	
	
	printf("请输入一串利用上述编码结果加密过后的数字");
	Decode(ht1.root,&ht1);


	system("pause");
}	
