// author: Hai Phan
// date: 25-01-2013
// print the wondrous length of a number
// can modify to print the wondrous sequence
// for more information search for Collatz conjecture

#include <stdio.h>
#include <stdlib.h>

int wondrous(long long start);

int main(int argc, char *argv[]) {
	long long x=3;
	int lx=0;
	int max=0;
	while(lx<600) {
		lx=wondrous(x);
		if(lx>max) {printf("%lld haslen %d\n",x,lx);max=lx;fflush(stdout);}
		x++;
	}
	
	return EXIT_SUCCESS;
}

int wondrous(long long start) {
	int result=1;
	long long nxt=start;
	while(nxt>1) {
		if(nxt%2==0) {nxt=nxt/2;}
		else {nxt=3*nxt+1;}
		result++;
	}
	//printf("%lld has len %d\n",start,result);
	return result;
}

