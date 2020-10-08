#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>

void calccel(int base, int numcel)// Функция отвечает за перевод целой части.
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
 	    printf("%x", ost[j-1]);// Вывод результата.
}

void calcdr(int base, float numdr)// Функция отвечает за перевод дробной части.
{
	int i, str;
	while((numdr!=0)&&(str<20))// str - защита от зацикливания в случае иррациональности.
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
        printf("Ошибка. Повторите ввод.\n");
	}
}

int main(void)
{
	setlocale(LC_ALL, "");
	int base, numcel;
	float num, numdr;

	printf("Введите десятичное число\n");
	num=inp();

	printf("Введите основание новой СС от 2 до 16\n");
	base = inp();
	if (base<2 || base>16)
		printf("Ошибка. Введите то 2 до 16\n");
		else 
		{
        printf("Результат: ");
	if (num<0)
		putchar('-');

	num=fabs(num);
	numcel=num; // Выделение целой части.
	numdr=num-numcel; // Выделение дробной части.      
    numdr = num - (int)num;
	calccel(base, numcel);
	if (numdr!=0)
	   printf("."); // Точка для красоты.
	calcdr(base, numdr);
	printf("\n");
}
}

