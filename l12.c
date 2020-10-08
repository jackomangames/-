#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#define LENBUF 512

struct list { char *word;
		      int num;
		      struct list *next;
		   }  *start=NULL;

char *razaraz(int i)
{
	switch(i%10)
	{
		case 2:
			return "раза";
		case 3:
			return "раза";
		case 4:
			return "раза";
		default:
			return "раз";
	}
}

void error(int i)
{
	switch(i)
	{
		case 1:
			printf("Переполнение буфера!");
			exit(1);
		case 2:
			printf("Ошибка выделения памяти");
			exit(2);
		default:
			printf("Неопознанная ошибка");
			exit(999);
	}
}

void inp(char *p_word)
{
	struct list *element;
	if(!check(p_word))
	{
		if((element=(struct list *)malloc(sizeof(struct list)))==NULL)
		    error(2);
		element->next = start;
		start = element;
		element->word = p_word;
		element->num=1;
	}
}

int check(char *p_word)
{
	struct list *p;
	for(p=start;p!=NULL;p=p->next)
		if(!strcmp(p->word, p_word))
		{
			p->num++;
			return 1;
		}
}

void out(void)
{
	struct list *p;
	for(p=start;p!=NULL;p=p->next)
		printf("Слово '%s' встретилось %d %s\n", p->word, p->num, razaraz(p->num));
}

int main(void)
{
	setlocale(LC_ALL,"");
	char buf[LENBUF], *p_word, c;
	int space=0, i=0;
	while((c=getchar())!='~')
		if(isspace(c))
		{
			if(space==0)
			    continue;
			space=0;
			buf[i]='\0';
			if((p_word=(char *)malloc(i*sizeof(char)))==NULL)
			    error(2);
			strcpy(p_word, buf);
			inp(p_word);
			i=0;
		}
		else
		{
			if(i>LENBUF)
		 	    error(1);
			buf[i]=c;
			i++;
			space=1;
		}
	out();	
}
