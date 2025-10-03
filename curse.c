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

typedef struct
{
    tData *head;
    tData *tail;
} tQueue;

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

int compare_records(const void *a, const void *b) {
    const record *rec_a = *(const record **)a;
    const record *rec_b = *(const record **)b;
    return less(rec_a, rec_b) ? -1 : 1;
}

void Heapmake(record **A, int L, int R) {
    record *x = A[L];
    int i = L;
    
    while (1) {
        int j = 2 * i + 1;
        if (j > R) break;
        
        if (j < R && less(A[j], A[j + 1])) {
            j++;
        }

        if (!less(x, A[j])) break;

        A[i] = A[j];
        i = j;
    }
    
    A[i] = x;
}

void HeapSort(record **A, int n) {

    for (int L = n / 2 - 1; L >= 0; L--) {
        Heapmake(A, L, n - 1);
    }

    for (int R = n - 1; R > 0; R--) {
        record *temp = A[0];
        A[0] = A[R];
        A[R] = temp;
        Heapmake(A, 0, R - 1);
    }
}

typedef record *(*GetRecordFunc)(int index, void *source);

int findPage(int pages_count){
    int input;
    printf("Введите номер страницы на которую желаете перейти:");
    
    do{
        scanf("%d", &input);
        if (input<1 || input>pages_count){
            printf ("Введите действительный диапазон от 1 до %d:", pages_count);
        }
        else break;
    }while (1);
    return input-1;
}

int findRecord(int records_on_page,int records_count){
    int input;
    printf("Введите номер записи на которую желаете перейти:");
    
    do{
        scanf("%d", &input);
        if (input<1 || input>records_count){
            printf ("Введите действительный диапазон от 1 до %d:", records_count);
        }
        else break;
    }while (1);
    return (input-1) / records_on_page;
}

void paginateRecords(void *source, int records_count, GetRecordFunc getRecord, const char *title)
{
    if (records_count == 0)
    {
        system("chcp 65001 > nul");
        printf("%s\n", title);
        printf("Нет данных для отображения.\n");
        return;
    }

    int current_page = 0;
    int input;

    do
    {
        system("cls");

        int pages_count = (records_count + RECORDS_ON_PAGE - 1) / RECORDS_ON_PAGE;
        if (current_page >= pages_count)
            current_page = pages_count - 1;
        if (current_page < 0)
            current_page = 0;

        int pageStart = current_page * RECORDS_ON_PAGE;
        int pageEnd = pageStart + RECORDS_ON_PAGE;
        if (pageEnd > records_count)
            pageEnd = records_count;

        system("chcp 65001 > nul");
        printf("%s\n", title);
        printf("Страница: %d/%d. Записи с %d по %d из %d.\n",
               current_page + 1, pages_count, pageStart + 1, pageEnd, records_count);
        printf("╔═════╦═══════════════════════════════╦════════╦═══════════════════════╦═══════════╗\n");
        printf("║%-6s ║ %-32s ║ %-9s  ║ %-30s ║ %-14s║                    ║\n",
               "№", "ФИО", "Отдел", "Должность", "Дата");
        printf("╠═════╬═══════════════════════════════╬════════╬═══════════════════════╬═══════════╣\n");

        for (int i = pageStart; i < pageEnd; i++)
        {
            record *r = getRecord(i, source);
            if (!r)
                continue;
                
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
        system("chcp 65001 > nul");
        printf("\n\x1b[1;35mУправление: \n -> 1 предыдущая \n -> 2 следующая \n -> 3 начало \n -> 4 конец \n -> 5 выбрать страницу \n -> 6 выбрать запись \n -> 7 сортировка (поиск)\x1b[0m\n");
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
            current_page = findRecord(RECORDS_ON_PAGE, records_count);
        else if (input == 7)
            break;

    } while (1);
}

record *getRecordFromArray(int index, void *source)
{
    record *arr = (record *)source;
    return &arr[index];
}

record *getRecordFromPtrArray(int index, void *source)
{
    record **arr = (record **)source;
    return arr[index];
}

record *getRecordFromQueue(int index, void *source)
{
    tData *cur = (tData *)source;
    for (int i = 0; i < index && cur; i++)
        cur = cur->next;
    return cur ? cur->data : NULL;
}

void fillQ(tData **head, tData **tail, record *Records, int records_count)
{
    for (int i = 0; i < records_count; i++)
    {
        AddToQueue(head, tail, &Records[i]);
    }
}

void trim_trailing_spaces(char *str) {
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[len - 1] = '\0';
        len--;
    }
}

void convert_date_format(const char *input_date, char *output_date)
{
    if (strlen(input_date) == 10 && input_date[2] == '.' && input_date[5] == '.')
    {
        output_date[0] = input_date[0];
        output_date[1] = input_date[1];
        output_date[2] = '-';
        output_date[3] = input_date[3];
        output_date[4] = input_date[4];
        output_date[5] = '-';
        output_date[6] = input_date[8];
        output_date[7] = input_date[9];
        output_date[8] = '\0';
    }
    else
    {
        strncpy(output_date, input_date, 9);
        output_date[9] = '\0';
    }
}

int compare_dates(const char *date1, const char *date2)
{
    char date1_clean[10], date2_clean[10];
    strncpy(date1_clean, date1, sizeof(date1_clean) - 1);
    date1_clean[sizeof(date1_clean) - 1] = '\0';
    strncpy(date2_clean, date2, sizeof(date2_clean) - 1);
    date2_clean[sizeof(date2_clean) - 1] = '\0';
    
    trim_trailing_spaces(date1_clean);
    trim_trailing_spaces(date2_clean);
    
    return strcmp(date1_clean, date2_clean);
}

void BinarySearchByDate(int n, record **records, const char *target_date_input, tData **head, tData **tail)
{
    char target_date[10];
    convert_date_format(target_date_input, target_date);
    
    printf("Поиск по дате: '%s' (преобразовано в '%s')\n", target_date_input, target_date);
    
    int found_count = 0;
    for (int i = 0; i < n; i++)
    {
        char record_date_clean[10];
        strncpy(record_date_clean, records[i]->Date, sizeof(record_date_clean) - 1);
        record_date_clean[sizeof(record_date_clean) - 1] = '\0';
        trim_trailing_spaces(record_date_clean);
        
        int cmp = strcmp(record_date_clean, target_date);
        
        if (cmp == 0)
        {
            printf("НАЙДЕНО СОВПАДЕНИЕ: запись %d, дата='%s' (очищено: '%s')\n", i, records[i]->Date, record_date_clean);
            AddToQueue(head, tail, records[i]);
            found_count++;
        }
    }
    
    printf("Всего найдено записей: %d\n", found_count);
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

    paginateRecords(allRecords, records_count, getRecordFromArray, "ВСЕ ЗАПИСИ");
    
    record **recordPointers = malloc(records_count * sizeof(record *));
    for (int i = 0; i < records_count; i++) {
        recordPointers[i] = &allRecords[i];
    }
    
    printf("Сортировка методом Вилльямса-Флойда...\n");
    HeapSort(recordPointers, records_count);
    
    paginateRecords(recordPointers, records_count, getRecordFromPtrArray, "ОТСОРТИРОВАННЫЕ ЗАПИСИ (Метод Вилльямса-Флойда)");

    char SearchDate[11];
    
    do
    {
        printf("Введите дату для поиска (в формате дд.мм.гггг): ");
        system("chcp 866 > nul");
        if (scanf("%10s", SearchDate) != 1) {
            printf("Ошибка ввода даты.\n");
            continue;
        }
        system("chcp 65001 > nul");
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (strlen(SearchDate) != 10 || SearchDate[2] != '.' || SearchDate[5] != '.')
        {
            printf("Неверный формат даты. Используйте дд.мм.гггг (например: 09.02.1976)\n");
            continue;
        }
        
        int valid = 1;
        for (int i = 0; i < 10; i++) {
            if (i == 2 || i == 5) {
                if (SearchDate[i] != '.') valid = 0;
            } else {
                if (!isdigit((unsigned char)SearchDate[i])) valid = 0;
            }
        }
        
        if (!valid) {
            printf("Дата должна содержать только цифры и точки в формате дд.мм.гггг\n");
            continue;
        }
        
        break;
    } while (1);
    
    tData *SearchHead = NULL;
    tData *SearchTail = NULL;
    int search_count = 0;
    
    BinarySearchByDate(records_count, recordPointers, SearchDate, &SearchHead, &SearchTail);
    
    tData *tmp = SearchHead;
    while (tmp)
    {
        search_count++;
        tmp = tmp->next;
    }
    
    if (search_count > 0)
    {
        char title[100];
        snprintf(title, sizeof(title), "РЕЗУЛЬТАТЫ ПОИСКА: дата=%s", SearchDate);
        paginateRecords(SearchHead, search_count, getRecordFromQueue, title);
    }
    else
    {
        printf("Записей с датой '%s' не найдено.\n", SearchDate);
        printf("Убедитесь, что:\n");
        printf("1. Дата введена в формате дд.мм.гггг (например: 09.02.1976)\n");
        printf("2. Такая запись существует в базе данных\n");
    }

    clear(SearchHead);
    free(recordPointers);
    free(allRecords);
    fclose(fp);
    return 0;
}
