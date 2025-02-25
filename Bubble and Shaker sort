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

int ShakerSort (int arr[], int n) {
    int T = 0, M = 0, C = 0, L = 0, R = n-1, k = n-1;

    while (L < R) 
    {
    for (int i = R; i > L; i--) { 
        C++; if (arr[i] < arr[i-1]) {
            M++; int temp = arr[i];
            M++; arr[i] = arr[i-1];
            M++; arr[i-1] = temp;
            k = i;
        }
    }

        L = k;
        for (int j = L; j < R; j++) { 
            C++; if (arr[j] > arr[j+1]) {
                M++; int temp = arr[j];
                M++; arr[j] = arr[j+1];
                M++; arr[j+1] = temp;
                k = j;
            }
        }
        R = k;
    }
    return T = C + M ;
}
 
int main () {

    int count = 5; // сколько строк
    int Report = 0; // нужно ли выводить сами массивы

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
            Tu[k] = BubbleSort (A, j);
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
            Td[k] = BubbleSort (A, j);
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
            Tr[k] = BubbleSort (A, j);
            printf ("--------------------Sroting-------------------\n\n");
                    if (Report == 1) { PrintMas (A, j); }
            CheckSum (A, j);  SerSum (A, j);
            Tt[k] = 3*((j * j - j)/2) + (j * j - j)/2;
            N[k] = j;
            k++;
        }


        int Tr0[count]; 
           k = 0;
        for (int j = 100; j < count * 100 + 1; j = j + 100) {
            printf ("\n     <<<<<+++++++++++++++   For massive %d elements    ++++++++++++++++++>>>>>> \n\n", j);
            int A[j];
            RandMas (A,j); 
                if (Report == 1) { PrintMas (A, j); }
            CheckSum (A, j);  SerSum (A, j);
            Tr0[k] = ShakerSort (A, j);
            printf ("--------------------Sroting-------------------\n\n");
                    if (Report == 1) { PrintMas (A, j); }
            CheckSum (A, j);  SerSum (A, j);
            k++;
        }

        int Tu0[count]; 
        k = 0;
     for (int j = 100; j < count * 100 + 1; j = j + 100) {
         printf ("\n     <<<<<+++++++++++++++   For massive %d elements    ++++++++++++++++++>>>>>> \n\n", j);
         int A[j];
         UpperMas (A,j); 
                if (Report == 1) { PrintMas (A, j); }
         CheckSum (A, j);  SerSum (A, j);
         Tu0[k] = ShakerSort (A, j);
         printf ("--------------------Sroting-------------------\n\n");
                if (Report == 1) { PrintMas (A, j); }
         CheckSum (A, j);  SerSum (A, j);
         k++;
     }

     int Td0[count]; 
     k = 0;
  for (int j = 100; j < count * 100 + 1; j = j + 100) {
      printf ("\n     <<<<<+++++++++++++++   For massive %d elements    ++++++++++++++++++>>>>>> \n\n", j);
      int A[j];
      DownMas (A,j); 
            if (Report == 1) { PrintMas (A, j); }
      CheckSum (A, j);  SerSum (A, j);
      Td0[k] = ShakerSort (A, j);
      printf ("--------------------Sroting-------------------\n\n");
            if (Report == 1) { PrintMas (A, j); }
      CheckSum (A, j);  SerSum (A, j);
      k++;
  }

        

  printf("\n\n");
  printf(" _____________________________________________________________________________________________________________________________________\n");
  printf("|     |                         Bubble Sort                           |                            Shaker Sort                        |\n");
  printf("|_____|_______________________________________________________________|_______________________________________________________________|\n");
  printf("|     |                         M (fact) + C (fact)                   |                         M (fact) + C (fact)                   |\n");
  printf("|  N  |_______________________|_____________________|_________________|_______________________|_____________________|_________________|\n");
  printf("|     |           Down               Upper                Rand        |           Down               Upper                Rand        |\n");
  printf("|_____|_______________________|_____________________|_________________|_______________________|_____________________|_________________|\n");
  for (int i = 0; i < k; i++) {
      printf("| %-4d| %-21d | %-19d | %-15d | %-21d | %-19d | %-15d |\n", N[i], Td[i], Tu[i], Tr[i], Td0[i], Tu0[i], Tr0[i]);
      printf("|_____|_______________________|_____________________|_________________|_______________________|_____________________|_________________|\n");
        }
    }
