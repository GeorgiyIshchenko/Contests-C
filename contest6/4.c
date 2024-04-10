#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct kaif Tree;

struct kaif
{
    int key;
    int data;
    Tree *left;
    Tree *right;
};

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

Tree *create(int key, int data)
{
    Tree *temp = (Tree *)xmalloc(sizeof(Tree));
    temp->key = key;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

Tree *search(Tree *tree, int key)
{
    if (tree != NULL)
    {
        if (key == tree->key)
        {
            return tree;
        }
        else if (key < tree->key)
        {
            return search(tree->left, key);
        }
        else
        {
            return search(tree->right, key);
        }
    }
    return tree;
}

Tree *add(Tree *tree, int key, int data)
{
    if (tree == NULL)
    {
        return create(key, data);
    }
    else if (key == tree->key)
    {
        tree->data = data;
    }
    else if (key < tree->key)
    {
        tree->left = add(tree->left, key, data);
    }
    else
    {
        tree->right = add(tree->right, key, data);
    }
    return tree;
}

Tree *minValue(Tree *node)
{
    Tree *cur = node;
    while (cur && cur->left != NULL)
        cur = cur->left;
    return cur;
}

Tree *delete(Tree *root, int key)
{
    if (root == NULL)
    {
        return root;
    }
    if (key < root->key)
        root->left = delete (root->left, key);
    else if (key > root->key)
        root->right = delete (root->right, key);
    else
    {
        if (root->left == NULL)
        {
            Tree *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Tree *temp = root->left;
            free(root);
            return temp;
        }
        Tree *temp = minValue(root->right);
        root->key = temp->key;
        root->data = temp->data;
        root->right = delete (root->right, temp->key);
        return root;
    }
    return root;
}

int main(void)
{
    char operation = '\0';
    Tree *root = NULL;
    while ((scanf("%c", &operation), operation != 'F'))
    {
        int key, data;
        if (operation == 'A')
        {
            scanf("%d %d", &key, &data);
            root = add(root, key, data);
        }
        else if (operation == 'S')
        {
            scanf("%d", &key);
            Tree *result = search(root, key);
            if (result != NULL)
            {
                printf("%d %d\n", result->key, result->data);
            }
        }
        else if (operation == 'D')
        {
            scanf("%d", &key);
            root = delete (root, key);
        }
        else if (operation == 'F')
        {
            break;
        }
    }
    if (root != NULL)
        free(root);
    return 0;
}