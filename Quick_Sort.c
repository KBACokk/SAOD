#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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



int QuickSort(int arr[], int L, int R, int* M, int* C) {
    int i = L, j = R;
    int a = arr[L]; 

    while (i <= j) {
        (*C)++;
        while (arr[i] < a) { i++; (*C)++; }
        
        (*C)++;
        while (arr[j] > a) { j--; (*C)++; }

        if (i <= j) {
            if (i < j) {
                int temp = arr[i];
                arr[j] = arr[i];
                arr[i] = temp;
                (*M) += 3;
            }
            i++;
            j--;
        }
    } 

    if (L < j) { QuickSort(arr, L, j, M, C); }
    if (i < R) { QuickSort(arr, i, R, M, C); }
    
    return *M + *C;
}

int main() {
    int count = 5;
    int Report = 0;

    int Tu[count], Td[count], Tr[count], Tt[count], N[count];
    int k = 0;


    for (int j = 100; j <= count * 100; j += 100) {
        printf("\n     <<<<<+++++++++++++++   For massive %d elements    ++++++++++++++++++>>>>>> \n\n", j);
        int A[j];
        UpperMas(A, j);
        if (Report) PrintMas(A, j);
        CheckSum(A, j);
        SerSum(A, j);
        
        int M = 0, C = 0;
        Tu[k] = QuickSort(A, 0, j-1, &M, &C);
        
        printf("--------------------Sorting-------------------\n\n");
        if (Report) PrintMas(A, j);
        CheckSum(A, j);
        SerSum(A, j);
        
        N[k] = j;
        k++;
    }

    k = 0;

    for (int j = 100; j <= count * 100; j += 100) {
        printf("\n     <<<<<+++++++++++++++   For massive %d elements    ++++++++++++++++++>>>>>> \n\n", j);
        int A[j];
        DownMas(A, j);
        if (Report) PrintMas(A, j);
        CheckSum(A, j);
        SerSum(A, j);
        
        int M = 0, C = 0;
        Td[k] = QuickSort(A, 0, j-1, &M, &C);
        
        printf("--------------------Sorting-------------------\n\n");
        if (Report) PrintMas(A, j);
        CheckSum(A, j);
        SerSum(A, j);
        k++;
    }

    k = 0;
    for (int j = 100; j <= count * 100; j += 100) {
        printf("\n     <<<<<+++++++++++++++   For massive %d elements    ++++++++++++++++++>>>>>> \n\n", j);
        int A[j];
        RandMas(A, j);
        if (Report) PrintMas(A, j);
        CheckSum(A, j);
        SerSum(A, j);
        
        int M = 0, C = 0;
        Tr[k] = QuickSort(A, 0, j-1, &M, &C);
        
        // Tt[k] = (int)(2 * j * log2(j));
        // Tt[k] = (3*(j-1) + (j*j + 5*j+4)/2);
        
        printf("--------------------Sorting-------------------\n\n");
        if (Report) PrintMas(A, j);
        CheckSum(A, j);
        SerSum(A, j);
        k++;
    }

    printf("\n\n");
    printf("___________________________________________________\n");
    printf("|     |                 M+C (fact)                 |\n");
    printf("|  N  |____________________________________________|\n");
    printf("|     |    Down           Upper           Rand     |\n");
    printf("|_____|____________________________________________|\n");
    for (int i = 0; i < count; i++) {
        printf("| %-4d| %-13d   %-13d   %-10d | \n", 
               N[i],  Td[i], Tu[i], Tr[i]);
        printf("|_____|____________________________________________|\n");
    }

    return 0;
}
