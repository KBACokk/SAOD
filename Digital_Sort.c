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
    // printf("\n");
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

void DigitalSort(tData** S, int num_passes, int* moves) {
    if (*S == NULL || num_passes <= 0) return;
    
    tQueue Q[256];
    for (int i = 0; i < 256; i++) {
        InitializeQueue(&Q[i]);
    }
    
    for (int pass = 0; pass < num_passes; pass++) {
        for (int i = 0; i < 256; i++) {
            Q[i].head = Q[i].tail = NULL;
        }

        tData* p = *S;
        while (p != NULL) {
            unsigned char digit = (p->data >> (8 * pass)) & 0xFF;
            
            if (Q[digit].head == NULL) {
                Q[digit].head = Q[digit].tail = p;
            } else {
                Q[digit].tail->next = p;
                Q[digit].tail = p;
            }
            
            p = p->next;
            (*moves)++;
        }
        
        tData* newHead = NULL;
        tData* newTail = NULL;
        
        for (int i = 0; i < 256; i++) {
            if (Q[i].head != NULL) {
                if (newHead == NULL) {
                    newHead = Q[i].head;
                    newTail = Q[i].tail;
                } else {
                    newTail->next = Q[i].head;
                    newTail = Q[i].tail;
                }
            }
        }
        
        if (newTail != NULL) {
            newTail->next = NULL;
        }
        
        *S = newHead;
    }
}

int main() {
    tData *A = NULL;
    int Mfact = 0;

    int count = 5; 
    int Report = 0;

    int Trand[count], Tinc[count], Tdec[count], Ttheor[count];
    int sizes[count];
    
    const int L = 16;
    
    for (int j = 0; j < count; j++) {
        int size = 100 * (j + 1);
        sizes[j] = size;

        fillRanStack(&A, size);
        if (Report) { 
            printf("Исходный случайный список:   ");
            print_list(A); printf (" }\n\n");
        }
        Mfact = 0;
        DigitalSort(&A, L, &Mfact);

        if (Report) { 
            printf("Отсортированный случайный список:   ");
            print_list(A);   printf (" }\n\n");
        }

        Trand[j] = Mfact;
        clear(A); A = NULL;

        fillIncStack(&A, size);
        if (Report) { 
            printf("Исходный возрастающий список:   ");
            print_list(A); printf (" }\n\n");
        }
        Mfact = 0;
        DigitalSort(&A, L, &Mfact);

        if (Report) { 
            printf("Отсортированный случайный список:   ");
            print_list(A); printf (" }\n\n");
        }

        Tinc[j] = Mfact;
        clear(A); A = NULL;

        fillDecStack(&A, size);
        if (Report) { 
            printf("Исходный убывающий список:   ");
            print_list(A); printf (" }\n\n");
        }
        Mfact = 0;
        DigitalSort(&A, L, &Mfact);

        if (Report) { 
            printf("Отсортированный случайный список:   ");
            print_list(A); printf (" }\n\n");
        }

        Tdec[j] = Mfact;
        clear(A); A = NULL;

        Ttheor[j] = size * L;
    }

    printf("\n\n\n");
    printf("                   For L = 16 bit ( 2 bytes )                    \n");
    printf(" ________________________________________________________________\n");
    printf("|       |     M + C     |             |            |             |\n");
    printf("|   N   |     Theor     |     Upper   |    Down    |    Rand     |\n");
    printf("|_______|_______________|_____________|____________|_____________|\n");

    for (int j = 0; j < count; j++) {
        printf("| %5d | %13d | %11d | %10d | %11d |\n", 
               sizes[j], Ttheor[j], Tinc[j], Tdec[j], Trand[j]);
        printf("|_______|_______________|_____________|____________|_____________|\n");
    }



    int Trand1[count], Tinc1[count], Tdec1[count], Ttheor1[count];
    int sizes1[count];
    
    const int L1 = 32;
    
    for (int j = 0; j < count; j++) {
        int size = 100 * (j + 1);
        sizes1[j] = size;

        fillRanStack(&A, size);
        if (Report) { 
            printf("Исходный случайный список:   ");
            print_list(A); printf (" }\n\n");
        }
        Mfact = 0;
        DigitalSort(&A, L1, &Mfact);

        if (Report) { 
            printf("Отсортированный случайный список:   ");
            print_list(A);   printf (" }\n\n");
        }

        Trand1[j] = Mfact;
        clear(A); A = NULL;

        fillIncStack(&A, size);
        if (Report) { 
            printf("Исходный возрастающий список:   ");
            print_list(A); printf (" }\n\n");
        }
        Mfact = 0;
        DigitalSort(&A, L1, &Mfact);

        if (Report) { 
            printf("Отсортированный случайный список:   ");
            print_list(A); printf (" }\n\n");
        }

        Tinc1[j] = Mfact;
        clear(A); A = NULL;

        fillDecStack(&A, size);
        if (Report) { 
            printf("Исходный убывающий список:   ");
            print_list(A); printf (" }\n\n");
        }
        Mfact = 0;
        DigitalSort(&A, L1, &Mfact);

        if (Report) { 
            printf("Отсортированный случайный список:   ");
            print_list(A); printf (" }\n\n");
        }

        Tdec1[j] = Mfact;
        clear(A); A = NULL;

        Ttheor1[j] = size * L1;
    }

    printf("\n\n\n");
    printf("                   For L = 32 bit ( 4 bytes )                    \n");
    printf(" ________________________________________________________________\n");
    printf("|       |     M + C     |             |            |             |\n");
    printf("|   N   |     Theor     |     Upper   |    Down    |    Rand     |\n");
    printf("|_______|_______________|_____________|____________|_____________|\n");

    for (int j = 0; j < count; j++) {
        printf("| %5d | %13d | %11d | %10d | %11d |\n", 
               sizes1[j], Ttheor1[j], Tinc1[j], Tdec1[j], Trand1[j]);
        printf("|_______|_______________|_____________|____________|_____________|\n");
    }
}
