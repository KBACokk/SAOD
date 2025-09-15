#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(a,b) (a > b ? a : b)
#define N 100

typedef struct Vertex {
    int Data;
    struct Vertex *Left;
    struct Vertex *Right;
} Vertex;

void Obhod_top_to_down(Vertex *p) {
    if (p != NULL) {
        printf(" %d ", p->Data);
        Obhod_top_to_down(p->Left);
        Obhod_top_to_down(p->Right);
    }
}

void Obhod_right_to_left(Vertex *p) {
    if (p != NULL) {
        Obhod_right_to_left(p->Left);
        printf(" %d ", p->Data);
        Obhod_right_to_left(p->Right);
    }
}

void Obhod_down_to_top(Vertex *p) {
    if (p != NULL) {
        Obhod_down_to_top(p->Left);
        Obhod_down_to_top(p->Right);
        printf(" %d ", p->Data);
    }
}

int ControlSum(Vertex *p) {
    if (p == NULL) { return 0; }
    else {
        return p->Data + ControlSum(p->Left) + ControlSum(p->Right);
    }
}

int Height(Vertex *p) {
    if (p == NULL) { return 0; }
    else {
        int Lheight = Height(p->Left);
        int Rheight = Height(p->Right);
        return 1 + MAX(Lheight, Rheight);
    }
}

int Sumway(Vertex* p, int gear) {
    if (p == NULL) { return 0; }
    else {
        return gear + Sumway(p->Left, gear + 1) +
                     Sumway(p->Right, gear + 1);
    }
}

int countV(Vertex *p) {
    if (p == NULL) {
        return 0;
    }
    else {
        return 1 + countV(p->Left) + countV(p->Right);
    }
}

void PrintTree(Vertex *root, int space, int isRight) {
    if (root == NULL)
        return;
    
    space += 5;
    
    PrintTree(root->Right, space, 1);
    
    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    
    if (isRight == 1)
        printf("/ ");
    else if (isRight == -1)
        printf("\\ ");
    
    printf("%d", root->Data);
    
    PrintTree(root->Left, space, -1);
}

Vertex *create_vertex(int data) {
    Vertex *newVertex = (Vertex *)malloc(sizeof(Vertex));
    newVertex->Data = data;
    newVertex->Left = NULL;
    newVertex->Right = NULL;
    return newVertex;
}

Vertex *NumericTree(int N_vertex, int n) {
    if (N_vertex > n)
        return NULL;
    Vertex *root = create_vertex(N_vertex);
    if (2 * N_vertex <= n) {
        root->Left = NumericTree(2 * N_vertex, n);
    }

    if (2 * N_vertex + 1 <= n) {
        root->Right = NumericTree(2 * N_vertex + 1, n);
    }

    return root;
}

void FillInc(int n, int A[]) {
    for (int i = 0; i < n; i++) {
        A[i] = i + 1;
    }
}

Vertex *BuildISDP(int L, int R, int A[]) {
    if (L > R) {
        return NULL;
    }
    else {
        int m = (L + R) / 2;
        Vertex *p = (Vertex *)malloc(sizeof(Vertex));
        p->Data = A[m];
        p->Left = BuildISDP(L, m - 1, A);
        p->Right = BuildISDP(m + 1, R, A);
        return p;
    }
}

int main() {
    system("chcp 65001 > nul");
    int A[N];
    FillInc(N, A);
    
    printf("=== ИСДП (сбалансированное дерево) ===\n");
    Vertex *root = BuildISDP(0, 99, A);
    
    printf("Обход дерева справа влево:\n");
    Obhod_right_to_left(root);
    
    printf("\n\nВизуализация дерева:\n");
    PrintTree(root, 0, 0);
    
    printf("\n\nРазмер дерева: %d\n", countV(root));
    printf("Контрольная сумма: %d\n", ControlSum(root));
    printf("Высота дерева: %d\n", Height(root));
    printf("Средняя высота дерева: %.2f\n", (float)Sumway(root, 1) / countV(root));
    
    printf("\n\n=== Заполнение дерева по порядку ===\n");
    root = NumericTree(1, 100);
    
    printf("Обход дерева справа влево:\n");
    Obhod_right_to_left(root);
    
    printf("\n\nВизуализация дерева:\n");
    PrintTree(root, 0, 0);
    
    printf("\n\nРазмер дерева: %d\n", countV(root));
    printf("Контрольная сумма: %d\n", ControlSum(root));
    printf("Высота дерева: %d\n", Height(root));
    printf("Средняя высота дерева: %.2f\n", (float)Sumway(root, 1) / countV(root));
    
    return 0;
}
