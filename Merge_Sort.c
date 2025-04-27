#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct tData {
    struct tData *next;
    int data;
} tData;

void AddToStack(tData** head, int data)
{
    tData* p = (tData*)malloc(sizeof(tData));
    p->data = data;
    p->next = *head;
    *head = p;
}

void fillIncStack(tData **head, int n)
{
    for (int i = 1; i <= n; i++)
    {
        AddToStack(head, i);
    }
}

void fillDecStack(tData** head, int n)
{
    for (int i = n; i >= 1; i--)
    {
        AddToStack(head, i);
    }
}

void fillRanStack(tData** head, int n)
{
    srand(time(NULL));
    for (int i = 1; i <= n; i++)
    {
        int ranNum = rand() % 100;
        AddToStack(head, ranNum);
    }
}

void AddToQueue(tData** head, tData** tail, int data)
{
    tData *p = (tData *)malloc(sizeof(tData));
    p->data = data;
    p->next = NULL;

    if (*tail == NULL)
    {
        *head = *tail = p;
    }
    else
    {
        (*tail)->next = p;
        *tail = p;
    }
}

void fillIncQueue(tData** head, tData** tail, int n)
{
    for (int i = 1; i <= n; i++)
    {
        AddToQueue(head, tail, i);
    }
}

void fillDecQueue(tData** head, tData** tail, int n)
{
    for (int i = n; i >= 1; i--)
    {
        AddToQueue(head, tail, i);
    }
}

void fillRanQueue(tData** head, tData** tail, int n)
{
    srand(time(NULL));
    for (int i = 1; i <= n; i++)
    {
        int ranNum = rand() % 100;
        AddToQueue(head, tail, ranNum);
    }
}

void delStackElement(tData** head)
{
    if (head != NULL)
    {
        tData *p = *head;
        *head = p->next;
        free(p);
    }
}

void print_list(tData *head)
{
    tData *p = head;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int checksum(tData *head)
{
    int sum = 0;
    tData *p = head;
    while (p != NULL)
    {
        sum += p->data;
        p = p->next;
    }
    return sum;
}

int series(tData *head)
{
    if (head == NULL)
    {
        return 0;
    }

    int count = 1;
    tData *p = head;

    while (p->next != NULL)
    {
        if (p->data > p->next->data)
        {
            count++;
        }
        p = p->next;
    }
    return count;
}

void clear(tData *head)
{
    tData *p = head;
    while (p != NULL)
    {
        tData *temp_p = p;
        p=p->next;
        free(temp_p);
    }
}

typedef struct {
    tData *head;
    tData *tail;
} tQueue;

void InitializeQueue(tQueue *q) {
    q->head = q->tail = NULL;
}

void Transfer(tData** head, tData** tail, tData** ls) {
    if (*head == NULL) {
        *head = *tail = *ls;
    } else {
        (*tail)->next = *ls;
        *tail = *ls;
    }
    *ls = (*ls)->next;
    (*tail)->next = NULL;
}

void MergeSeries(tData **a, int q, tData **b, int r, tQueue *c, int *comp, int *mv) {
    while (q > 0 && r > 0 && *a != NULL && *b != NULL) {
        (*comp)++;
        if ((*a)->data <= (*b)->data) {
            Transfer(&c->head, &c->tail, a);
            q--;
        } else {
            Transfer(&c->head, &c->tail, b);
            r--;
        }
        (*mv)++;
    }

    while (q > 0 && *a != NULL) {
        Transfer(&c->head, &c->tail, a);
        q--;
        (*mv)++;
    }

    while (r > 0 && *b != NULL) {
        Transfer(&c->head, &c->tail, b);
        r--;
        (*mv)++;
    }
}

void SplitLists(tData *head, tData **a, tData **b, int *n, int *mv) {
    *a = head;
    *b = head->next;
    *n = 1;
    tData *k = *a;
    tData *p = *b;

    while (p != NULL) {
        (*n)++;
        k->next = p->next;
        k = p;
        p = p->next;
        (*mv)++;
    }
    if (k != NULL) {
        k->next = NULL;
    }
}

void MergeSort(tData **S, int *comp, int *mv) {
    if (*S == NULL || (*S)->next == NULL) {
        return;
    }

    tQueue c[2];
    tData *a, *b;
    int n;
    SplitLists(*S, &a, &b, &n, mv);

    int p = 1;
    while (p < n) {
        InitializeQueue(&c[0]);
        InitializeQueue(&c[1]);
        int i = 0, m = n;

        while (m > 0) {
            int q = (m >= p) ? p : m;
            m -= q;
            
            int r = (m >= p) ? p : m;
            m -= r;

            MergeSeries(&a, q, &b, r, &c[i], comp, mv);
            i = 1 - i;
        }

        a = c[0].head;
        b = c[1].head;
        p = 2 * p;
    }

    *S = c[0].head;
    if (c[0].tail != NULL) {
        c[0].tail->next = NULL;
    }
}

int main() {
    tData *A = NULL;
    int Cfact = 0;
    int Mfact = 0;

    int count = 7; 
    int Report = 0;

    printf(" ________________________________________________________________\n");
    printf("|       |     M + C     |             |            |             |\n");
    printf("|   N   |     Theor     |     Upper   |    Down    |    Rand     |\n");
    printf("|_______|_______________|_____________|____________|_____________|\n");


    int Trand[count], Tinc[count], Tdec[count], Ttheor[count];
    int sizes[count];
    
    for (int j = 0; j < count; j++) {
        int size = 100 * (j + 1);
        sizes[j] = size;

        fillRanStack(&A, size);
        if (Report) { 
            printf("Исходный случайный список:\n");
            print_list(A); 
        }
        Cfact = Mfact = 0;
        MergeSort(&A, &Cfact, &Mfact);
        Trand[j] = Cfact + Mfact;
        clear(A); A = NULL;

        fillIncStack(&A, size);
        if (Report) { 
            printf("Исходный убывающий список:\n");
            print_list(A); 
        }
        Cfact = Mfact = 0;
        MergeSort(&A, &Cfact, &Mfact);
        Tinc[j] = Cfact + Mfact;
        clear(A); A = NULL;

        fillDecStack(&A, size);
        if (Report) { 
            printf("Исходный возрастающий список:\n");
            print_list(A); 
        }
        Cfact = Mfact = 0;
        MergeSort(&A, &Cfact, &Mfact);
        Tdec[j] = Cfact + Mfact;
        clear(A); A = NULL;

        Ttheor[j] = (int)(2 * size * log2(size));
    }

    for (int j = 0; j < count; j++) {
        printf("| %5d | %13d | %11d | %10d | %11d |\n", sizes[j], Ttheor[j], Tinc[j], Tdec[j], Trand[j]);
        printf("|_______|_______________|_____________|____________|_____________|\n");

    }

    return 0;
}
