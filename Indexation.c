#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Student {
    char name[64];
    char surname[64];
    int phone;
    int age;
};

const char *names[] = {
    "Влад", "Роман", "Валерия", "Виктория", "Никита", "Сергей", "Богдан", 
    "Андрей", "Артём", "Павел", "Вадим", "Александр", "Арина", "Дмитрий", 
    "Даниил", "Самир", "Юрий"
};    

const char *surnames[] = {
    "Погорелов(а)", "Петров(а)", "Лысенко", "Демин(а)", "Шаимов(а)", 
    "Кутенков(а)", "Попов(а)", "Добромилов(а)", "Волевач", "Бубенин(а)", 
    "Воробьёв(а)", "Рудомётов(а)", "Бобокулов(а)", "Кузеванов(а)"
};

int lessNameSurname(struct Student a, struct Student b) {
    int cmp = strcmp(a.name, b.name);
    return cmp == 0 ? strcmp(a.surname, b.surname) < 0 : cmp < 0;
}

int lessSurnameName(struct Student a, struct Student b) {
    int cmp = strcmp(a.surname, b.surname);
    return cmp == 0 ? strcmp(a.name, b.name) < 0 : cmp < 0;
}

int lessPhoneAge(struct Student a, struct Student b) {
    return a.phone == b.phone ? a.age < b.age : a.phone < b.phone;
}

int lessAgePhone(struct Student a, struct Student b) {
    return a.age == b.age ? a.phone < b.phone : a.age < b.age;
}

struct Student addStudent() {
    struct Student newStudent;
    strcpy(newStudent.name, names[rand() % (sizeof(names)/sizeof(names[0]))]);
    strcpy(newStudent.surname, surnames[rand() % (sizeof(surnames)/sizeof(surnames[0]))]);
    newStudent.phone = rand() % 1000000 + 300000;
    newStudent.age = rand() % 11 + 18;
    return newStudent;
}

void Info(struct Student s) {
    printf("  \x1b[35;1mStudent    >>>\x1b[0m  \x1b[32m%s    %s\x1b[0m    <number> => \x1b[32m%d\x1b[0m    <age> => \x1b[36m%d\x1b[0m\n", 
           s.name, s.surname, s.phone, s.age);
}

void printIndexArray(int arr[], int n, const char* title) {
    printf("%s: [", title);
    for (int i = 0; i < n; i++) {
        printf("\x1b[31m%d\x1b[0m", arr[i]);
        if (i < n-1) printf(", ");
    }
    printf("]\n");
}

void InsertingSortIndex(int n, struct Student A[], int B[], int (*less)(struct Student, struct Student)) {
    for (int i = 0; i < n; i++) {
        B[i] = i;
    }
    
    printf("\n\x1b[33mИндексный массив ДО сортировки:\x1b[0m\n");
    printIndexArray(B, n, "Индексы");
    
    for (int i = 1; i < n; i++) {
        int current_index = B[i];  
        struct Student current = A[current_index];  
        int j = i - 1;
        
        while (j >= 0 && less(current, A[B[j]])) {
            B[j + 1] = B[j]; 
            j--;
        }
        
        B[j + 1] = current_index;
    }
    printf("\x1b[33mИндексный массив ПОСЛЕ сортировки:\x1b[0m\n");
    printIndexArray(B, n, "Индексы");
    printf("\n");
}

int main() {
    srand(time(NULL));
    int n = 5; // Кол-во студов
    struct Student students[n];
    int index_name[n]; 
    int index_age[n];

    printf("\n\x1b[1;33m---------------------------------------------------------------------------\x1b[0m\n");
    printf("  \x1b[1;33m            <<<<<  *** Изначальный массив структур ***  >>>>>              \x1b[0m\n");
    printf("\x1b[1;33m-------------------------------------------------------------------------\x1b[0m\n\n");
    for (int i = 0; i < n; i++) {
        students[i] = addStudent();
        Info(students[i]);
    }

    printf("\n\x1b[1;33m---------------------------------------------------------------------------\x1b[0m\n");
    printf("  \x1b[1;33m            <<<<<  *** Сортировка по имени + фамилии ***  >>>>>           \x1b[0m\n");
    printf("\x1b[1;33m-------------------------------------------------------------------------\x1b[0m\n");
    InsertingSortIndex(n, students, index_name, lessNameSurname);
    
    printf("\x1b[1;33mРезультат сортировки:\x1b[0m\n");
    for (int i = 0; i < n; i++) {
        Info(students[index_name[i]]);
    }

    printf("\n\x1b[1;33m---------------------------------------------------------------------------\x1b[0m\n");
    printf("  \x1b[1;33m            <<<<<  *** Сортировка по возрасту + номеру ***  >>>>>         \x1b[0m\n");
    printf("\x1b[1;33m-------------------------------------------------------------------------\x1b[0m\n");
    InsertingSortIndex(n, students, index_age, lessAgePhone);
    
    printf("\x1b[1;33mРезультат сортировки:\x1b[0m\n");
    for (int i = 0; i < n; i++) {
        Info(students[index_age[i]]);
    }

    return 0;
}
