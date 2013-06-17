// author: Hai Phan
// date: 18-01-2013
// swap two integer

#include <stdio.h>
#include <stdlib.h>

void swap (int* first, int* second);

int main (int argc, char* argv[]) {
	int a=5,b=8;
	swap(&a,&b);
	printf("first %d, second %d\n",a,b);
	return EXIT_SUCCESS;
}

void swap (int* first, int* second) {
	int tmp;
	tmp=*first;*first=*second;*second=tmp;
}