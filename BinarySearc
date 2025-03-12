#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void UpperMas(int A[], int n) {
    for (int i = 0; i < n; i++){
    A[i] = i+1;}
}
void UpperRandMas(int A[], int n) {
    A[0] = 1 + rand() % 2; 
    for (int i = 1; i < n; i++) {
        A[i] = A[i - 1] + 1 + rand() % 2;  
    }
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


 
int BinarySearch0(int arr[], int n, int f, int *T0) {
    int C = 0;
    int L = 0, R = n - 1;
    int m = 0;
    while ( L <= R) {
        m = (L+R)/2;
        C++; if (arr[m] == f) {
            *T0 = C;
            return m + 1;
        }
        else if (arr[m] < f && C++) {
            L = m+1;
        }
        else {
            R = m-1;
            C++;
        }
    } 
    *T0 = C;
    return -1;
}



int BinarySearch1(int arr[], int n, int f, int *T1) {
    int C = 0;
    int L = 0, R = n - 1;
    int m = 0;
    while ( L <= R) {
        m = (L+R)/2;
        C++; 
        if (arr[m] < f) {
            L = m + 1;
        }
        else {
            R = m - 1;
        }
    } 
    if (arr[L] == f) {
        *T1 = C;
        return L + 1;
    }
    else {
        *T1 = C;
        return -1;
    }
}




int main () {

    int n = 0;

    int count = 10;
    int SHAM = 100;
    int N[count];
    int Report = 0;
    int f;
    printf ("\n   Input element  -> ");
    scanf ("%d", &f);

    int k = 0;
    int T0[count];
        for (int j = SHAM; j < count * SHAM + 1; j = j + SHAM) {
            printf ("\n     <<<<<+++++++++++++++   For massive %d elements    ++++++++++++++++++>>>>>> \n\n", j);
            int A[j];
            UpperMas (A,j);
                    if (Report == 1) { PrintMas (A, j); }
            n = BinarySearch0 (A, j, f, &T0[k]);
            if (n == -1) {
                printf ("\n  Element < %d > not found \n", f);
            }
            else {
            printf ("\n\n  The position of < %d > on %d \n",f,n);
          }
          k++;
        }

        printf ("\n\n  ====================   Second version    ===================  \n\n");


        k = 0;
        int T1[count];
        for (int j = SHAM; j < count * SHAM + 1; j = j + SHAM) {
            printf ("\n     <<<<<+++++++++++++++   For massive %d elements    ++++++++++++++++++>>>>>> \n\n", j);
            int A[j];
            UpperMas (A,j); 
                    if (Report == 1) { PrintMas (A, j); }
            n = BinarySearch1 (A, j, f, &T1[k]);
            if (n == -1) {
                printf ("\n  Element < %d > not found \n", f);
            }
            else {
            printf ("\n\n  The position of < %d > on %d position \n",f,n);
          }
          N[k] = j;
          k++;
        }


        printf("\n\n");
        printf(" __________________________________\n");
        printf("|     |             |              |\n");
        printf("|  N  | C I version | C II version |\n");
        printf("|_____|_____________|______________|\n");
        for (int i = 0; i < k; i++) {
            printf("| %-10d %-13d  %-13d               \n", N[i], T0[i], T1[i]);
        printf("|_____|_____________|______________|\n");
        }
        printf ("\n");

        
    }
