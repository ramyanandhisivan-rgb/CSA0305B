
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char word[50];
    struct Node *left, *right;
};

struct Node* createNode(char word[]) {
    struct Node* n = malloc(sizeof(struct Node));

    strcpy(n->word, word);
    n->left = n->right = NULL;

    return n;
}

struct Node* insert(struct Node* root, char word[]) {
    if (root == NULL)
        return createNode(word);

    int cmp = strcmp(word, root->word);

    if (cmp < 0)
        root->left = insert(root->left, word);
    else if (cmp > 0)
        root->right = insert(root->right, word);

    return root;
}

int search(struct Node* root, char word[]) {
    if (root == NULL)
        return 0;

    int cmp = strcmp(word, root->word);

    if (cmp == 0)
        return 1;

    if (cmp < 0)
        return search(root->left, word);

    return search(root->right, word);
}

void autocomplete(struct Node* root, char prefix[]) {
    if (root == NULL)
        return;

    autocomplete(root->left, prefix);

    if (strncmp(root->word, prefix, strlen(prefix)) == 0)
        printf("%s ", root->word);

    autocomplete(root->right, prefix);
}

void rangeSearch(struct Node* root, char low[], char high[]) {
    if (root == NULL)
        return;

    if (strcmp(root->word, low) > 0)
        rangeSearch(root->left, low, high);

    if (strcmp(root->word, low) >= 0 &&
        strcmp(root->word, high) <= 0)
        printf("%s ", root->word);

    if (strcmp(root->word, high) < 0)
        rangeSearch(root->right, low, high);
}

int main() {
    struct Node* root = NULL;

    char *words[] = {
        "apple", "application", "banana",
        "bat", "cat", "car",
        "dog", "doll", "elephant",
        "fish"
    };

    int n = 10;

    for (int i = 0; i < n; i++)
        root = insert(root, words[i]);

    printf("Dictionary Search:\n");

    if (search(root, "banana"))
        printf("banana: Found\n");
    else
        printf("banana: Not Found\n");

    printf("\nAutocomplete for 'ca': ");
    autocomplete(root, "ca");

    printf("\n\nAlphabetical Range (banana to dog): ");
    rangeSearch(root, "banana", "dog");

    printf("\n");

    return 0;
}
