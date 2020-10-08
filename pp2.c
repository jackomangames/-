#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {MALLOC, CALLOC, REALLOC} allocmode;

char *readline(FILE* fp, size_t start, size_t step);//считывание слова
void* alloc(void *ptr, int n, size_t size, allocmode mode);//выделение памяти
void check(FILE *file, int *array);

int main()
{
    char* item = NULL;//название файла
    int repeats[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };//массив повторений
    FILE *read = NULL;//файл чтения

    while (!feof(stdin))//пока не ctrl-D
    {
        item = readline(stdin, 32, 2);
        if ((read = fopen(item, "r")) == NULL)
            fprintf(stderr, "Can't open file %s\n", item);
        else
        {
            check(read, repeats);
            fclose(read);
        }
        read = NULL;
        free(item);
        item = NULL;
    }

    return 0;
}

char *readline(FILE* fp, size_t start, size_t step)
{
    int c = 0;
    size_t len = 0;
    char *str = alloc(str, 1, sizeof(char) * start, MALLOC);

    while ((c = fgetc(fp)) != EOF && c != '\n')
    {
        str[len++] = c;
        if(len == start)
            str = alloc(str, 1, sizeof(char) * (start *= step), REALLOC);
    }
    str[len++]='\0';

    return alloc(str, 1, sizeof(char) * len, REALLOC);
}

void* alloc(void *ptr, int n, size_t size, allocmode mode)
{
    switch (mode)
    {
        case MALLOC:
            ptr = malloc(size);
            break;
        case CALLOC:
            ptr = calloc(n, size);
            break;
        case REALLOC:
            ptr = realloc(ptr, size);
            break;
    }

    if (ptr == NULL)
    {
        printf("Memory allocation error\n");
        exit(1);
    }

    return ptr;
}

void check(FILE *file, int *array)
{
    char c;
    while ((c = fgetc(file)) != EOF)
        if (isdigit(c))
            array[c - '0'] = array[c - '0'] + 1;
    for (int i = 0; i < 10; i++)
        fprintf(stderr, "%d: %d\n", i, array[i]);
    fputc('\n', stderr);
    for (int i = 0; i < 10; i++)
        array[i] = 0;
}