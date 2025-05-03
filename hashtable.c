#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node* next;
} Node;

int insert(Node** table, int tableSize, int key) {
    int index = key % tableSize;
    Node* head = table[index];
    int collision = (head != NULL);
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) exit(EXIT_FAILURE);
    newNode->key = key;
    newNode->next = head;
    table[index] = newNode;
    return collision;}

void freeTable(Node** table, int tableSize) {
    for (int i = 0; i < tableSize; i++) {
        Node* current = table[i];
        while (current) {
            Node* tmp = current;
            current = current->next;
            free(tmp);}}
    free(table);}

void generateRandomText(char* buffer, size_t size) {
    const char charset[] = " LorEm!ipsum?dolor$sit@amet, xyz123! ~Consectetur*adipiscing^elit. Qu1z_why@reading+this#nonsense? R@nd0m!junk: data{flow}=42; ~V0lUptAtE?n0n!qu3sti0n. B@ck_t0_work! Lorem*ipsum=dolor#si.I love.t%met. 7h.you.1s!isN0t@real$text. G0_@w@y! 42+xyz=99? N0pe. Just@waste^your%time. By3! ";
    for (size_t i = 0; i < size - 1; i++) {
        buffer[i] = charset[rand() % (sizeof(charset) - 1)];}
    buffer[size - 1] = '\0';}

int main() {
    srand(time(NULL));
    
    int primes[] = {11, 13, 17, 19, 23, 29, 31, 37, 41, 47,101};
    int primesCount = sizeof(primes) / sizeof(primes[0]);

    const size_t textSize = 100;
    char* text = (char*)malloc(textSize + 1);
    generateRandomText(text, textSize + 1);
    printf("\n Хеширование текста (1 КБ) методом прямого связывания \n");
    printf(" ______________________________________\n");
    printf("|Размер|Кол-во символов|Кол-во коллизий|\n");
    printf("|______|_______________|_______________|\n");

    for (int p = 0; p < primesCount; p++) {
        int tableSize = primes[p];
        Node** table = (Node**)calloc(tableSize, sizeof(Node*));

        int collisionCount = 0;
        for (size_t i = 0; i < textSize && text[i] != '\0'; i++) {
            collisionCount += insert(table, tableSize, (int)text[i]);
        }

        printf("|%4d  |%10zu     |%10d     |\n", tableSize, strlen(text), collisionCount);
        printf("|______|_______________|_______________|\n");
        freeTable(table, tableSize);
    }



    free(text);
    return 0;}
