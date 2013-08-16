#include <stdint.h>
#include <stdio.h>
#include "aes128e.h"

/* Multiplication by two in GF(2^8). Multiplication by three is xtime(a) ^ a */
#define xtime(a) ( ((a) & 0x80) ? (((a) << 1) ^ 0x1b) : ((a) << 1) )

//number of column in AES state, a constant
#define Nb 4
//global vars
unsigned char RoundKey[176];
unsigned char Key[16];
unsigned char state[4][4];
//len of key in 32bit word, and bytes
int Nk=4;
int Nkb=16;
//number of cipher rounds
int Nr=10;

/* The S-box table */
static const unsigned char sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
    0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
    0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
    0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
    0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
    0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
    0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
    0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
    0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
    0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
    0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
    0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
    0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
    0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
    0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
    0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
    0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

/* The round constant table (needed in KeyExpansion) */
static const unsigned char rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 
    0x20, 0x40, 0x80, 0x1b, 0x36 };

	void KeyExpansion()
{
	int i,j;
	unsigned char temp[4],k;
	// The first 4 rounds is just to copy 16B key
	for(i=0;i<Nkb;i++)
	{
		RoundKey[i]=Key[i];
	}
	i=4;
    // in the next 40 rounds, each rounds adds 4B to the RoundKey
	while (i < (Nb * (Nr+1)))
	{
					for(j=0;j<4;j++)
					{
						temp[j]=RoundKey[(i-1) * 4 + j];
					}
					if (i % 4 == 0)
					{
						// For rounds 4,8,16... only
                        //RotWord rotates the 4 bytes in a word to the left once.
						//[a0,a1,a2,a3] becomes [a1,a2,a3,a0]
						{
							k = temp[0];
							temp[0] = temp[1];
							temp[1] = temp[2];
							temp[2] = temp[3];
							temp[3] = k;
						}
						// SubWord() uses the sbox to replace byte 	
						{
							temp[0]=sbox[temp[0]];
							temp[1]=sbox[temp[1]];;
							temp[2]=sbox[temp[2]];;
							temp[3]=sbox[temp[3]];;
						}
						//use rcon array
						temp[0] =  temp[0] ^ rcon[i/Nk - 1];
					}
					RoundKey[i*4+0] = RoundKey[(i-4)*4+0] ^ temp[0];
					RoundKey[i*4+1] = RoundKey[(i-4)*4+1] ^ temp[1];
					RoundKey[i*4+2] = RoundKey[(i-4)*4+2] ^ temp[2];
					RoundKey[i*4+3] = RoundKey[(i-4)*4+3] ^ temp[3];
					i++;
	}
	//in the end RoundKey is 176B long
}

//this func just xor the roundkey with the state
void AddRoundKey(int round) 
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			state[j][i] ^= RoundKey[round * Nb * 4 + i * Nb + j];
		}
	}
}

// use sbox to replace bytes in the state
void SubBytes()
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			state[i][j] = sbox[state[i][j]];
		}
	}
}

// This function shifts the rows in the state to the left.
void ShiftRows()
{
	unsigned char temp;
    // Offset = Row number. So row 0 is not shifted.
	// row 1 left  rotate 1 time	
	temp=state[1][0];
	state[1][0]=state[1][1];
	state[1][1]=state[1][2];
	state[1][2]=state[1][3];
	state[1][3]=temp;

	// row 2 left  rotate 2 times	
	temp=state[2][0];
	state[2][0]=state[2][2];
	state[2][2]=temp;
	temp=state[2][1];
	state[2][1]=state[2][3];
	state[2][3]=temp;

	//  row 3 left  rotate 3 times
	temp=state[3][0];
	state[3][0]=state[3][3];
	state[3][3]=state[3][2];
	state[3][2]=state[3][1];
	state[3][1]=temp;
}

//this mixes the colums in the state
void MixColumns()
{
	int i;
	unsigned char old0,old1,old2,old3;
	for(i=0;i<4;i++)
	{	
		//load the old column values
		old0=state[0][i];
		old1=state[1][i];
		old2=state[2][i];
		old3=state[3][i];
        //do matrix multiplication
		state[0][i] = xtime(old0) ^ (xtime(old1)^old1) ^ old2 ^ old3;
		state[1][i] = old0 ^ xtime(old1) ^ (xtime(old2)^old2) ^ old3;
		state[2][i] = old0 ^ old1 ^ xtime(old2) ^ (xtime(old3)^old3);
		state[3][i] = (xtime(old0)^old0) ^ old1 ^ old2 ^ xtime(old3);
	}
}

/* Under the 16-byte key at k, encrypt the 16-byte plaintext at p and store it at c. */
void aes128e(unsigned char *c, const unsigned char *p, const unsigned char *k) {
	//load key
	int i,j,round=0;
	for(i=0;i<Nkb;i++)
	{
		Key[i]=k[i];
	}
	//Copy the input PlainText to state array.
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			state[j][i] = p[i*4 + j];
		}
	}
	//get the RoundKey from original key
	KeyExpansion();
	//before going to the rounds add round key
	AddRoundKey(0);
	
	// The same procedure for first Nr-1 rounds
	for(round=1;round<Nr;round++)
	{
		SubBytes();
		ShiftRows();
		MixColumns();
		AddRoundKey(round);
	}
	// The last round does not have MixColumn
	SubBytes();
	ShiftRows();
	AddRoundKey(Nr);
	// Copy the state array to output cipher
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			c[i*4+j]=state[j][i];
		}
	}
}


