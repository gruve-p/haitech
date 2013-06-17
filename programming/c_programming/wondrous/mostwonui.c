// author: Hai Phan
// date: 25-01-2013
// find smallest number that has wondrous
// sequence of length bigger than 1000

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int wondrous(uint64_t start);

int main(int argc, char *argv[]) {
	uint64_t x=5649499;
	int lx=0;
	int max=0;
	while(lx<=1000) {
		lx=wondrous(x);
		if(lx>max) {printf ("%"PRIu64" haslen %d\n",x,lx);;max=lx;fflush(stdout);}
		//if(x%1000000==0) {printf("alive\n");fflush(stdout);}
		x++;
	}
	
	return EXIT_SUCCESS;
}

int wondrous(uint64_t start) {
	int result=1;
	uint64_t nxt=start;
	while(nxt>1) {
		if(nxt%2==0) {nxt=nxt/2;}
		else {nxt=3*nxt+1;}
		result++;
	}
	//printf("%lld has len %d\n",start,result);
	return result;
}

