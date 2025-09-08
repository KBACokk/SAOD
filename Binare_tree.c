#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(a,b) (a > b ? a : b)
#define PMAX(a,b) (a > b ? (printf("%d\n", a)) : (printf("%d\n", b)))

    typedef struct Vertex {
        int Data;
        struct Vertex *Left;
        struct Vertex *Right;
    } Vertex;

    void Obhod_top_to_down (Vertex *p ) {
            if (p != NULL) {
            printf (" %d ", p -> Data);
            Obhod_top_to_down (p -> Left);
            Obhod_top_to_down (p -> Right);
            }
        }
    
    void Obhod_right_to_left (Vertex *p ) {
            if (p != NULL) {
            Obhod_right_to_left (p -> Left);
            printf (" %d ", p -> Data);
            Obhod_right_to_left (p -> Right);
            }
        }

    void Obhod_down_to_top (Vertex *p ) {
            if (p != NULL) {
            Obhod_down_to_top (p -> Left);
            Obhod_down_to_top (p -> Right);
            printf (" %d ", p -> Data);
            }
        }

    int ControlSum(Vertex * p) {
        if (p == NULL) { return 0;}
        else {
            return p -> Data + ControlSum(p -> Left) + ControlSum(p -> Right);
        }
    }

    int Height (Vertex * p) {
        if (p == NULL) { return 0;}
        else {
            int Lheight = Height(p -> Left);
            int Rheight = Height(p -> Right);
            return 1 + MAX(Lheight, Rheight);
        }
    }

    int Sumway (Vertex* p, int gear) {
        if (p == NULL) {return 0;}
        else {
            return gear + Sumway (p -> Left, gear + 1) +
                          Sumway (p -> Right, gear + 1);
        }
    }

    int countV (Vertex *p) {
        if (p == NULL) {
            return 0;
        }
        else {
            return 1 + countV(p -> Left) + countV(p -> Right);
        }
    }


int main () {

    srand(time(NULL)); 

    Vertex *root = (Vertex *)malloc(sizeof(Vertex));
        root->Data = rand() % 20 + 1;
        root->Right = NULL;
        root->Left = NULL; 

        root->Left = (Vertex *)malloc(sizeof(Vertex));
        root->Left->Data = rand() % 20 + 1;;
        root->Left->Right = NULL;
        root->Left->Left = NULL;

        root->Left->Right = (Vertex *)malloc(sizeof(Vertex));
        root->Left->Right->Data = rand() % 20 + 1;;
        root->Left->Right->Right = NULL;
        root->Left->Right->Left = NULL;

        root->Left->Left = (Vertex *)malloc(sizeof(Vertex));
        root->Left->Left->Data = rand() % 20 + 1;;
        root->Left->Left->Right = NULL;
        root->Left->Left->Left = NULL;

        root->Left->Left->Left = (Vertex *)malloc(sizeof(Vertex));
        root->Left->Left->Left->Data = rand() % 20 + 1;;
        root->Left->Left->Left->Right = NULL;
        root->Left->Left->Left->Left = NULL;

        root->Left->Left->Right = (Vertex *)malloc(sizeof(Vertex));
        root->Left->Left->Right->Data = rand() % 20 + 1;;
        root->Left->Left->Right->Right = NULL;
        root->Left->Left->Right->Left = NULL;

        printf("Двоичное дерево (вариант 14):\n");
    printf("          %d\n",       root->Data         );
    printf("         / \n"            );
    printf("        %d   \n", root->Left->Data          );
    printf("       / \\\n"                );
    printf("      %d   %d\n",      root->Left->Left->Data , root->Left->Right->Data     );
    printf("     / \\\n"                   );
    printf("    %d   %d\n\n", root->Left->Left->Left->Data, root->Left->Left->Right->Data       );

        printf ("\nОбход дерева сверху вниз -> ");
    Obhod_top_to_down(root);
        printf ("\nОбход дерева справа влево -> ");
    Obhod_right_to_left(root);
        printf ("\nОбход дерева снизу вверх -> ");
    Obhod_down_to_top(root);
    // printf ("\n\n");
        printf ("\nКонтрольная сумма -> %d", ControlSum(root));
        printf("\nВысота дерева -> %d\n", Height(root));
        printf("средняя высота дерева -> %.2f\n", (float)Sumway(root, 1) / countV(root));
    printf ("\n\n");
    
}
