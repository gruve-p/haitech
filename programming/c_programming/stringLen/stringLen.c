// author: Hai Phan
// date: 18-01-2013
// explore memory and
// calculate string length
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NUM_MONTHS 4

int stringLength(char *start);
void testStringLength(void);
int main (int argc, char* argv[]) {
	//char *message = "tree";
	char message[42];
	message[0]='T';
	message[1]='r';
	message[2]='e';
	message[3]='e';
	message[4]=0;
	
	int days[NUM_MONTHS];
	days[0]=31;
	days[1]=29;
	days[2]=30;
	days[3]=30;
	
	int pos=0,sum=0;
	while(pos<NUM_MONTHS) {
		sum=sum+days[pos];
		pos++;
	}
	printf("sum of days is %d\n",sum);
	
	printf("the address of message is %p\n",message);
	printf("lenof %s is %d, first letter is %c ie %c\n",
	        message, strlen(message),*message,message[0]);
	//int outlen = stringLength(message);
	testStringLength();
	return EXIT_SUCCESS;
}
/*
int stringLength(char *start) {
	int length=0;
	char *pointer;
	pointer=start;
	while(*pointer!=0) {
		length++;
		pointer++;
	}
	return length;
}
*/

int stringLength(char *start) {
	int length=0;
	while(start[length]!=0) {
		length++;
	}
	return length;
}

void testStringLength(void) {
	assert(stringLength("Gwen")==4);
	assert(stringLength("tiger")==5);
	assert(stringLength("puppy")==5);
	assert(stringLength(" 42 ")==4);
	assert(stringLength("")==0);
	assert(stringLength("monkey")==6);
	printf("You are awesome!\n");
}