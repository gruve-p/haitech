#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "groestl256.h"

#define NUMBYTES 64

/* Multiplication by two in GF(2^8). Multiplication by three is xtime(a) ^ a */
#define xtime(a) ( ((a) & 0x80) ? (((a) << 1) ^ 0x1b) : ((a) << 1) )

static const unsigned char Pconst[64] = {
    0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	
static const unsigned char Qconst[64] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xef, 0xdf, 0xcf, 0xbf, 0xaf, 0x9f, 0x8f,};

static const unsigned char Bmatrix[64] = {
	0x02, 0x02, 0x03, 0x04, 0x05, 0x03, 0x05, 0x07,
	0x07, 0x02, 0x02, 0x03, 0x04, 0x05, 0x03, 0x05,
	0x05, 0x07, 0x02, 0x02, 0x03, 0x04, 0x05, 0x03,
	0x03, 0x05, 0x07, 0x02, 0x02, 0x03, 0x04, 0x05,
	0x05, 0x03, 0x05, 0x07, 0x02, 0x02, 0x03, 0x04,
	0x04, 0x05, 0x03, 0x05, 0x07, 0x02, 0x02, 0x03,
	0x03, 0x04, 0x05, 0x03, 0x05, 0x07, 0x02, 0x02,
	0x02, 0x03, 0x04, 0x05, 0x03, 0x05, 0x07, 0x02};
	
unsigned char Pstate[8][8],Qstate[8][8];
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

static void groestl_pad(unsigned char **m_pad, unsigned long long *len_pad, const unsigned char *m, const unsigned long long n);

static void omega(unsigned char *h, unsigned char *x);
static void pBlock(unsigned char *pout, unsigned char *pin);
static void qBlock(unsigned char *qout, unsigned char *qin);
static void fhash(unsigned char *hout, unsigned char *hin, unsigned char *msg);
static void PAddRoundConst(int round);
static void PShiftBytes();
static void PSubBytes();
static void PMixBytes();
static void QAddRoundConst(int round);
static void QShiftBytes();
static void QSubBytes();
static void QMixBytes();
static unsigned char gfmul(unsigned char a, unsigned char b);

/* Hash the message at m and store the 32-byte hash at h. The length of m in bytes is given at n. */
void groestl256(unsigned char *h, const unsigned char *m, unsigned long long n) {

	unsigned char *m_pad;					/* An array for the padded message */
	unsigned long long len_pad;			/* The length of the padded message (in 64-byte blocks) */
	int i,j;
	unsigned char hi[64],mi[64],him1[64];
	unsigned char h0[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,};
	for (i=0;i<64;i++) {hi[i]=h0[i];}
	groestl_pad(&m_pad,&len_pad,m,n);	/* Perform the message padding */
	
	for (i=0;i<len_pad;i++){
		for (j=0;j<64;j++) {mi[j]=m_pad[64*i+j];him1[j]=hi[j];}
		fhash(hi,him1,mi);
	}
	//get hash output, 256b
	omega(h,hi);
	free(m_pad); 								/* Should be at the end. */
}

/* Performs the message padding. The original message and its length (in bytes) are given at
	m and n, respectively. Reserves memory for the	padded message and stores it at m_pad. 
	The length (in 512-bit blocks) is stored at len_pad. */
static void groestl_pad(unsigned char **m_pad, unsigned long long *len_pad, const unsigned char *m, const unsigned long long n) {

	/* Compute the length of the padded message (in 64-byte blocks) */
	*len_pad = (n*8 + 65 + (-n*8 - 65) % 512) / 512;	

	/* Allocate memory for the padded message */
	*m_pad = (unsigned char*) calloc(*len_pad*NUMBYTES, sizeof(unsigned char));

	/* Copy m to m_pad */
	memcpy(*m_pad, m, n);

	/* Add a bit to the end of the original message */
	(*m_pad)[n] = 0x80;

	/* Add the 64-bit representation of ((N+w+65)/512) in the end of m_pad */
	(*m_pad)[*len_pad*NUMBYTES-8] = (unsigned char) (*len_pad >> 56);
	(*m_pad)[*len_pad*NUMBYTES-7] = (unsigned char) (*len_pad >> 48);
	(*m_pad)[*len_pad*NUMBYTES-6] = (unsigned char) (*len_pad >> 40);
	(*m_pad)[*len_pad*NUMBYTES-5] = (unsigned char) (*len_pad >> 32);
	(*m_pad)[*len_pad*NUMBYTES-4] = (unsigned char) (*len_pad >> 24);
	(*m_pad)[*len_pad*NUMBYTES-3] = (unsigned char) (*len_pad >> 16);
	(*m_pad)[*len_pad*NUMBYTES-2] = (unsigned char) (*len_pad >> 8);
	(*m_pad)[*len_pad*NUMBYTES-1] = (unsigned char) (*len_pad);

}

/* take 512b input, generate 256b hash */
static void omega(unsigned char *h, unsigned char *x) {
	unsigned char px[64];
	int i;
	pBlock(px,x);
	for (i=0;i<32;i++) {h[i]=px[i+32]^x[i+32];}
}

/* P function take 512b input, generate 512b output */
static void pBlock(unsigned char *pout, unsigned char *pin) {
	int i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			Pstate[j][i] = pin[i*8 + j];
		}
	}
	
	for (i=0;i<10;i++) {
		PAddRoundConst(i);
		PSubBytes();
		PShiftBytes();
		PMixBytes();
	}
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			pout[i*8 + j] = Pstate[j][i];
		}
	}
}

/* Q function take 512b input, generate 512b output */
static void qBlock(unsigned char *qout, unsigned char *qin) {
	int i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			Qstate[j][i] = qin[i*8 + j];
		}
	}
	
	for (i=0;i<10;i++) {
		QAddRoundConst(i);
		QSubBytes();
		QShiftBytes();
		QMixBytes();
	}
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			qout[i*8 + j] = Qstate[j][i];
		}
	}
}
/* compression function f, input 512b h and 512b m, output 512b hout*/
static void fhash(unsigned char *hout, unsigned char *hin, unsigned char *msg) {
	unsigned char hplusm[64],phpm[64],qm[64];
	int i;
	for (i=0;i<64;i++) {hplusm[i]=hin[i]^msg[i];}
	pBlock(phpm,hplusm);
	qBlock(qm,msg);
	for (i=0;i<64;i++) {hout[i]=phpm[i]^qm[i]^hin[i];}
}

//this func just xor the round const with Pstate
void PAddRoundConst(int round) 
{
	int i,j;
	unsigned char Pconsti[8][8];
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			Pconsti[i][j]=Pconst[j+8*i];
		}
	}
	// calculate round constant
	for (i=0;i<8;i++) {Pconsti[0][i]=Pconsti[0][i]^round;}
	//add the p round const to p state
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			Pstate[j][i] ^= Pconsti[j][i];
		}
	}
}

//this func just xor the round const with Qstate
void QAddRoundConst(int round) 
{
	int i,j;
	unsigned char Qconsti[8][8];
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			Qconsti[i][j]=Qconst[j+8*i];
		}
	}
	// calculate round constant
	for (i=0;i<8;i++) {Qconsti[7][i]=Qconsti[7][i]^round;}
	//add the q round const to q state
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			Qstate[j][i] ^= Qconsti[j][i];
		}
	}
}

// use sbox to replace bytes in Pstate
void PSubBytes() {
	int i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			Pstate[i][j] = sbox[Pstate[i][j]];
		}
	}
}

// use sbox to replace bytes in Qstate
void QSubBytes() {
	int i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			Qstate[i][j] = sbox[Qstate[i][j]];
		}
	}
	
}

// This function shifts the rows in the Pstate to the left.
void PShiftBytes()
{
	unsigned char temp;
	unsigned char old[8][8];
	int i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			old[i][j] = Pstate[i][j];
		}
	}
    // Offset = Row number. So row 0 is not shifted.
	// row i left rotate i times
	for (i=0;i<8;i++) 
	{
		for (j=0;j<8;j++)
		{
			Pstate[i][j]=old[i][(j+i)%8];
		}
	
	}
}

// This function shifts the rows in the Qstate to the left.
void QShiftBytes()
{
	unsigned char temp;
	unsigned char old[8][8];
	int i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			old[i][j] = Qstate[i][j];
		}
	}
    // row i will shift left (rowno*2+1)%9 times
	// this includes row 0
	for (i=0;i<8;i++) 
	{
		for (j=0;j<8;j++)
		{
			Qstate[i][j]=old[i][(j+((2*i+1)%9))%8];
		}
	}
}

// multiplication in GF field, return a byte
unsigned char gfmul(unsigned char a, unsigned char b) {
        unsigned char p = 0;
		unsigned char temp;
		int i,j;
        unsigned char mulby=b;
        for (i = 0; i < 8; i++) {
				if (mulby & 1) 
				{
				temp=a;
				for (j=0;j<i;j++) {temp=xtime(temp);}
				p^=temp;
				}
				mulby >>= 1;
        }
        return p;
}
//mix every column in Pstate
static void PMixBytes() {
	int i,j,k;
	unsigned char sum;
	unsigned char old[8][8];
	for (i=0;i<8;i++) 
	{
		for (j=0;j<8;j++) {old[i][j]=Pstate[i][j];}
	}
	for (i=0;i<8;i++) //column i
	{
		for (j=0;j<8;j++) //row j
		{
			sum=0;
			for (k=0;k<8;k++) {sum^=gfmul(Bmatrix[8*j+k],old[k][i]);}
			Pstate[j][i]=sum;
		}
	}
}

//mix every column in Qstate
static void QMixBytes() {
	int i,j,k;
	unsigned char sum;
	unsigned char old[8][8];
	for (i=0;i<8;i++) 
	{
		for (j=0;j<8;j++) {old[i][j]=Qstate[i][j];}
	}
	for (i=0;i<8;i++) //column i
	{
		for (j=0;j<8;j++) //row j
		{
			sum=0;
			for (k=0;k<8;k++) {sum^=gfmul(Bmatrix[8*j+k],old[k][i]);}
			Qstate[j][i]=sum;
		}
	}
}
