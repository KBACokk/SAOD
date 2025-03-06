#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void UpperMas(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i + 1;
    }
}

void DownMas(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = n - i;
    }
}

void RandMas(int A[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100;
    }
}

int CheckSum(int A[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += A[i];
    }
    printf("Control Sum => %d\n", sum);
    return sum;
}

int SerSum(int A[], int n) {
    int ser = 1;
    for (int i = 1; i < n; i++) {
        if (A[i] < A[i - 1]) ser++;
    }
    printf("Control Ser => %d\n", ser);
    return ser;
}

void PrintMas(int A[], int n) {
    printf("Massive {");
    for (int i = 0; i < n; i++) {
        printf(" %d ", A[i]);
    }
    printf("} \n");
}

int knuthStep(int n) {
    int h = 1;
    while ((h * 2) + 1 < n) {
        h = 2 * h + 1;
    }
    return h;
}

int kbaStep(int n) {
    int h = 1;
    while (h * 3 < n) {
        h = 3 * h;
    }
    return h;
}

int ShellSort(int arr[], int n) {
    int T = 0, C = 0, M = 0;
    int h = knuthStep(n);
    while (h >= 1) {
        for (int i = h; i < n; i++) {
            M++;
            int temp = arr[i];
            int j;
            for (j = i; j >= h && arr[j - h] > temp; j -= h) {
                M++;
                arr[j] = arr[j - h];
                C++;
            }
            M++;
            arr[j] = temp;
        }
        h = (h - 1) / 2;
    }
    return T = M + C;
}

int InsertingSort(int arr[], int n) {
    int T = 0, C = 0, M = 0, temp = 0;
    for (int i = 1; i < n; i++) {
        M++; temp = arr[i];
        int j = i - 1;
        while (j >= 0 && temp < arr[j]) {
            M++; arr[j + 1] = arr[j];
            C++;
            j--;
        }
        if (j >= 0) {
            C++;
        }
        M++; arr[j + 1] = temp;
    }
    return T = M + C;
}

int main() {
    int count = 10; 
    int Report = 0;

    int N[count];
    int Tu[count]; 
    int Tr[count];
    int Tt[count];
    int k = 0;

    int H0[count][10];
    int Td0[count]; 
    int Td[count]; 

    for (int i = 0; i < count; i++) {
        N[i] = 100 * (i + 1);
    }

    for (int j = 0; j < count; j++) {
        int n = N[j];
        printf("\n     <<<<<+++++++++++++++   For massive %d elements    ++++++++++++++++++>>>>>> \n\n", n);
        int A[n];
        RandMas(A, n); 
        if (Report == 1) { PrintMas(A, n); }
        CheckSum(A, n);  SerSum(A, n);
        Td0[j] = ShellSort(A, n);
        printf("--------------------Sroting-------------------\n\n");
        if (Report == 1) { PrintMas(A, n); }
        CheckSum(A, n);  SerSum(A, n);
        int h = knuthStep(n);
        int stepIndex = 0;
        while (h >= 1) {
            H0[j][stepIndex++] = h;
            h = (h - 1) / 2;
        }
        H0[j][stepIndex] = 0;
    }

    for (int j = 0; j < count; j++) {
        int n = N[j];
        printf("\n     <<<<<+++++++++++++++   For massive %d elements    ++++++++++++++++++>>>>>> \n\n", n);
        int A[n];
        RandMas(A, n); 
        if (Report == 1) { PrintMas(A, n); }
        CheckSum(A, n);  SerSum(A, n);
        Td[j] = InsertingSort(A, n);
        printf("--------------------Sroting-------------------\n\n");
        if (Report == 1) { PrintMas(A, n); }
        CheckSum(A, n);  SerSum(A, n);
    }

    printf("\n\n");
    printf(" _________________________________________________________________________________________________________\n");
    printf("|   N    |ShellSort  D.Knut|                      Steps (h)  D.Knut                     |Inserting Sorting|\n");
    printf("|________|_________________|____________________________________________________________|_________________|\n");
    for (int i = 0; i < count; i++) {
        printf("| %-6d | %-15d |", N[i], Td0[i]);
        int m = 0; 
        for (int j = 0; H0[i][j] != 0; j++) {
            printf(" %-4d ", H0[i][j]);
            m++;
        }
        int ll = 0;
        if (m < 10) {
            for (; m < 10; m++) {
                printf(" %-4d ", ll);
            }
        }
        printf("| %-15d |\n", Td[i]);
    printf("|________|_________________|____________________________________________________________|_________________|\n");
    }

    return 0;
}
