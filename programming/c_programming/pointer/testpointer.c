// author: Hai Phan
// date: 15-01-2013
// modify a variable passed into a function

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void genRan(int* number) {
	*number=rand()%100;
	printf("inside %i\n",*number);
}

int main (int argc, const char* argv[]) {
   srand(time(NULL));
   int i=10;
   genRan(&i);
   printf("%d\n",i);
   
   return 0;
}
