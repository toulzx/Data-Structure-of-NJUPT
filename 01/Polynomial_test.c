//����
/*
	7 12
	-5 6
	6 3
	9 0
	0 0
*/
/*
	2 10
	4 6
	-6 3
	5 0
	0 0
*/


#include "Polynomial.c"

void main(){
	int choose;
	Polynominal pn1,pn2;

	while(1){
		Init(&pn1);
		Init(&pn2);

		Input(&pn1);
		Output(&pn1);
		Input(&pn2);
		Output(&pn2);
	
		printf("\n\n��ѡ�������1��� 2���\n");
		scanf("%d",&choose);
		if(choose == 1) {
			Add(&pn1,&pn2);
			printf("����ʽ��ӽ�����£�");
			Output(&pn1);
		}
		else if(choose == 2) Mutiply(&pn1,&pn2);
		else printf("������䡣\n");

		Destroy(&pn1);
		Destroy(&pn2);
	}
}


