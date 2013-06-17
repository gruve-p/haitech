// author: Hai Phan
// date: 9.2.2013
// print symmetry cross

#include <stdio.h>
#include <stdlib.h>
void printCross(int n);

int main (int argc, char* argv[]) {
	int n=0;
	scanf("%d",&n);
	printCross(n);
	return EXIT_SUCCESS;
}

void printCross(int n) {
	int row=0,col=0;
	if(n%2==1) {
		for(row=0;row<n;row++) {
			for(col=0;col<n;col++) {
				if(col==row || col+row==n-1) {
					printf("#");
				} else {
					printf("-");
				}
			}
			printf("\n");
		}
	}
}