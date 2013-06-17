    /*
    *  charfreq.c
    *
    *  reads in characters from standard input until it reaches EOF
    *  merge upper and lower case versions of letters.
    *  Ignore any characters that are not letters.
	*  
    *  Created by Hai Phan on 09/02/2013.
    *  ./charfreq < /usr/share/dict/words
    */
     
    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>

    #define ALPHABET_SIZE 26
	#define FIRSTCHAR 'a'
	#define LASTCHAR 'z'
	#define FIRSTUCHAR 'A'
	#define LASTUCHAR 'Z'


	void charcount(int *len, char c);
	void charStat(int *len);
	
    int main (int argc, char *argv[]) {
		int count[26]={0};
		char c;
     
       // getchar() reads and returns one character from the keyboard
       // returns -1 when it reads end-of-file character (^D in linux)
       while (!feof(stdin)) {
			c = getchar();
			//putchar(c);
			charcount(count,c);
       }
	   charStat(count);
       return EXIT_SUCCESS;
    }
     
	void charcount(int *len, char c) {
		if(c>=FIRSTCHAR && c<=LASTCHAR) {
			len[c-FIRSTCHAR]=len[c-FIRSTCHAR]+1;
		}
		if(c>=FIRSTUCHAR && c<=LASTUCHAR) {
			len[c-FIRSTUCHAR]=len[c-FIRSTUCHAR]+1;
		}
	}

	void charStat(int *len) {
		int c=FIRSTCHAR;
		int total=0;
		for(c=0;c<26;c++) {total=total+len[c];}
		for(c=FIRSTCHAR;c<=LASTCHAR;c++) {
			printf("%c-%d/%d\n",c,len[c-FIRSTCHAR],total);
		}
	}