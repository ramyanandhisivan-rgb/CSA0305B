
#include <stdio.h>
#include <stdlib.h>

#define T 3

typedef struct BTreeNode {
    int keys[2 * T - 1];
    struct BTreeNode *child[2 * T];
    int n;
    int leaf;
} BTreeNode;

BTreeNode* createNode(int leaf) {
    BTreeNode *node = malloc(sizeof(BTreeNode));
    node->n = 0;
    node->leaf = leaf;

    for (int i = 0; i < 2 * T; i++)
        node->child[i] = NULL;

    return node;
}

void traverse(BTreeNode *root) {
    if (root == NULL)
        return;

    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            traverse(root->child[i]);

        printf("%d ", root->keys[i]);
    }

    if (!root->leaf)
        traverse(root->child[i]);
}

BTreeNode* search(BTreeNode *root, int key) {
    int i = 0;

    while (i < root->n && key > root->keys[i])
        i++;

    if (i < root->n && root->keys[i] == key)
        return root;

    if (root->leaf)
        return NULL;

    return search(root->child[i], key);
}

void splitChild(BTreeNode *parent, int i, BTreeNode *full) {
    BTreeNode *newNode = createNode(full->leaf);
    newNode->n = T - 1;

    for (int j = 0; j < T - 1; j++)
        newNode->keys[j] = full->keys[j + T];

    if (!full->leaf) {
        for (int j = 0; j < T; j++)
            newNode->child[j] = full->child[j + T];
    }

    full->n = T - 1;

    for (int j = parent->n; j >= i + 1; j--)
        parent->child[j + 1] = parent->child[j];

    parent->child[i + 1] = newNode;

    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = full->keys[T - 1];
    parent->n++;
}

void insertNonFull(BTreeNode *node, int key) {
    int i = node->n - 1;

    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->n++;
    } else {
        while (i >= 0 && key < node->keys[i])
            i--;

        i++;

        if (node->child[i]->n == 2 * T - 1) {
            splitChild(node, i, node->child[i]);

            if (key > node->keys[i])
                i++;
        }

        insertNonFull(node->child[i], key);
    }
}

void insert(BTreeNode **root, int key) {
    if (*root == NULL) {
        *root = createNode(1);
        (*root)->keys[0] = key;
        (*root)->n = 1;
        return;
    }

    BTreeNode *r = *root;

    if (r->n == 2 * T - 1) {
        BTreeNode *s = createNode(0);
        s->child[0] = r;

        splitChild(s, 0, r);

        int i = 0;
        if (key > s->keys[0])
            i++;

        insertNonFull(s->child[i], key);
        *root = s;
    } else {
        insertNonFull(r, key);
    }
}

void display(BTreeNode *root, int level) {
    if (root == NULL)
        return;

    printf("Level %d: ", level);

    for (int i = 0; i < root->n; i++)
        printf("%d ", root->keys[i]);

    printf("\n");

    if (!root->leaf) {
        for (int i = 0; i <= root->n; i++)
            display(root->child[i], level + 1);
    }
}

void freeTree(BTreeNode *root) {
    if (root == NULL)
        return;

    if (!root->leaf) {
        for (int i = 0; i <= root->n; i++)
            freeTree(root->child[i]);
    }

    free(root);
}

int main() {
    BTreeNode *root = NULL;

    int values[] = {
        10, 20, 5, 6, 12, 30, 7, 17,
        3, 25, 35, 40, 45, 50, 60
    };

    int n = sizeof(values) / sizeof(values[0]);

    printf("B-TREE IMPLEMENTATION\n");
    printf("---------------------\n");

    printf("Inserted elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        insert(&root, values[i]);
    }

    printf("\n\nB-Tree Structure:\n");
    display(root, 0);

    printf("\nInorder Traversal: ");
    traverse(root);

    int key = 25;

    printf("\n\nSearching for %d: ", key);

    if (search(root, key) != NULL)
        printf("Key found!\n");
    else
        printf("Key not found!\n");

    freeTree(root);
    return 0;
}
