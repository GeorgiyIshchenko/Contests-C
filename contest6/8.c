#include <stdio.h>
#include <stdlib.h>

#define INPUT "words.in"
#define OUTPUT "words.out"

void *xmalloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        printf("Memory error.");
        exit(137);
    }
    return ptr;
}

typedef struct node
{
    char data;
    struct node *next;
    struct node *previous;
} Node;


typedef struct List
{
    Node *head;
    Node *end;
} List;

void pushBack(List *list, char data)
{
    Node *newNode = (Node*)xmalloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (list->head == NULL)
    {
        newNode->previous = NULL;
        list->head = newNode;
        list->end = newNode;
        return;
    }
    list->end->next = newNode;
    newNode->previous = list->end;
    list->end = newNode;
}

void delete(List *list, Node *node)
{
    if (list->head == NULL || list->end == NULL || node == NULL)
        return;
    if (list->head == node)
        list->head = node->next;
    if (list->end == node)
        list->end = node->previous;
    if (node->next != NULL)
        node->next->previous = node->previous;
    if (node->previous != NULL)
        node->previous->next = node->next;
    free(node);
}

void clear_middle(List *list, int word_len)
{
    if (word_len % 2 == 1)
    {
        Node *cur = list->end;
        for (int i = 0; i < word_len / 2; i++)
        {
            cur = cur->previous;
        }
        delete (list, cur);
        if (list->end && list->end->data == ' ')
        {
            delete(list, list->end);
        }
    }
}

void print_list_to_file(List *list, FILE *file)
{
    Node *cur = list->head;
    while (cur != NULL)
    {
        fprintf(file, "%c", cur->data);
        cur = cur->next;
    }
    fclose(file);
}

int main(void)
{
    FILE *input = fopen(INPUT, "r");

    List *list = (List*)xmalloc(sizeof(List));   
    list->head = NULL;
    list->end = NULL;
    char scanner;
    int word_len = 0;
    while ((fscanf(input, "%c", &scanner)))
    {
        if (scanner == ' ' || scanner == '.')
        {
            clear_middle(list, word_len);
            word_len = 0;
        }
        else
        {
            word_len++;
        }
        pushBack(list, scanner);
        if (scanner == '.')
        {
            break;
        }
    }
    fclose(input);
    FILE *output = fopen(OUTPUT, "w");
    print_list_to_file(list, output);
    return 0;
}