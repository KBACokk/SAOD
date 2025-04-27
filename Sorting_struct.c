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
    "Влад", "Роман", "Валерия", "Виктория", "Никита", "Сергей", "Богдан", "Анрей", "Артём", "Павел", "Вадим", "Александр", "Арина", "Дмитрий", "Даниил", "Самир", "Юрий", 
};    

const char *surnames[] = {
    "Погорелов(а)", "Петров(а)", "Лысенко", "Демин(а)", "Шаимов(а)", "Кутенков(а)", "Попов(а)", "Добромилов(а)", "Волевач", "Бубенин(а)", "Воробьёв(а)", "Рудомётов(а)", "Бобокулов(а)", "Кузеванов(а)"
};

struct Student addStudent() {
    struct Student newStudent;
    strcpy(newStudent.name, names[rand() % (sizeof(names) / sizeof(names[0]))]);
    strcpy(newStudent.surname, surnames[rand() % (sizeof(surnames) / sizeof(surnames[0]))]);
    newStudent.phone = rand() % 1000000 + 300000;
    newStudent.age = rand() % 10 + 18;
    return newStudent;
}

void Info(struct Student s) {
    printf("\n  Student    >>>   %-19s %-15s <number> => %-3d <age> => %-3d",s.name, s.surname, s.phone, s.age);
}


// printf("| %-9d %-13d  %-13d %-13d %-13d                              \n", N[i], Tt[i], Td[i], Tu[i], Tr[i]);

void SelSortAgePhone(int n, struct Student A[], int reverse) {
    for (int i = 0; i < n - 1; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) {
            if (reverse == 1) {
                if (A[j].age < A[k].age || (A[j].age == A[k].age && A[j].phone < A[k].phone)) {
                    k = j;
                }
            } else {
                if (A[j].age > A[k].age || (A[j].age == A[k].age && A[j].phone > A[k].phone)) {
                    k = j;
                }
            }
        }
        if (i != k) {
            struct Student temp = A[i];
            A[i] = A[k];
            A[k] = temp;
        }
    }
}

void SelSortPhoneAge(int n, struct Student A[], int reverse) {
    for (int i = 0; i < n - 1; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) {
            if (reverse == 1) {
                if (A[j].phone < A[k].phone || (A[j].phone == A[k].phone && A[j].age < A[k].age)) {
                    k = j;
                }
            } else {
                if (A[j].phone > A[k].phone || (A[j].phone == A[k].phone && A[j].age > A[k].age)) {
                    k = j;
                }
            }
        }
        if (i != k) {
            struct Student temp = A[i];
            A[i] = A[k];
            A[k] = temp;
        }
    }
}

void SelSortNameSurname(int n, struct Student A[], int reverse) {
    for (int i = 0; i < n - 1; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) {
            int nameComp = strcmp(A[j].name, A[k].name);
            if (reverse == 1) {
                if (nameComp < 0 || (nameComp == 0 && strcmp(A[j].surname, A[k].surname) < 0)) {
                    k = j;
                }
            } else {
                if (nameComp > 0 || (nameComp == 0 && strcmp(A[j].surname, A[k].surname) > 0)) {
                    k = j;
                }
            }
        }
        if (i != k) {
            struct Student temp = A[i];
            A[i] = A[k];
            A[k] = temp;
        }
    }
}

void SelSortSurnameName(int n, struct Student A[], int reverse) {
    for (int i = 0; i < n - 1; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) {
            int surnameComp = strcmp(A[j].surname, A[k].surname);
            if (reverse == 1) {
                if (surnameComp < 0 || (surnameComp == 0 && strcmp(A[j].name, A[k].name) < 0)) {
                    k = j;
                }
            } else {
                if (surnameComp > 0 || (surnameComp == 0 && strcmp(A[j].name, A[k].name) > 0)) {
                    k = j;
                }
            }
        }
        if (i != k) {
            struct Student temp = A[i];
            A[i] = A[k];
            A[k] = temp;
        }
    }
}

int main() {
    srand(time(NULL));

    int n = 20; // Кол-во студентов
    int b = 0;
    int reverse = 0;
    struct Student students[n];

    printf("\n\n    \x1b[1;33m*** <<<===================   Изначальный массив структур    ===================>>>  **\x1b[0m \n");
    for (int i = 0; i < n; i++) {
        students[i] = addStudent();
        Info(students[i]);
    }

    printf("   Выберите ключ сортировки:\n");
    printf("  > 1 Имя + Фамилия\n");
    printf("  > 2 Фамилия + Имя\n");
    printf("  > 3 Номер + Возраст\n");
    printf("  > 4 Возраст + Номер\n");
    printf("   => ");
    scanf("%d", &b);

    printf("   Выберите направление сортировки:\n");
    printf("  > 1 По возрастанию\n");
    printf("  > 2 По убыванию\n");
    printf("   => ");
    scanf("%d", &reverse);

    if (b == 1) {
        SelSortNameSurname(n, students, reverse);
    } else if (b == 2) {
        SelSortSurnameName(n, students, reverse);
    } else if (b == 3) {
        SelSortPhoneAge(n, students, reverse);
    } else if (b == 4) {
        SelSortAgePhone(n, students, reverse);
    } else {
        printf("   Ошибка! Неизвестная команда!\n");
        return 1;
    }

    printf("\n\n    \x1b[1;33m*** <<<===================   Отсортированный массив структур    ===================>>>  **\x1b[0m \n");
    for (int i = 0; i < n; i++) {
        Info(students[i]);
    }
}
