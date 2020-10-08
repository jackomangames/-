#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data;
    struct element *next;
} element;

element *list;

void add(int x) {
    element *p;
    if (list == NULL) {
        list = malloc(sizeof(element));
        list->data = x;
        list->next = NULL;
    }
    else {
        p = malloc(sizeof(element));
        p->data = x;
        p->next = list;
        list = p;
    }
}

void print_list() {
    element *p;

    p = list;

    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
}

element* find_max() {
    element *p;
    element *mp;
    int m;

    p = list;

    if (p == NULL) {
        return NULL;
    }

    m = p->data;
    mp = p;

    while (p != NULL) {
        if (p->data > m) {
            m = p->data;
            mp = p;
        }
        p = p->next;
    }
    return mp;
}

element* find_min() {
    element *p;
    element *mp;
    int m;

    p = list;

    if (p == NULL) {
        return NULL;
    }

    m = p->data;
    mp = p;

    while (p != NULL) {
        if (p->data < m) {
            m = p->data;
            mp = p;
        }
        p = p->next;
    }
    return mp;
}

int main(int argv,  char* argc[])
{
    FILE *F;
    int x;

    if (argv == 1) {
        printf("Error: Expected filename as a 1st parameter\n");
        return 0;
    }

    F = fopen(argc[1], "rt");

    if (F == NULL) {
        printf("No such file!\n");
        return 0;
    }

    while (!feof(F)) {
        fscanf(F, "%d", &x);
        add(x);
    }

    printf("List is created:\n");
    print_list();
	printf("\n");
    if (list == NULL) {
        printf("List is empty\n");
        return 0;
    }
    element* p1 = find_max();
    element* p2 = find_min();

    int t;

    t = p1->data;
    p1->data = p2->data;
    p2->data = t;

    printf("After min-max exchange:\n");
    print_list();
    return 0;
}
