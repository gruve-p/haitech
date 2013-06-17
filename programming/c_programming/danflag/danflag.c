// author: Hai Phan
// date: 18-01-2013
// print Danish flag

#include <stdio.h>
#include <stdlib.h>
#define LINE 2
#define DROW 5
#define DCOL 12
void showDanish (void);

int main (int argc, char* argv[]) {
showDanish();
return EXIT_SUCCESS;
}

void showDanish (void) {
	int row,col;
	for(row=0;row<DROW;row++) {
		if(row!=LINE) {
			for(col=0;col<DCOL;col++) {
				if(col!=2) {
					printf("*");
				} else {
					printf(" ");
				}
			}
		}
		printf("\n");
	}
}