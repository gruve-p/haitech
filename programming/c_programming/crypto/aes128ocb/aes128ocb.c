#include <stdint.h>
#include <stdlib.h>
#include "aes128ocb.h"
#include "aes128e.h"
#include <stdio.h>
#include <limits.h>

static const unsigned char ZEROK[16] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

/* Returns the exponent of the msb of 'value' */
static unsigned int msb(unsigned int value);

/* Returns the number of trailing zeros in 'value' */
static unsigned int ntz(unsigned int value);

/*bitshift to the left an array*/
void shiftl(unsigned char *object, int size);

/*double 128b block*/
void double_block(unsigned char *block);

/* Under the 16-byte (128-bit) key at k and the 12-byte (96-bit) nonce at n, encrypt the plaintext at p and store it at c. 
   The length of the plaintext is a multiple of 16 bytes given at len (e.g., len = 2 for a 32-byte p). The length of the
   ciphertext c is (len+1)*16 bytes. */
void aes128ocb(unsigned char *c, const unsigned char *k, const unsigned char *n, const unsigned char *p, const unsigned int len) {
	unsigned int i,j;
	//init Lstar,Ldollar,L0,Li
	unsigned char zero[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	unsigned char Lstar[16],Ldollar[16],L0[16],Li[16];
	aes128e(Lstar, zero, k);
	for (i=0;i<16;i++) {Ldollar[i]=Lstar[i];}
	double_block(Ldollar);
	for (i=0;i<16;i++) {L0[i]=Ldollar[i];}
	double_block(L0);
	//m here is len, c will have same len as p
	//init Nonce, last 96b of Nonce is same as n
	unsigned char Nonce[] = {0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,
							 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	for (i=4;i<16;i++) {Nonce[i]=n[i-4];}
	//init bottom=last 6b of Nonce
	unsigned char bottom = Nonce[15] & 0x3f;
	//init Ktop
	unsigned char tmp[16],tmp2[24],Ktop[16];
	for (i=0;i<16;i++) {tmp[i]=Nonce[i];}
	tmp[15] = tmp[15] & 0xc0;
	aes128e(Ktop, tmp, k);
	//init Stretch
	unsigned char Stretch[24];
	for (i=0;i<16;i++) {Stretch[i]=Ktop[i];}
	for (i=0;i<8;i++) {Stretch[i+16]=Ktop[i] ^ Ktop[i+1];}
	//init Offset0, Offseti
	unsigned char Offset0[16],Offseti[16],oldOffset[16];
	for (i=0;i<24;i++) {tmp2[i]=Stretch[i];}
	for (i=0;i<bottom;i++) {shiftl(tmp2,24);}
	for (i=0;i<16;i++) {Offset0[i]=tmp2[i];}
	//init Checksum0,Checksumi
	unsigned char Checksum0[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
								 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	unsigned char Checksumi[16];
	//other variables used for encryption
	unsigned char Pi[16],Ci[16],Tag[16];//plaintext and cipher block, also the Tag
	//init Offseti and Checksumi
	for (i=0;i<16;i++) {Offseti[i]=Offset0[i];}
	for (i=0;i<16;i++) {Checksumi[i]=Checksum0[i];}
	
	//process the input block, 16B at a time
	//from 1 to len
	for (i=1;i<=len;i++)
	{
		for (j=0;j<16;j++) {Pi[j]=p[j+16*(i-1)];} //load Pi
		//calculate Li
		for (j=0;j<16;j++) {Li[j]=L0[j];}
		for (j=0;j<ntz(i);j++) {double_block(Li);}
		//calculate Offseti
		for (j=0;j<16;j++) {Offseti[j]=Offseti[j] ^ Li[j];}
		//calculate checksum
		for (j=0;j<16;j++) {Checksumi[j]=Checksumi[j] ^ Pi[j];}
		//encrypt
		for (j=0;j<16;j++) {Pi[j]=Pi[j] ^ Offseti[j];}
		aes128e(Ci, Pi, k);
		for (j=0;j<16;j++) {Ci[j]=Ci[j] ^ Offseti[j];}
		//copy Ci to output
		for (j=0;j<16;j++) {c[j+16*(i-1)]=Ci[j];}
	}
	//no C_*, just calculate the tag
	for (j=0;j<16;j++) {tmp[j]=Checksumi[j] ^ Offseti[j] ^ Ldollar[j];}
	aes128e(Tag, tmp, k);
	//append the Tag to ciphertext
	for (j=0;j<16;j++) {c[j+16*len]=Tag[j];}
}

/* Returns the exponent of the msb of 'value' */
static unsigned int msb(unsigned int value) {

	unsigned int index=0;

	while (value >>= 1) { 		/* Loop while greater than one */ 
		index++;
	}
	return index;

}

/* Returns the number of trailing zeros in 'value' */
static unsigned int ntz(unsigned int value) {

	unsigned int zeros=0;

	while (!(value & 0x01)) { 	/* Loop while the lsb is zero */
		value >>= 1;
		/* Shift to the right; that is, observe the next bit. */
		zeros++;
	}
	return zeros;
	
}

/*leftshift array by one bit, must enter the size of array*/
void shiftl(unsigned char *object, int size)
{
   unsigned char *byte;
   for ( byte = object; size--; ++byte )
   {
      unsigned char bit = 0;
      if ( size )
      {
         bit = byte[1] & (1 << (CHAR_BIT - 1)) ? 1 : 0;
      }
      *byte <<= 1;
      *byte  |= bit;
   }
}

/*double 128b block*/
void double_block(unsigned char *block)
{
       unsigned char msb = block[0] & 0x80;
       shiftl(block, 16);
       //if msb set xor last byte with 0x87
       if( (msb) != 0){
       block[15] ^= 0x87;
       }
}