// author: Hai Phan
// date: 22-05-2013
// pi estimation

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
void calpi (long tries);
double fRand(double fMin, double fMax);

int main (int argc, char* argv[]) {
srand(time(NULL));
long times=pow(10,9);
calpi(times);
return EXIT_SUCCESS;
}

void calpi (long tries) {
	long i;
	double x,y;
	long cnt=0;
	for(i=0;i<tries;i++) {
		x=fRand(0.0, 1.0);
		y=fRand(0.0, 1.0);
		if(x*x+y*y<=1) {
			cnt+=1;
		}
	}
	double pii = (double) cnt / tries;
	printf("pi estimation: %f\n",pii*4);
	//printf("cnt: %d\n",cnt);
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / (double) RAND_MAX;
    return fMin + f * (fMax - fMin);
}