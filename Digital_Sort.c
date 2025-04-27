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

void DigitalSort(tData** S, int L, int* moves) {
    if (*S == NULL) return;
    
    // Создаем массив из 10 очередей (по цифрам 0-9)
    tQueue Q[10];
    for (int i = 0; i < 10; i++) {
        InitializeQueue(&Q[i]);
    }
    
    // Проходим по всем разрядам от младшего к старшему
    for (int j = 0; j < L; j++) {
        // Инициализация очередей
        for (int i = 0; i < 10; i++) {
            Q[i].head = Q[i].tail = NULL;
        }
        
        // Распределение элементов по очередям
        tData* p = *S;
        while (p != NULL) {
            int digit = (p->data / (int)pow(10, j)) % 10;
            
            if (Q[digit].head == NULL) {
                Q[digit].head = Q[digit].tail = p;
            } else {
                Q[digit].tail->next = p;
                Q[digit].tail = p;
            }
            
            p = p->next;
            (*moves)++;
        }
        
        // Соединение очередей обратно в список
        tData* newHead = NULL;
        tData* newTail = NULL;
        
        for (int i = 0; i < 10; i++) {
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

    printf(" ________________________________________________________________\n");
    printf("|       |     M + C     |             |            |             |\n");
    printf("|   N   |     Theor     |     Upper   |    Down    |    Rand     |\n");
    printf("|_______|_______________|_____________|____________|_____________|\n");

    int Trand[count], Tinc[count], Tdec[count], Ttheor[count];
    int sizes[count];
    
    const int L = 2;
    
    for (int j = 0; j < count; j++) {
        int size = 100 * (j + 1);
        sizes[j] = size;

        fillRanStack(&A, size);
        if (Report) { 
            printf("Исходный случайный список:\n");
            print_list(A); 
        }
        Mfact = 0;
        DigitalSort(&A, L, &Mfact);
        Trand[j] = Mfact;
        clear(A); A = NULL;

        fillIncStack(&A, size);
        if (Report) { 
            printf("Исходный возрастающий список:\n");
            print_list(A); 
        }
        Mfact = 0;
        DigitalSort(&A, L, &Mfact);
        Tinc[j] = Mfact;
        clear(A); A = NULL;

        fillDecStack(&A, size);
        if (Report) { 
            printf("Исходный убывающий список:\n");
            print_list(A); 
        }
        Mfact = 0;
        DigitalSort(&A, L, &Mfact);
        Tdec[j] = Mfact;
        clear(A); A = NULL;

        Ttheor[j] = size * L;
    }

    for (int j = 0; j < count; j++) {
        printf("| %5d | %13d | %11d | %10d | %11d |\n", 
               sizes[j], Ttheor[j], Tinc[j], Tdec[j], Trand[j]);
        printf("|_______|_______________|_____________|____________|_____________|\n");
    }

    return 0;
}
