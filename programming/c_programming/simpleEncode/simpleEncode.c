    /*
    *  simpleEncode.c
    *
    *  reads in a permutation of the alphabet then encodes
    *  lower case letters using that permutation
    *
    *  Created by Hai Phan on 09/02/2013.
    *  Copyright 2013 Licensed under Creative Commons SA-BY-NC 3.0.
    *
    */
     
    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
     
    #define STOP -1
    #define ALPHABET_SIZE 26
	#define FIRSTCHAR 'a'
	#define LASTCHAR 'z'
     
    char encode (int plainChar, char *permuation);
    void testEncode (void);
     
    int main (int argc, char *argv[]) {
     
       testEncode();
     
       char permutation[ALPHABET_SIZE];
     
       scanf ("%s", permutation);
     
       // getchar() reads and returns one character from the keyboard
       // returns -1 when it reads end-of-file character (^D in linux)
       int plainCharacter = getchar();
       while (plainCharacter != STOP) {
          int encodedCharacter = encode (plainCharacter, permutation);
          printf ("%c", encodedCharacter);
          plainCharacter = getchar();
       }
       return EXIT_SUCCESS;
    }
     
    void testEncode (void) {
       assert (encode ('A',"abcdefghijklmnopqrstuvwxyz") == 'A');
       assert (encode ('?',"abcdefghijklmnopqrstuvwxyz") == '?');
       assert (encode (' ',"abcdefghijklmnopqrstuvwxyz") == ' ');
       assert (encode ('\n',"abcdefghijklmnopqrstuvwxyz") == '\n');
     
       assert (encode ('a',"abcdefghijklmnopqrstuvwxyz") == 'a');
       assert (encode ('m',"abcdefghijklmnopqrstuvwxyz") == 'm');
       assert (encode ('z',"abcdefghijklmnopqrstuvwxyz") == 'z');
     
       assert (encode ('a',"bcdefghijklmnopqrstuvwxyza") == 'b');
       assert (encode ('m',"bcdefghijklmnopqrstuvwxyza") == 'n');
       assert (encode ('z',"bcdefghijklmnopqrstuvwxyza") == 'a');
     
       assert (encode ('a',"qwertyuiopasdfghjklzxcvbnm") == 'q');
       assert (encode ('b',"qwertyuiopasdfghjklzxcvbnm") == 'w');
       assert (encode ('z',"qwertyuiopasdfghjklzxcvbnm") == 'm');
    }
     
    char encode (int plainChar, char *permutation) {
      // complete this function
		char result=(char)plainChar;
		if(result>=FIRSTCHAR && result<=LASTCHAR) {
			result=permutation[result-FIRSTCHAR];
		}
	  
	  
	  
	  return result;
    }