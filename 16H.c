#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int i=0,j=0;
	
	if((*argv[2]!='x') && (*argv[2]!='X'))
	{
		printf("plese enter N x M\n");
		return 0;
	};
if (argc != 4)
	{
		printf("plese enter N x M\n");
		return 0;
	};
	int n = atoi(argv[1]);
	int m = atoi(argv[3]);
//	printf("%d %d\n", n, m);
 	int mas[n][m];
 
 for (i=0; i<n; i++)
 	{	mas[i][0]=1;
 		for (j=0; j<m; j++)
 		mas[0][j]=1;
	 };
for (i=1; i<n; i++)
	{
		for (j=1; j<m; j++)
		mas[i][j]=mas[i][j-1]+mas[i-1][j];
	};
	 for(i=0; i<n; i++) {
	 printf("\n");
	 	for(j=0;j<m;j++)
	 		printf("%10d \t", mas[i][j]);
	 	};
}

