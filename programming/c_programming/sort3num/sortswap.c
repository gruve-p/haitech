// author: Hai Phan
// date: 18-01-2013
// sort 3 numbers using swap of two integer

#include <stdio.h>
#include <stdlib.h>

void swap (int* first, int* second);
void sort (int* a, int* b, int* c);

int main (int argc, char* argv[]) {
	srand(time(NULL));
	int num1=rand()%100,num2=rand()%100,num3=rand()%100;
	printf("%d,%d,%d\n",num1,num2,num3);
	sort(&num1,&num2,&num3);
	printf("%d,%d,%d\n",num1,num2,num3);
	return EXIT_SUCCESS;
}

void swap (int* first, int* second) {
	int tmp;
	tmp=*first;*first=*second;*second=tmp;
}

void sort (int* a, int* b, int* c) {
	int tmp1,tmp2,tmp3;
	tmp1=*a;tmp2=*b;tmp3=*c;
	if(tmp1>tmp2) {
		swap(&tmp1,&tmp2);
	}
	if(tmp1>tmp3) {
		swap(&tmp1,&tmp3);
	}
	if(tmp2>tmp3) {
		swap(&tmp2,&tmp3);
	}
	*a=tmp1;
	*b=tmp2;
	*c=tmp3;
}