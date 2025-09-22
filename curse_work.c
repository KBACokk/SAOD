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

void navigatePages(record *allRecords, int records_count)
{
    int current_page = 0;
    int input;

    do
    {
        system("cls");

        int pages_count = records_count / RECORDS_ON_PAGE;
        if (records_count % RECORDS_ON_PAGE != 0)
        {
            pages_count++;
        }

        if (current_page >= pages_count)
        {
            current_page = pages_count - 1;
        }
        if (current_page < 0)
        {
            current_page = 0;
        }

        int pageStart = current_page * RECORDS_ON_PAGE;
        int pageEnd = pageStart + RECORDS_ON_PAGE;
        if (pageEnd > records_count)
        {
            pageEnd = records_count;
        }

        printf("Страница: %d/%d. Записи с %d по %d из %d.\n",
               current_page + 1, pages_count, pageStart + 1, pageEnd, records_count);
        printf("-----------------------------------------------------------------------------------------\n");
        printf("|%-4s | %-30s | %-8s | %-20s | %-10s|\n",
               "№", "ФИО", "Отдел", "Должность", "Дата");
        printf("-----------------------------------------------------------------------------------------\n");
        
        for (int i = pageStart; i < pageEnd; i++)
        {
            char *fio_utf8 = convert_cp866_to_utf8(allRecords[i].FIO);
            char *position_utf8 = convert_cp866_to_utf8(allRecords[i].Position);
            
            printf("|%-4d | %-30s | %-6hd | %-20s | %-10s|\n",
                   i + 1, 
                   fio_utf8 ? fio_utf8 : allRecords[i].FIO,
                   allRecords[i].Department,
                   position_utf8 ? position_utf8 : allRecords[i].Position,
                   allRecords[i].Date);
            
            free(fio_utf8);
            free(position_utf8);
        }
        printf("-----------------------------------------------------------------------------------------\n");
        
        printf("\nУправление: \n1 - предыдущая \n2 - следующая \n3 - вернутся в начало \n4 - перейти в конец \n0 - сортировка\n");
        printf("Введите команду: ");

        scanf("%d", &input);

        if (input == 1 && current_page > 0)
        {
            current_page--;
        }
        else if (input == 2)
        {
            if (current_page < pages_count - 1)
            {
                current_page++;
            }
        }
        else if (input == 3)
        {
            current_page = 0;
        }
        else if (input == 4)
        {
            current_page = pages_count - 1;
        }
        else if (input == 0)
        {
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
    
    int current_page = 0;
    navigatePages(allRecords, records_count);
    
    record *sortedRecords = malloc(records_count * sizeof(record));
    memcpy(sortedRecords, allRecords, records_count * sizeof(record));
    
    heapSort(sortedRecords, records_count);
    
    navigatePages(sortedRecords, records_count);

    free(allRecords);
    free(sortedRecords);
    fclose(fp);
    return 0;
}
