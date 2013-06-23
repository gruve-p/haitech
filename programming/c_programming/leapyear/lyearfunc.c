// hai phan
// 12-02-2013
// function to compute if a user supplied year
// is a leap year or not

 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
#define START_OF_GREG_CALENDAR  1582
 
int isLeapYear(int year);

int main (int argc, const char * argv[]) {
 
   int year;
   int isLeap;
   printf ("please enter the year you are interested in\n");
 
   scanf("%d", &year);
   // notice this only works if the year if >= 1582
   // because of the gregorian calanedara stuff
   assert (year >= START_OF_GREG_CALENDAR);
   isLeap=isLeapYear(year);       
   if (isLeap==1) {
	  printf ("%d is a leap year!\n",year);
   } else {
	  printf ("%d not is a leap year!\n",year);
   }
   
   return EXIT_SUCCESS;
}

int isLeapYear(int year) {
  int result;
  if ((year % 4) == 0 ) {
 
	  if ((year % 100 == 0) && (year % 400 !=0)) {
		 result=0;
	  } else {
		 result=1;
	  }
   } else {
	  result=0;
   }
return result;
}