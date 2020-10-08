#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
//#include <malloc.h>
FILE *fp;


int infile(char* inputfile)
{
 fp=fopen(inputfile, "r+");
 if (fp==NULL)
  printf("FILE NOT FOUND");
return 0;
}

int main(int argc, char* argv[])
{
if ((argc<3)||(argc>5)){
  printf("Input error\n");
  return(1);
 }
 char* buf;
 char* inputfile, ch;
 int k=0, i=0, j=0, N=0;
 int seed=0, x=0;
 int opt=0;
  while((opt=getopt(argc, argv, "s:f:"))!=-1)
    {
  	switch(opt)
  	{
     	 case 's': seed=atoi(optarg); break;
     	 case 'f': inputfile=optarg; break;        
      	case '?': break;
 	 }
    }
inputfile=argv[3]; //имя файла
  seed=atoi(argv[4]); //зерно псевдослучайной последовательности
fp=fopen(inputfile, "r+");
if(fp==NULL)
	{
		inputfile=argv[4];
		seed=atoi(argv[3]);
	}
 srand(seed);
 infile(inputfile);
 while((ch=fgetc(fp)) != EOF)
  {
   N++;
  }
 buf=(char*)malloc(N*sizeof(char));
 rewind(fp);
 while((ch=fgetc(fp)) != EOF)
  {
   buf[j]=ch;
   j++;
  }
 rewind(fp);
 for(k=0; k<N; k++)
  {
   if(isdigit(buf[k])!=0)
    {
     fputc(buf[k], fp);
     fputc('\\', fp);
     fputc('g', fp);
     x=rand()%9;
     fprintf(fp, "%d", x);
     fprintf(stdout, "%d", x);
    }
   else
    {
     fputc(buf[k], fp);
    }
  }
  printf("\n");
 fclose(fp);
 free(buf);
	return 0;
}


