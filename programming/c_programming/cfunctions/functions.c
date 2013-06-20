// author: Hai Phan
// date: 07-02-2013
// testing some c functions
// check out printing,
// define  constant
// memory allocation

#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#define NUM_UNDERGRADS 210
#define NUM_POSTGRADS  24
#define NUM_STUDENTS   NUM_POSTGRADS+NUM_UNDERGRADS

int main (int argc, char* argv[]) {
	double height=2.31;
	printf("num of stud: %d\n",NUM_STUDENTS);
	//exampleOne();
	//exampleDouble(height);
	//exampleHex();
	//exampleThree();
	int x,mys;
	mys=scanf("%d",x);
	printf("scanf returns %08X, address of x %p\n",&x);
	exampleFour();
	return EXIT_SUCCESS;
}

void exampleOne (void) {
	printf("Example 1\n");
	printf("EXITSUCCESS is %d\n",EXIT_SUCCESS);
	return;
}

void exampleDouble (double meters) {
	//double height=1.84;
	printf("your height is: %f\n",meters);
}

void exampleHex (void) {
	long height=1234;
	printf("your height is: %lx\n",height);
}

void exampleThree (void) {
	printf("Example 3\n");
	char letter;
	printf("sizeof(letter)=%ld\n",sizeof(letter));
	return;
}

void exampleFour(void) {
	printf("Example 4\n");
	int x = 1,y=2,z=3;
	int *address;//address of the first cell of an int
	
	address=&x;
	printf("address of x is %p\n",&x);
	printf("the value stored at %p is %u\n",address,*address);
	
	address=&y;
	printf("address of y is %p\n",address);
	printf("the value stored at %p is %u\n",address,*address);
	
	address=&z;
	printf("address of y is %p\n",address);
	printf("the value stored at %p is %u\n",address,*address);
}
