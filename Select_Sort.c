#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int SelectSort(int arr[], int n) {
    int T = 0, C = 0, M = 0, temp = 0;
    for (int i = 0; i < n-1; i++) {
        int k = i; 
        for (int j = i + 1; j < n; j++) {
            C++; if (arr[j] < arr[k]) {
                k = j;
            }
        }
        M++; int temp = arr[i];
        M++; arr[i] = arr[k];
        M++; arr[k] = temp;

    }
    return T = M + C;
        
}
 
int main () {

    int count = 5;
    int Report = 0;

    int Tu[count];
    int Tt[count];
    int N[count];
    int k = 0;
        for (int j = 100; j < count * 100 + 1; j = j + 100) {
            printf ("\n     <<<<<+++++++++++++++   For massive %d elements    ++++++++++++++++++>>>>>> \n\n", j);
            int A[j];
            UpperMas (A,j); 
                    if (Report == 1) { PrintMas (A, j); }
            CheckSum (A, j);  SerSum (A, j);
            Tu[k] = SelectSort (A, j);
            printf ("--------------------Sroting-------------------\n\n");
                    if (Report == 1) { PrintMas (A, j); }
            CheckSum (A, j);  SerSum (A, j);
            k++;
        }

        int Td[count]; 
            k = 0;
        for (int j = 100; j < count * 100 + 1; j = j + 100) {
            printf ("\n     <<<<<+++++++++++++++   For massive %d elements    ++++++++++++++++++>>>>>> \n\n", j);
            int A[j];
            DownMas (A,j); 
                    if (Report == 1) { PrintMas (A, j); }
            CheckSum (A, j);  SerSum (A, j);
            Td[k] = SelectSort (A, j);
            printf ("--------------------Sroting-------------------\n\n");
                    if (Report == 1) { PrintMas (A, j); }
            CheckSum (A, j);  SerSum (A, j);
            k++;
        }

        int Tr[count]; 
           k = 0;
        for (int j = 100; j < count * 100 + 1; j = j + 100) {
            printf ("\n     <<<<<+++++++++++++++   For massive %d elements    ++++++++++++++++++>>>>>> \n\n", j);
            int A[j];
            RandMas (A,j); 
                    if (Report == 1) { PrintMas (A, j); }
            CheckSum (A, j);  SerSum (A, j);
            Tr[k] = SelectSort (A, j);
            printf ("--------------------Sroting-------------------\n\n");
                    if (Report == 1) { PrintMas (A, j); }
            CheckSum (A, j);  SerSum (A, j);
            Tt[k] = 3 * (j - 1) + (j*j - j)/2;
            N[k] = j;
            k++;
        }


        printf("\n\n");
        printf("____________________________________________________________________\n");
        printf("|     |                |                 M+C (fact)                 |\n");
        printf("|  N  |       M+C      |____________________________________________|\n");
        printf("|     |      theor     |    Down           Upper           Rand     |\n");
        printf("|_____|________________|____________________________________________|\n");
        for (int i = 0; i < k; i++) {
            printf("| %-9d %-13d  %-13d %-13d %-13d                              \n", N[i], Tt[i], Td[i], Tu[i], Tr[i]);
        printf("|_____|________________|____________________________________________|\n");
        }
    }
