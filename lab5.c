#include <stdio.h>
#include <math.h>

int fib(int n)
{
	int i, num[3]={0,1,1};
	for (i=3; i<=n+1; i++)
	{
		num[2]=num[0]+num[1];
		num[0]=num[1];
		num[1]=num[2];
	}
	return num[2];
}

double inp()
{
	double tochn;
	printf("BBeguTe To4HocTb\n");
	while(scanf("%lf", &tochn) != 1)
 	{
        while(getchar() != '\n');          
        printf("ERROR\n");
	}
	if (tochn<0.0)
	{
	       printf("3HaK To4HocTu 6bIJI u3MeHeH\n");
	    	return fabsl(tochn);
	}
	else
		return tochn;
}

double calc(double tochn)
{
	int i=1;
	double result;
	int fibb1, fibb2, fibb3;
	do
	{
	    fibb1=fib(i);
	    fibb2=fib(i+1);
	    fibb3=fib(i+2);
 	    result=fabsl(((double)fibb3/(double)fibb2)-((double)fibb2/(double)fibb1));
 	    i++;
	}
	while(result>tochn);
	return fibb3/fibb2;
}

main(void)
{
	double tochn;
	tochn=inp();
	printf("%.7lf\n", calc(tochn));
}
