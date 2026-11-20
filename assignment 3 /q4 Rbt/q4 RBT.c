
#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct Node {
    int data;
    int color;
    struct Node *left, *right, *parent;
};

struct Node *root = NULL;

struct Node* createNode(int data) {
    struct Node *newNode =
        (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->color = RED;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    return newNode;
}

void leftRotate(struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rightRotate(struct Node *y) {
    struct Node *x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

void fixInsert(struct Node *z) {
    while (z != root && z->parent->color == RED) {

        struct Node *p = z->parent;
        struct Node *g = p->parent;

        if (p == g->left) {
            struct Node *u = g->right;

            if (u != NULL && u->color == RED) {
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            } else {
                if (z == p->right) {
                    z = p;
                    leftRotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            struct Node *u = g->left;

            if (u != NULL && u->color == RED) {
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            } else {
                if (z == p->left) {
                    z = p;
                    rightRotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }

    root->color = BLACK;
}

void insert(int data) {
    struct Node *z = createNode(data);
    struct Node *y = NULL;
    struct Node *x = root;

    while (x != NULL) {
        y = x;

        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == NULL)
        root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    fixInsert(z);
}

void inorder(struct Node *node) {
    if (node == NULL)
        return;

    inorder(node->left);

    printf("%d(%s) ",
           node->data,
           node->color == RED ? "R" : "B");

    inorder(node->right);
}

int findMinimum() {
    struct Node *temp = root;

    while (temp->left != NULL)
        temp = temp->left;

    return temp->data;
}

int main() {
    int processes[] = {10, 20, 30, 15, 25, 5};
    int n = 6;

    printf("Red-Black Tree Process Scheduling\n");

    for (int i = 0; i < n; i++)
        insert(processes[i]);

    printf("\nInorder Traversal:\n");
    inorder(root);

    printf("\n\nSmallest Process ID: %d\n",
           findMinimum());

    return 0;
}
