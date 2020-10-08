#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>

void calccel(int base, int numcel)// ������� �������� �� ������� ����� �����.
{
	int pr, i=0, j, ost[50];
	do
	{
		pr=(numcel/base);
		ost[i]=numcel-pr*base;
		numcel=pr;
		i++;
	}
	while((numcel!=0)&&(i<50));
	for(j=i;j>=1;j--)
 	    printf("%x", ost[j-1]);// ����� ����������.
}

void calcdr(int base, float numdr)// ������� �������� �� ������� ������� �����.
{
	int i, str;
	while((numdr!=0)&&(str<20))// str - ������ �� ������������ � ������ ����������������.
	{
		numdr*=base;
		i=numdr;
		numdr-=i;
		printf("%x", i);
		str++;
	}
}

float inp()
{
	float input;
	while(scanf("%f", &input) != 1)
 	{
        while(getchar() != '\n');
        printf("������. ��������� ����.\n");
	}
}

int main(void)
{
	setlocale(LC_ALL, "");
	int base, numcel;
	float num, numdr;

	printf("������� ���������� �����\n");
	num=inp();

	printf("������� ��������� ����� �� �� 2 �� 16\n");
	base = inp();
	if (base<2 || base>16)
		printf("������. ������� �� 2 �� 16\n");
		else 
		{
        printf("���������: ");
	if (num<0)
		putchar('-');

	num=fabs(num);
	numcel=num; // ��������� ����� �����.
	numdr=num-numcel; // ��������� ������� �����.      
    numdr = num - (int)num;
	calccel(base, numcel);
	if (numdr!=0)
	   printf("."); // ����� ��� �������.
	calcdr(base, numdr);
	printf("\n");
}
}

