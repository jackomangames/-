#include <stdio.h>
#include <math.h>
#define EPS 0.00001
#define A 0
#define B 2

float F(float x)
{
	return sin(0.5*x) - exp(2*x) - x*x + 10;
}

int main()
{
	float a,b,c,y;
	a=A;
	b=B;
	c=(a+b)/2;
	
	while(fabs(y=F(c))>EPS)
	{
		if(F(c)*F(a)<0)
				b=c;
				else a=c;
				
		c = (a+b)/2;
	}
	printf("%f\n", c);
	return 0;
}
