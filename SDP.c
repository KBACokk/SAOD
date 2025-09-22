#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define cnt 100

typedef struct Vertex {
    int Data;
    struct Vertex *Left;
    struct Vertex *Right;
} Vertex;

Vertex *create_vertex(int Data) {
    Vertex *newVertex = (Vertex *)malloc(sizeof(Vertex));
    newVertex->Data = Data;
    newVertex->Left = NULL;
    newVertex->Right = NULL;
    return newVertex;
}

void Left_to_Right(Vertex *p) {
    if (p != NULL)
    {
        Left_to_Right(p->Left);
        printf("%d ", p->Data);
        Left_to_Right(p->Right);
    }
}

int Search(Vertex *p, int X) {
    while (p != NULL) {
        if (X < p->Data) {
            p = p->Left;
        }
        else if (X > p->Data) {
            p = p->Right;
        }
        else
            break;
    }
    return (p != NULL);
}

int Size(Vertex *p) {
    if (p == NULL) {
        return 0;
    }
    else {
        return 1 + Size(p->Left) + Size(p->Right);
    }
}

int CheckSum(Vertex *p) {
    if (p == NULL) {
        return 0;
    }
    else {
        return p->Data + CheckSum(p->Left) + CheckSum(p->Right);
    }
}

int Height(Vertex *p) {
    if (p == NULL) {
        return 0;
    }
    else {
        int LeftHeight = Height(p->Left);
        int RightHeight = Height(p->Right);
        return 1 + (LeftHeight > RightHeight ? LeftHeight : RightHeight);
    }
}

int SumLen(Vertex *p, int level) {
    if (p == NULL) {
        return 0;
    }
    else {
        return level +
               SumLen(p->Left, level + 1) +
               SumLen(p->Right, level + 1);
    }
}

float AverageHeight(Vertex *root) {
    if (root == NULL) {
        return 0.0f;
    }
    int total_path_length = SumLen(root, 1);
    int tree_size = Size(root);
    return (float)total_path_length / tree_size;
}

void generator(int arr[], int n) {
    srand(time(NULL));
    int count = 0;
    while (count < n) {
        int num = rand() % 101;
        int isUnique = 1;
        for (int i = 0; i < count; i++) {
            if (arr[i] == num) {
                isUnique = 0;
                break;
            }
        }
        if (isUnique) {
            arr[count] = num;
            count++;
            printf("%d ", num);
        }
    }
}

void PrintMas(int n, int A[]) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int BubbleSort(int arr[], int n) {
    int T = 0, C = 0, M = 0;
    for (int i = 0; i < n - 1; i++) { 
        for (int j = n - 1; j > i; j--) {
            int temp; 
            C++; if (arr[j] < arr[j-1]) {
                M++; temp = arr[j];
                M++; arr[j] = arr[j-1];
                M++; arr[j-1] = temp; 
            }
        }
    }
    return T = C + M;
}

Vertex *ISDP(int L, int R, int A[])
{
    if (L > R) {
        return NULL;
    }
    else {
        int m = (L + R) / 2;
        Vertex *p = (Vertex *)malloc(sizeof(Vertex));
        p->Data = A[m];
        p->Left = ISDP(L, m - 1, A);
        p->Right = ISDP(m + 1, R, A);
        return p;
    }
}

void DoubleSDP(Vertex **p, int Data) {
    while (*p != NULL) {
        if (Data < (*p)->Data) {
            p = &((*p)->Left);
        }
        else if (Data > (*p)->Data) {
            p = &((*p)->Right);
        }
        else {
            return;
        }
    }
    if (*p == NULL) {
        *p = (Vertex *)malloc(sizeof(Vertex));
        (*p)->Data = Data;
        (*p)->Left = NULL;
        (*p)->Right = NULL;
    }
}

Vertex *RecursiveSDP(Vertex *p, int Data) {
    if (p == NULL) {
        p = (Vertex *)malloc(sizeof(Vertex));
        p->Data = Data;
        p->Left = NULL;
        p->Right = NULL;
    }
    else if (Data < p->Data) {
        p->Left = RecursiveSDP(p->Left, Data);
    }
    else if (Data > p->Data) {
        p->Right = RecursiveSDP(p->Right, Data);
    }
    return p;
}

void Result(const char *name, Vertex *p) {
    printf("║ %-20s ║ %-10d ║ %-15d ║ %-10d ║ %-13.2f ║\n",
           name,
           Size(p),
           CheckSum(p),
           Height(p),
           AverageHeight(p));
}


int main()
{
    int rand[cnt];
    int sort[cnt];

    printf("\n═══════════════════════════════════════════════════════════════════════════════\n");
    printf("                        ГЕНЕРАЦИЯ СЛУЧАЙНОГО МАССИВА\n");
    printf("═══════════════════════════════════════════════════════════════════════════════\n");
    
    generator(rand, cnt);
    
    for (int i = 0; i < cnt; i++) {
        sort[i] = rand[i];
    }
    
    BubbleSort(sort, cnt);
    
    printf("\n\n═══════════════════════════════════════════════════════════════════════════════\n");
    printf("                          ОТСОРТИРОВАННЫЙ МАССИВ\n");
    printf("═══════════════════════════════════════════════════════════════════════════════\n");
    PrintMas(cnt, sort);

    Vertex *root = ISDP(0, 99, sort);
    
    printf("\n═══════════════════════════════════════════════════════════════════════════════\n");
    printf("                ОБХОД ИДЕАЛЬНО СБАЛАНСИРОВАННОГО ДЕРЕВА (ISDP)\n");
    printf("═══════════════════════════════════════════════════════════════════════════════\n");
    Left_to_Right(root);

    Vertex *SDP1Root = NULL;
    for (int i = 0; i < cnt; i++) {
        DoubleSDP(&SDP1Root, rand[i]);
    }
    
    printf("\n\n═══════════════════════════════════════════════════════════════════════════════\n");
    printf("           ОБХОД ДЕРЕВА ПОИСКА (ДВОЙНЫЕ УКАЗАТЕЛИ)\n");
    printf("═══════════════════════════════════════════════════════════════════════════════\n");
    Left_to_Right(SDP1Root);

    Vertex *SDP2Root = NULL;
    for (int i = 0; i < cnt; i++)
    {
        SDP2Root = RecursiveSDP(SDP2Root, rand[i]);
    }
    
    printf("\n\n═══════════════════════════════════════════════════════════════════════════════\n");
    printf("              ОБХОД ДЕРЕВА ПОИСКА (РЕКУРСИВНЫЙ МЕТОД)\n");
    printf("═══════════════════════════════════════════════════════════════════════════════\n");
    Left_to_Right(SDP2Root);

    printf("\n\n═══════════════════════════════════════════════════════════════════════════════\n");
    printf("                          СТАТИСТИКА ДЕРЕВЬЕВ\n");
    printf("═══════════════════════════════════════════════════════════════════════════════\n");
    
    printf("\n╔══════════════════════╦════════════╦═════════════════╦════════════╦═══════════════╗\n");
    printf("║      Тип дерева      ║  Размер    ║  Контр. сумма   ║   Высота   ║   Ср. высота  ║\n");
    printf("╠══════════════════════╬════════════╬═════════════════╬════════════╬═══════════════╣\n");
    
    Result("ISDP", root);
    Result("SDP (двойные указ)  ",   SDP1Root);
    Result("SDP (рекурсивный)   ", SDP2Root);
    
    printf("╚══════════════════════╩════════════╩═════════════════╩════════════╩═══════════════╝\n");

    return 0;
}
