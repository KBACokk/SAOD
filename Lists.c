#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10

typedef struct tData
{
    struct tData *next;
    int data;
} tData;

void AddToStack(tData** head, int data) {
    tData* p = (tData*)malloc(sizeof(tData));
    p->data = data;
    p->next = *head;
    *head = p;
}

void UpperStack(tData **head, int n) {
    for (int i = 1; i <= n; i++) {
        AddToStack(head, i);
    }
}

void DownStack(tData** head, int n) {
    for (int i = n; i >= 1; i--) {
        AddToStack(head, i);
    }
}

void RandStack(tData** head, int n) {
    srand(time(NULL));
    for (int i = 1; i <= n; i++) {
        int ranNum = rand() % 10;
        AddToStack(head, ranNum);
    }
}

void AddToQueue(tData** head, tData** tail, int data) {
    tData *p = (tData *)malloc(sizeof(tData));
    p->data = data;
    p->next = NULL;

    if (*tail == NULL) {
        *head = *tail = p;
    }
    else {
        (*tail)->next = p;
        *tail = p;
    }
}

void UpperQueue(tData** head, tData** tail, int n) {
    for (int i = 1; i <= n; i++) {
        AddToQueue(head, tail, i);
    }
}

void DownQueue(tData** head, tData** tail, int n) {
    for (int i = n; i >= 1; i--) {
        AddToQueue(head, tail, i);
    }
}

void RandQueue(tData** head, tData** tail, int n) {
    srand(time(NULL));
    for (int i = 1; i <= n; i++) {
        int ranNum = rand() % 10;
        AddToQueue(head, tail, ranNum);
    }
}

void delStackElement(tData** head) {
    if (head != NULL) {
        tData *p = *head;
        *head = p->next;
        free(p);
    }
}

void print_list(tData *head) {
    tData *p = head;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int checksum(tData *head) {
    int sum = 0;
    tData *p = head;
    while (p != NULL) {
        sum += p->data;
        p = p->next;
    }
    return sum;
}

int count_series(tData *head) {
    if (head == NULL) {
        return 0;
    }

    int count = 1;
    tData *p = head;

    while (p->next != NULL) {
        if (p->data > p->next->data)
        {
            count++;
        }
        p = p->next;
    }
    return count;
}

void clear(tData *head) {
    tData *p = head;
    while (p != NULL) {
        tData *temp_p = p;
        p=p->next;
        free(temp_p);
    }
    printf("\n");
}




int main() {

    printf ("     -----  Stack info  -----\n\n");

    tData* stack_head = NULL;
    UpperStack(&stack_head, N);
    printf("Stack (Dw): ");
    print_list(stack_head);
    printf("Control_sum: %d\n", checksum(stack_head));
    printf("Series: %d\n", count_series(stack_head));
    clear(stack_head);

    stack_head = NULL;
    DownStack(&stack_head, N);
    printf("Stack (Up): ");
    print_list(stack_head);
    printf("Control_sum: %d\n", checksum(stack_head));
    printf("Series: %d\n", count_series(stack_head));
    clear(stack_head);

    stack_head = NULL;
    RandStack(&stack_head, N);
    printf("Stack (Rand): ");
    print_list(stack_head);
    printf("Control_sum: %d\n", checksum(stack_head));
    printf("Series: %d\n", count_series(stack_head));
    clear(stack_head);

    printf ("     -----  Queue info  -----\n\n");

    tData* queue_head = NULL, *queue_tail = NULL;
    UpperQueue(&queue_head, &queue_tail, N);
    printf("Queue (Dw): ");
    print_list(queue_head);
    printf("Control_sum: %d\n", checksum(queue_head));
    printf("Series: %d\n", count_series(queue_head));
    clear(queue_head);

    queue_head = NULL; 
    queue_tail = NULL;
    DownQueue(&queue_head, &queue_tail, N);
    printf("Queue (Up): ");
    print_list(queue_head);
    printf("Control_sum: %d\n", checksum(queue_head));
    printf("Series: %d\n", count_series(queue_head));
    clear(queue_head);

    queue_head = NULL; 
    queue_tail = NULL;
    RandQueue(&queue_head, &queue_tail, N);
    printf("Queue (Rand): ");
    print_list(queue_head);
    printf("Control_sum: %d\n", checksum(queue_head));
    printf("Series: %d\n", count_series(queue_head));
    clear(queue_head);

}
