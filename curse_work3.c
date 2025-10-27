#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iconv.h>
#define N 4000
#define RECORDS_ON_PAGE 20

typedef struct record
{
    char FIO[30];           
    short int Department;   
    char Position[22];      
    char Date[10];         
} record;

typedef struct tData
{
    struct tData *next;
    record *data;
} tData;

typedef struct
{
    tData *head;
    tData *tail;
} tQueue;
typedef struct Vertex {
    record *Data;         
    int key;              
    int balance;
    struct Vertex *Left;
    struct Vertex *Right;
} Vertex;

void AddToQueue(tData **head, tData **tail, record *data)
{
    tData *p = (tData *)malloc(sizeof(tData));
    p->data = data;
    p->next = NULL;

    if (*tail == NULL)
    {
        *head = *tail = p;
    }
    else
    {
        (*tail)->next = p;
        *tail = p;
    }
}

void clear(tData *head)
{
    tData *p = head;
    while (p != NULL)
    {
        tData *temp_p = p;
        p = p->next;
        free(temp_p);
    }
}

void InitializeQueue(tQueue *q)
{
    q->head = q->tail = NULL;
}

char* convert_cp866_to_utf8(const char *input) {
    iconv_t cd = iconv_open("UTF-8", "CP866");
    if (cd == (iconv_t)-1) return NULL;
    
    size_t in_len = strlen(input);
    size_t out_len = in_len * 4;
    char *output = malloc(out_len);
    char *out_ptr = output;
    char *in_ptr = (char*)input;
    
    if (iconv(cd, &in_ptr, &in_len, &out_ptr, &out_len) == (size_t)-1) {
        free(output);
        iconv_close(cd);
        return NULL;
    }
    
    *out_ptr = '\0';
    iconv_close(cd);
    return output;
}

int less(const record *a, const record *b)
{
    int date_cmp = strcmp(a->Date, b->Date);
    if (date_cmp < 0)
    {
        return 1;
    }
    else if (date_cmp > 0)
    {
        return 0;
    }

    char fio_a[32], fio_b[32];
    strncpy(fio_a, a->FIO, sizeof(fio_a) - 1);
    fio_a[sizeof(fio_a) - 1] = '\0';
    strncpy(fio_b, b->FIO, sizeof(fio_b) - 1);
    fio_b[sizeof(fio_b) - 1] = '\0';

    for (int i = 0; fio_a[i]; i++)
        fio_a[i] = tolower((unsigned char)fio_a[i]);
    for (int i = 0; fio_b[i]; i++)
        fio_b[i] = tolower((unsigned char)fio_b[i]);

    int fio_cmp = strcmp(fio_a, fio_b);
    if (fio_cmp < 0)
    {
        return 1;
    }
    else if (fio_cmp > 0)
    {
        return 0;
    }

    return 1;
}

int getDayFromDate(const char *date)
{
    char dayStr[3];
    strncpy(dayStr, date, 2);
    dayStr[2] = '\0';
    return atoi(dayStr);
}

int compareDay(const record *rec, int searchDay)
{
    return getDayFromDate(rec->Date) - searchDay;
}

int compareByDay(const record *rec, int searchDay)
{
    int day = getDayFromDate(rec->Date);
    if (day < searchDay) return -1;
    if (day > searchDay) return 1;
    return 0;
}

void BinarySearchByDay(int n, record *records, int searchDay, tData **head, tData **tail) {
    int L = 0, R = n - 1;
    int m;
    int found_index = -1;
    
    while (L <= R)
    {
        m = (L + R) / 2;
        int cmp = compareByDay(&records[m], searchDay);
        
        if (cmp < 0)
        {
            L = m + 1;
        }
        else if (cmp > 0)
        {
            R = m - 1;
        }
        else
        {
            found_index = m;
            R = m - 1; 
        }
    }
    
    if (found_index == -1)
    {
        printf("Записи с днем рождения '%d' не найдены.\n", searchDay);
        return;
    }
    
    int index = found_index;
    int count = 0;
    while (index < n && compareByDay(&records[index], searchDay) == 0)
    {
        AddToQueue(head, tail, &records[index]);
        index++;
        count++;
    }
    
    printf("Найдено %d записей с днем рождения '%d'\n", count, searchDay);
}

typedef record *(*GetRecordFunc)(int index, void *source);

record *getRecordFromArray(int index, void *source)
{
    record *arr = (record *)source;
    return &arr[index];
}

record *getRecordFromQueue(int index, void *source)
{
    tData *cur = (tData *)source;
    for (int i = 0; i < index && cur; i++)
        cur = cur->next;
    return cur ? cur->data : NULL;
}

int findPage(int pages_count)
{
    int input;
    printf("Введите номер страницы на которую желаете перейти: ");
    
    do{
        scanf("%d", &input);
        if (input < 1 || input > pages_count)
        {
            printf("Введите действительный диапазон от 1 до %d: ", pages_count);
        }
        else break;
    } while (1);
    return input - 1;
}

int findRecord(int records_count)
{
    int input;
    printf("Введите номер записи на которую желаете перейти: ");
    
    do{
        scanf("%d", &input);
        if (input < 1 || input > records_count)
        {
            printf("Введите действительный диапазон от 1 до %d: ", records_count);
        }
        else break;
    } while (1);
    return (input - 1) / RECORDS_ON_PAGE;
}

void paginateRecords(void *source, int records_count, GetRecordFunc getRecord, const char *title)
{
    if (records_count == 0)
    {
        printf("%s\n", title);
        printf("Нет данных для отображения.\n");
        return;
    }

    int current_page = 0;
    int input;

    do
    {
        system("clear");

        int pages_count = (records_count + RECORDS_ON_PAGE - 1) / RECORDS_ON_PAGE;
        


        int pageStart = current_page * RECORDS_ON_PAGE;
        int pageEnd = pageStart + RECORDS_ON_PAGE;
        if (pageEnd > records_count)
            pageEnd = records_count;


        printf("%s\n", title);
        printf("Страница: %d/%d. Записи с %d по %d из %d. \n", current_page + 1, pages_count, pageStart + 1, pageEnd, records_count);
        printf("╔═════╦═══════════════════════════════╦════════╦═══════════════════════╦═══════════╗\n");
        printf("║%-4s   ║ %-30s   ║ %-4s  ║     %-20s       ║ %-10s    ║\n",
               "№", "ФИО", "Отдел", "Должность", "Дата");
        printf("╠═════╬═══════════════════════════════╬════════╬═══════════════════════╬═══════════╣\n");
        
        for (int i = pageStart; i < pageEnd; i++)
        {
            record *r = getRecord(i, source);
            if (!r) { continue; }
             
            char *fio_utf8 = convert_cp866_to_utf8(r->FIO);
            char *position_utf8 = convert_cp866_to_utf8(r->Position);
            
            printf("║%-4d ║ %-30s ║ %-6hd ║ %-20s ║ %-10s║\n",
                   i + 1, 
                   fio_utf8 ? fio_utf8 : r->FIO,
                   r->Department,
                   position_utf8 ? position_utf8 : r->Position,
                   r->Date);
            
            free(fio_utf8);
            free(position_utf8);
        }
        printf("╚═════╩═══════════════════════════════╩════════╩═══════════════════════╩═══════════╝\n");
        
        printf("\nУправление: \n");
        printf ("\n1 - предыдущая");
        printf ("\n2 - следующая");
        printf ("\n3 - начало");
        printf ("\n4 - конец");
        printf ("\n5 - перейти на страницу");
        printf ("\n6 - перейти к записи");
        printf ("\n7 - Сортировка ( поиск )\n");
        
        
        printf("Введите команду: ");
        scanf("%d", &input);

        if (input == 1 && current_page > 0)
            current_page--;
        else if (input == 2 && current_page < pages_count - 1)
            current_page++;
        else if (input == 3)
            current_page = 0;
        else if (input == 4)
            current_page = pages_count - 1;
        else if (input == 5)
            current_page = findPage(pages_count);
        else if (input == 6)
            current_page = findRecord(records_count);
        else if (input == 7)
            break;

    } while (1);
}

void heapify(record arr[], int n, int i)
{
    int largest = i;        
    int left = 2 * i + 1;  
    int right = 2 * i + 2;  

    if (left < n && less(&arr[largest], &arr[left]))
        largest = left;

    if (right < n && less(&arr[largest], &arr[right]))
        largest = right;

    if (largest != i)
    {
        record temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(record arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        record temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}


void ll_rotation(Vertex **p) {
    Vertex *q = (*p)->Left;
    (*p)->Left = q->Right;
    q->Right = *p;
    (*p)->balance = 0;
    q->balance = 0;
    *p = q;
}

void lr_rotation(Vertex **p) {
    Vertex *q = (*p)->Left;
    Vertex *r = q->Right;

    if (r->balance < 0) (*p)->balance = 1;
    else (*p)->balance = 0;

    if (r->balance > 0) q->balance = -1;
    else q->balance = 0;

    r->balance = 0;

    q->Right = r->Left;
    (*p)->Left = r->Right;
    r->Left = q;
    r->Right = *p;
    *p = r;
}

void rl_rotation(Vertex **p) {
    Vertex *q = (*p)->Right;
    Vertex *r = q->Left;

    if (r->balance > 0) (*p)->balance = -1;
    else (*p)->balance = 0;

    if (r->balance < 0) q->balance = 1;
    else q->balance = 0;

    r->balance = 0;

    q->Left = r->Right;
    (*p)->Right = r->Left;
    r->Left = *p;
    r->Right = q;
    *p = r;
}

void rr_rotation(Vertex **p) {
    Vertex *q = (*p)->Right;
    (*p)->Right = q->Left;
    q->Left = *p;
    (*p)->balance = 0;
    q->balance = 0;
    *p = q;
}

int insert_AVL(int key, record *data, Vertex **p) {
    int growth = 0;
    if (*p == NULL) {
        *p = (Vertex *)malloc(sizeof(Vertex));
        (*p)->key = key;
        (*p)->Data = data;
        (*p)->balance = 0;
        (*p)->Left = (*p)->Right = NULL;
        return 1;
    }

    if (key < (*p)->key) {
        growth = insert_AVL(key, data, &(*p)->Left);
        if (growth) {
            if ((*p)->balance > 0) {
                (*p)->balance = 0;
                return 0;
            } else if ((*p)->balance == 0) {
                (*p)->balance = -1;
                return 1;
            } else {
                if ((*p)->Left->balance < 0)
                    ll_rotation(p);
                else
                    lr_rotation(p);
                return 0;
            }
        }
    } else {
        growth = insert_AVL(key, data, &(*p)->Right);
        if (growth) {
            if ((*p)->balance < 0) {
                (*p)->balance = 0;
                return 0;
            } else if ((*p)->balance == 0) {
                (*p)->balance = 1;
                return 1;
            } else {
                if ((*p)->Right->balance > 0)
                    rr_rotation(p);
                else
                    rl_rotation(p);
                return 0;
            }
        }
    }
    return 0;
}



int compareByDepartment(const record *rec, int searchDept) {
    if (rec->Department < searchDept) return -1;
    if (rec->Department > searchDept) return 1;
    return 0;
}

void BinarySearchByDepartment(int n, record *records, int searchDept, tData **head, tData **tail) {
    int L = 0, R = n - 1;
    int m;
    int found_index = -1;
    
    while (L <= R)
    {
        m = (L + R) / 2;
        int cmp = compareByDepartment(&records[m], searchDept);
        
        if (cmp < 0)
        {
            L = m + 1;
        }
        else if (cmp > 0)
        {
            R = m - 1;
        }
        else
        {
            found_index = m;
            R = m - 1; 
        }
    }
    
    if (found_index == -1)
    {
        printf("Записи с номером отдела '%d' не найдены.\n", searchDept);
        return;
    }
    
    int index = found_index;
    int count = 0;
    while (index < n && compareByDepartment(&records[index], searchDept) == 0)
    {
        AddToQueue(head, tail, &records[index]);
        index++;
        count++;
    }
    
    printf("Найдено %d записей с номером отдела '%d'\n", count, searchDept);
}

void inorder_traversal(Vertex *node, record **treeRecords, int *index) {
    if (node == NULL) return;
    inorder_traversal(node->Left, treeRecords, index);
    treeRecords[(*index)++] = node->Data;
    inorder_traversal(node->Right, treeRecords, index);
}

void paginateRecordsAVL(Vertex *root, int records_count, const char *title) {
    if (root == NULL) {
        printf("%s\n", title);
        printf("Дерево пусто.\n");
        return;
    }

    record **treeRecords = malloc(records_count * sizeof(record*));
    int index = 0;

    inorder_traversal(root, treeRecords, &index);
    
    int actual_count = index; 
    
    if (actual_count == 0) {
        printf("%s\n", title);
        printf("Нет данных для отображения.\n");
        free(treeRecords);
        return;
    }

    int current_page = 0;
    int input;

    do
    {
        system("clear");

        int pages_count = (actual_count + RECORDS_ON_PAGE - 1) / RECORDS_ON_PAGE;
        if (current_page >= pages_count)
            current_page = pages_count - 1;
        if (current_page < 0)
            current_page = 0;

        int pageStart = current_page * RECORDS_ON_PAGE;
        int pageEnd = pageStart + RECORDS_ON_PAGE;
        if (pageEnd >= actual_count)
            pageEnd = actual_count;

        printf("%s\n", title);
        printf("Страница: %d/%d. Записи с %d по %d из %d.\n", current_page + 1, pages_count, pageStart + 1, pageEnd, actual_count);
        printf("╔═════╦═══════════════════════════════╦════════╦═══════════════════════╦═══════════╗\n");
        printf("║%-4s   ║ %-30s   ║ %-6s  ║ %-20s           ║ %-10s    ║\n",
               "№", "ФИО", "Отдел", "Должность", "Дата");
        printf("╠═════╬═══════════════════════════════╬════════╬═══════════════════════╬═══════════╣\n");
        
        for (int i = pageStart; i < pageEnd; i++)
        {
            record *r = treeRecords[i];
            if (!r) { continue; }
             
            char *fio_utf8 = convert_cp866_to_utf8(r->FIO);
            char *position_utf8 = convert_cp866_to_utf8(r->Position);
            
            printf("║%-4d ║ %-30s ║ %-6hd ║ %-20s ║ %-10s║\n",
                   i + 1, 
                   fio_utf8 ? fio_utf8 : r->FIO,
                   r->Department,
                   position_utf8 ? position_utf8 : r->Position,
                   r->Date);
            
            free(fio_utf8);
            free(position_utf8);
        }
        printf("╚═════╩═══════════════════════════════╩════════╩═══════════════════════╩═══════════╝\n");
        
        printf("\nУправление: \n");
        printf("1 - предыдущая\n");
        printf("2 - следующая\n");
        printf("3 - начало\n");
        printf("4 - конец\n");
        printf("5 - перейти на страницу\n");
        printf("6 - перейти к записи\n");
        printf("7 - Поиск по номеру отдела\n");
        printf("8 - Выход в терминал\n");
        
        printf("Введите команду: ");
        scanf("%d", &input);

        if (input == 1 && current_page > 0)
            current_page--;
        else if (input == 2 && current_page < pages_count - 1)
            current_page++;
        else if (input == 3)
            current_page = 0;
        else if (input == 4)
            current_page = pages_count - 1;
        else if (input == 5)
            current_page = findPage(pages_count);
        else if (input == 6)
            current_page = findRecord(actual_count);
        else if (input == 7) {
            int searchDept;
            printf("Введите номер отдела для поиска: ");
            scanf("%d", &searchDept);
            
            tData *searchHead = NULL;
            tData *searchTail = NULL;
            
            record *deptSortedRecords = malloc(actual_count * sizeof(record));
            for (int i = 0; i < actual_count; i++) {
                deptSortedRecords[i] = *treeRecords[i];
            }
            
            for (int i = 0; i < actual_count - 1; i++) {
                for (int j = 0; j < actual_count - i - 1; j++) {
                    if (deptSortedRecords[j].Department > deptSortedRecords[j + 1].Department) {
                        record temp = deptSortedRecords[j];
                        deptSortedRecords[j] = deptSortedRecords[j + 1];
                        deptSortedRecords[j + 1] = temp;
                    }
                }
            }
            
            BinarySearchByDepartment(actual_count, deptSortedRecords, searchDept, &searchHead, &searchTail);
            
            int search_count = 0;
            tData *tmp = searchHead;
            while (tmp) {
                search_count++;
                tmp = tmp->next;
            }
            
            if (search_count > 0) {
                paginateRecords(searchHead, search_count, getRecordFromQueue, "РЕЗУЛЬТАТЫ ПОИСКА ПО ОТДЕЛУ");
            }
        }
        else if (input == 8) {
            break;
        }

    } while (1);
    
}



int main()
{
    FILE *fp;
    fp = fopen("testBase2.dat", "rb");
    if (fp == NULL)
    {
        printf("Ошибка открытия файла!\n");
        return 1;
    }
    
    record *allRecords = malloc(N * sizeof(record));
    int records_count = fread(allRecords, sizeof(record), N, fp);
    printf("%d records read\n", records_count);

    int choice;
    printf (" ==========  Вывести на экран таблицы на основе работы с .... =========  ");
    printf("\n1 - Со списком");
    printf("\n2 - С АВЛ-деревом");
    printf("\nВведите команду: ");
    scanf ("%d", &choice);
    if (choice == 1) {
    
        paginateRecords(allRecords, records_count, getRecordFromArray, "\n\nВсе записи");
    
        record *sortedRecords = malloc(records_count * sizeof(record));
        memcpy(sortedRecords, allRecords, records_count * sizeof(record));
        heapSort(sortedRecords, records_count);
        
        paginateRecords(sortedRecords, records_count, getRecordFromArray, "\n\nОтсортированные записи");

        int searchDay;
        printf("Поиск по дню рождения (число от 1 до 31)\n");
        scanf("%d", &searchDay);
        
        tData *searchHead = NULL;
        tData *searchTail = NULL;
            
        if (searchDay < 1 || searchDay > 31) {
            printf("Неверный день! Введите число от 1 до 31\n");
        }
        else {
            BinarySearchByDay(records_count, sortedRecords, searchDay, &searchHead, &searchTail);
        }
        
        int search_count = 0;
        tData *tmp = searchHead;
        while (tmp) {
            search_count++;
            tmp = tmp->next;
        }
        
        if (search_count > 0) {
            paginateRecords(searchHead, search_count, getRecordFromQueue, "РЕЗУЛЬТАТЫ ПОИСКА ПО ДНЮ РОЖДЕНИЯ");
        }
    }

    else if (choice == 2) {
        Vertex *AVL = NULL;
    for (int i = 0; i < N; i++) {
        insert_AVL(allRecords[i].Department, &allRecords[i], &AVL);
    }

    paginateRecordsAVL(AVL, records_count, "\n\nАВЛ-дерево (сортировка происходила по параметру: отдел)");
    }
    
}
