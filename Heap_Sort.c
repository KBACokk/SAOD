#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int C = 0;
int M = 0;

int C_build = 0;
int M_build = 0;

void UpperMas(int A[], int n) {
    for (int i = 0; i < n; i++){
    A[i] = i+1;}
}
void DownMas(int A[], int n) {
    for (int i = 0; i < n; i++){
    A[i] = n - i;}
}
void RandMas(int A[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++){
    A[i] = rand() % 100;}
}
int CheckSum(int A[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++){
    sum += A[i];}
    printf ("Control Sum => %d\n", sum);
}
int SerSum(int A[], int n){
    int ser = 1;
    for (int i = 1; i < n; i++){
            if (A[i] < A[i-1]) ser++;
    }
    printf ("Control Ser => %d\n", ser);;
}
void PrintMas(int A[], int n){
    printf (" Massive  {");
    for (int i = 0; i < n; i++){
        printf(" %d ", A[i]);}
    printf("} \n");
}

double calculate_M(int n) { return n * log2(n) + 6.5 * n - 4; }

double calculate_C(int n) { return 2 * n * log2(n) + n + 2; }

double calculate_M_build(int n) { return log2(n) + 2; }

double calculate_C_build(int n) { return 2 * log2(n) + 1; }

void Heapmake(int A[], int L, int R) {
    int x = A[L];
    M++;
    M_build++;
    int i = L;
    while (1)
    {
        int j = 2 * i + 1;
        if (j > R)
            break;
+
        C++;
        C_build++;
        if (j < R && A[j + 1] > A[j])
        {
            j++;
        }

        C++;
        C_build++;
        if (x >= A[j])
            break;

        A[i] = A[j];
        M++;
        M_build++;
        i = j;
    }
    
    M++;
    M_build++;
    A[i] = x;
}

void HeapSort(int A[], int n)
{
    int temp;
    for (int L = n / 2 - 1; L >= 0; L--)
    {
        Heapmake(A, L, n - 1);
    }

    for (int R = n - 1; R > 0; R--)
    {
        temp = A[0];
        M++;
        A[0] = A[R];
        M++;
        A[R] = temp;
        M++;

        Heapmake(A, 0, R - 1);
    }
}

int main()
{
    srand(time(NULL));
    printf("  \x1b[1;33mТрудоемкость ппостроения пирамиды\x1b[0m\n");
    printf(" _______________________________________________________________________________________\n");
    printf("|         |       теоретические         |                  Фактические                  |\n");
    printf("|    N    |                             |_______________________________________________|\n");
    printf("|         |                             |   убывающий   |   случайный   |  возрастающий |\n");
    printf("|_________|_____________________________|_______________|_______________|_______________|\n");
    
    for (int i = 1; i < 6; i++)
    {
        int n = 100 * i;
        int A[n];
        double M_teor_build = calculate_M_build(n);
        double C_teor_build = calculate_C_build(n);
        int teor_T_build = M_teor_build + C_teor_build;

        DownMas(A, n);
        Heapmake(A, 0, n-1);
        int T_buildDec = C_build + M_build;
        C_build=0;
        M_build=0;

        RandMas(A, n);
        Heapmake(A, 0, n-1);
        int T_buildRan = C_build + M_build;
        C_build=0;
        M_build=0;

        UpperMas(A, n);
        Heapmake(A, 0, n-1);
        int T_buildInc = C_build + M_build;
        C_build=0;
        M_build=0;

        printf("| %6d  | %27d | %13d | %13d | %13d |\n", 
               n, teor_T_build, T_buildDec, T_buildRan, T_buildInc);
    }
    printf("|_______________________________________________________________________________________|\n");
    printf("  \x1b[1;33mТрудоемкость пирамидальной сортировки\x1b[0m\n");
    printf(" _________________________________________________________\n");
    printf("|         |                  Фактические                  |\n");
    printf("|    N    |_______________________________________________|\n");
    printf("|         |   убывающий   |   случайный   |  возрастающий |\n");
    printf("|_________|_______________|_______________|_______________|\n");

    for (int i = 1; i < 6; i++)
    {
        int n = 100 * i;
        int A[n];
        int M_teor = calculate_M(n);
        int C_teor = calculate_C(n);
        int teor_T = M_teor + C_teor;

        DownMas(A, n);
        HeapSort(A, n);
        int decT = C + M;
        C = 0;
        M = 0;

        RandMas(A, n);
        HeapSort(A, n);
        int randT = C + M;
        C = 0;
        M = 0;

        UpperMas(A, n);
        HeapSort(A, n);
        int incT = C + M;
        C = 0;
        M = 0;

        printf("| %6d  | %13d | %13d | %13d |\n", n, decT, randT, incT);
    }
    printf("|_________________________________________________________|\n");

    return 0;
}
