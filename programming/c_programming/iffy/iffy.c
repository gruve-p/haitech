// program demonstrating the use of
// branching logic
 
#include <stdio.h>
#include <stdlib.h>
 
int main (int argc, char *argv[]) {
   int first;
   int second;
   //first = 7;
   //second = 9;
   first=atoi( argv[1] );
   second=atoi( argv[2] );
   if (first > 7) {
	  printf ("Danish\n");
	  if (second < 3) {
		 printf ("happy");
	  }
   } else {
	  if (second > 8) {
		 printf ("Dan");
	  } else if (second > 4) {
		 printf ("Sally");
	  } else {
		 // print nothing
	  }
   }
 
   if (second < 10) {
	  printf ("ish\n");
   }
 
   if (first > second) {
	  printf ("\nFlag\n");
   } else {
	  printf ("Flag\n");
   }
 
   return EXIT_SUCCESS;
}