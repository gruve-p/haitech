// author: Hai Phan
// date: 23-01-2013
// test what happens when array
// index out ouf bound

#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

int main (int argc, char* argv[]) {
	int canaryA = 42;
	int testArray[10] = {0,1,2,3,4,5,6,7,8,9};
	int canaryB = 99;
	int sum=canaryA+canaryB;
	sum=5;
	int index;
	printf("canA %p, test %p, canB %p\n",&canaryA,testArray,&canaryB);
	
	while(sum>0) {
		printf ("Enter an array index between 0 and 9\n");
		scanf ("%d", &index);
		printf ("testArray[%d]=%d,\n",index, testArray[index]);
	}
	
	return EXIT_SUCCESS;
}
