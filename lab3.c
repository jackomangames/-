#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

int main()
{
      float a, b, c, d;
      setlocale(LC_ALL, "");
      printf("������� ������������\n");
      while(scanf("%f%f%f", &a, &b, &c) != 3)
      {
          while(getchar() != '\n');          
          printf("�������� ���� ������ \n");
      }
      
      if (a==0)
      {
      	printf("X ����� %.f", -c/b);
      }
      else
      {
	   	   d=(b*b)-(4*a*c);
	   	   
     	   if (d==0)
      	   {
 	 	   	  printf("X ����� %f\n", -b/(2*a));
           }
           else
           {
  	       	   if (d>0) 
   	   	   	   {
	       	   	  dpl(b, d, a);
   	   		   }
   	  	       else
   	   		   {
   	   	  	       dmn(b, d, a);
   	           }
           }
      }
}

void dpl(double b, double d, double a)
{
	printf("����� ����� %.2f %.2f", ((-b+sqrt(d))/(2*a)), ((-b-sqrt(d))/(2*a)));
}

void dmn(double b, double d, double a)
{
	printf("X1 ����� %.3f + %.3fi ", -b/(2*a), sqrt(fabs(d))/(2*a));
	printf("X2 ����� %.3f - %.3fi ", -b/(2*a), sqrt(fabs(d))/(2*a));
}


