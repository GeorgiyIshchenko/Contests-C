#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 27

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

void *xrealloc(void *array, int size)
{
    void *ptr = realloc(array, size);
    if (ptr == NULL)
    {
        printf("Memory Error");
        exit(137);
    }
    return ptr;
}

typedef enum
{
    WORD,
    NODE
} Tag;

typedef struct r
{
    char *key;
    int value;
} Record;

typedef struct t
{
    Tag t;
    union
    {
        Record *r;
        struct tree *nodes[M + 1];
    };
} Tree;

int ord(char c)
{
    return c ? c - 'a' + 1 : 0;
}

Record *create_record(char *key, int value)
{
    Record *r = (Record *)xmalloc(sizeof(Record));
    r->key = strdup(key);
    r->value = value;
    return r;
}

Tree *create_from_record(Record *r)
{
    Tree *t = (Tree *)xmalloc(sizeof(Tree));
    t->t = WORD;
    t->r = r;
    return t;
}

Tree *create_word(char *key, int value)
{
    return create_from_record(create_record(key, value));
}

Tree *create_node(void)
{
    Tree *t = calloc(1, sizeof(Tree));
    t->t = NODE;
    return t;
}

Tree *insert(Tree *t, char *key, int value)
{
    if (!t)
        return create_word(key, value);
    int i = 0;
    Tree *root = t;
    while (t->t == NODE)
    {
        Tree **p = &t->nodes[ord(key[i])];
        i++;
        if (!*p)
        {
            *p = create_word(key, value);
            return root;
        }
        t = *p;
    }
    if (i && !key[i - 1])
    {
        t->r->value = value;
        return root;
    }
    int j = i;
    for (; key[i]; i++)
    {
        if (key[i] != t->r->key[i])
        {
            break;
        }
    }
    if (!key[i] && !t->r->key[i])
    {
        t->r->value = value;
        return root;
    }
    Record *other = t->r;
    t->t = NODE;
    memset(t->nodes, 0, sizeof(t->nodes));

    for (; j < i; j++)
    {
        Tree *p = create_node();
        t->nodes[ord(key[j])] = p;
        t = p;
    }

    t->nodes[ord(other->key[i])] = create_from_record(other);
    t->nodes[ord(key[i])] = create_word(key, value);
    return root;
}

int main(void)
{
    char *s = (char*)xmalloc(sizeof(char) * 2001);
    scanf("%s", s);

    int len = strlen(s);
    s = (char*)xrealloc(s, sizeof(char) * len);

    int cnt = 0;
    Tree *root = NULL;
    for(int i = 0; i < len; i++)
    {
        insert(root, *(s + i), 1);
    }
    printf("%d", cnt);

    return 0;
}