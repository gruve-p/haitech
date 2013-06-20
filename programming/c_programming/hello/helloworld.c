// author: Hai Phan
// date: 11-01-2013
// print hello world and read from input

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {
printf("helloworld\n");
int x;
x=6.3*10;
printf("enter a number less than 9000\n");
scanf("%d",&x);
printf("my fav number is %d \n",x);

return EXIT_SUCCESS;
}