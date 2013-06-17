// hai phan
// created 21.01.2013
// program to sort 3 numbers
 
 
#include <stdio.h>
#include <stdlib.h>
 
#define START_OF_GREG_CALENDAR  1582
 
int main (int argc, const char * argv[]) {
	int num1,num2,num3;
	scanf("%d %d %d",&num1,&num2,&num3);
	if (num1<num2) {
		if (num1<num3) {
			if (num2<num3) {
				printf("%d\n%d\n%d\n",num1,num2,num3);
			} else {
				printf("%d\n%d\n%d\n",num1,num3,num2);
			}
		} else {
			if (num3<num2) {
				printf("%d\n%d\n%d\n",num3,num1,num2);
			}
		}
	} else {
		if (num2<num3) {
			if (num1<num3) {
				printf("%d\n%d\n%d\n",num2,num1,num3);
			} else {
				printf("%d\n%d\n%d\n",num2,num3,num1);
			}
		} else {
			printf("%d\n%d\n%d\n",num3,num2,num1);
		}
	}
	return EXIT_SUCCESS;
}