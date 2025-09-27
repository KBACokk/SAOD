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

void Delete(Vertex **Root, int D) {
    Vertex **p = Root;
    while (*p != NULL) {
        if (D < (*p)->Data) {
            p = &((*p)->Left);
        } else if (D > (*p)->Data) {
            p = &((*p)->Right);
        } else {
            break;
        }
    }
    
    if (*p != NULL) {
        Vertex *q = *p;
        if (q->Left == NULL) {
            *p = q->Right;
        } else if (q->Right == NULL) {
            *p = q->Left;
        } else {
            Vertex *r = q->Left;
            Vertex *S = q;
            
            if (r->Right == NULL) {
                r->Right = q->Right;
                *p = r;
            } else {
                while (r->Right != NULL) {
                    S = r;
                    r = r->Right;
                }
                S->Right = r->Left;
                r->Left = q->Left;
                r->Right = q->Right;
                *p = r;
            }
        }
        free(q);
    }
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

        printf("\n\n═══════════════════════════════════════════════════════════════════════════════\n");
    printf("                УДАЛЕНИЕ ВЕРШИН ИЗ СЛУЧАЙНОГО ДЕРЕВА ПОИСКА\n");
    printf("═══════════════════════════════════════════════════════════════════════════════\n");
    
    Vertex *deleteRoot = NULL;
    for (int i = 0; i < cnt; i++) {
        DoubleSDP(&deleteRoot, rand[i]);
    }
    
    printf("Исходное дерево перед удалением:\n");
    Left_to_Right(deleteRoot);
    printf("\nРазмер дерева: %d, Контрольная сумма: %d, Высота: %d\n", 
           Size(deleteRoot), CheckSum(deleteRoot), Height(deleteRoot));
    
    int keysToDelete[10];
    printf("\nВведите 10 ключей для удаления из дерева:\n");
    
    for (int i = 0; i < 10; i++) {
        printf("Ключ %d ->  ", i + 1);
        scanf("%d", &keysToDelete[i]);
    }
    
    printf("\n═══════════════════════════════════════════════════════════════════════════════\n");
    printf("                    ПРОЦЕСС УДАЛЕНИЯ ВЕРШИН\n");
    printf("═══════════════════════════════════════════════════════════════════════════════\n");
    
    for (int i = 0; i < 10; i++) {
        int key = keysToDelete[i];
        
        printf("\n--- Удаление вершины с ключом \x1b[1;31m%d\x1b[0m\n ---\n", key);
        
        if (Search(deleteRoot, key)) {
            Delete(&deleteRoot, key);
            printf("\x1b[1;32mВершина удалена успешно.\x1b[0m\n");
        } else {
            printf("\x1b[1;33mВершина с ключом %d не найдена.\x1b[0m\n\n", key);
        }
        
        printf("Обход дерева после удаления: ");
        Left_to_Right(deleteRoot);
        printf("\nРазмер: %d, Контр. сумма: %d, Высота: %d, Ср. высота: %.2f\n",
               Size(deleteRoot), CheckSum(deleteRoot), Height(deleteRoot), AverageHeight(deleteRoot));
        
        printf("\n");
    }
    
    printf("\n═══════════════════════════════════════════════════════════════════════════════\n");
    printf("                    ФИНАЛЬНАЯ СТАТИСТИКА ПОСЛЕ УДАЛЕНИЙ\n");
    printf("═══════════════════════════════════════════════════════════════════════════════\n");
    
    printf("Итоговый обход дерева: ");
    Left_to_Right(deleteRoot);
    printf("\n\n╔══════════════════════╦════════════╦═════════════════╦════════════╦═══════════════╗\n");
    printf("║      Тип дерева      ║  Размер    ║  Контр. сумма   ║   Высота   ║   Ср. высота  ║\n");
    printf("╠══════════════════════╬════════════╬═════════════════╬════════════╬═══════════════╣\n");
    
    Result("Исходное СДП        ", SDP1Root);
    Result("СДП после удалений  ", deleteRoot);
    
    printf("╚══════════════════════╩════════════╩═════════════════╩════════════╩═══════════════╝\n");

    return 0;
}
