
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

Node *createNode(int key) {
    Node *n = malloc(sizeof(Node));
    if (n == NULL) exit(1);
    n->key = key;
    n->left = n->right = NULL;
    return n;
}

Node *insert(Node *root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

int search(Node *root, int key, int *cmp) {
    *cmp = 0;

    while (root != NULL) {
        (*cmp)++;

        if (root->key == key)
            return 1;

        if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }

    return 0;
}

int height(Node *root) {
    if (root == NULL)
        return -1;

    int l = height(root->left);
    int r = height(root->right);

    return 1 + (l > r ? l : r);
}

Node *minimum(Node *root) {
    while (root->left != NULL)
        root = root->left;

    return root;
}

Node *deleteNode(Node *root, int key) {
    if (root == NULL)
        return NULL;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        }

        if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        Node *temp = minimum(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}

void inorder(Node *root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void preorder(Node *root) {
    if (root) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node *root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}

void levelorder(Node *root) {
    if (!root) return;

    Node *queue[10000];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        Node *temp = queue[front++];
        printf("%d ", temp->key);

        if (temp->left)
            queue[rear++] = temp->left;

        if (temp->right)
            queue[rear++] = temp->right;
    }
}

void savePreorder(Node *root, FILE *fp) {
    if (root) {
        fprintf(fp, "%d ", root->key);
        savePreorder(root->left, fp);
        savePreorder(root->right, fp);
    }
}

void destroy(Node *root) {
    if (root) {
        destroy(root->left);
        destroy(root->right);
        free(root);
    }
}

int main() {
    Node *root = NULL;

    int keys[] = {50, 30, 70, 20, 40, 60, 80, 65};

    for (int i = 0; i < 8; i++)
        root = insert(root, keys[i]);

    printf("Inorder Traversal: ");
    inorder(root);

    printf("\nPreorder Traversal: ");
    preorder(root);

    printf("\nPostorder Traversal: ");
    postorder(root);

    printf("\nLevel Order Traversal: ");
    levelorder(root);

    printf("\nHeight: %d", height(root));

    int cmp;
    int found = search(root, 65, &cmp);

    printf("\nSearch 65: %s", found ? "Found" : "Not Found");
    printf("\nComparisons: %d", cmp);

    root = deleteNode(root, 20);
    root = deleteNode(root, 30);
    root = deleteNode(root, 50);

    printf("\nAfter Deletion: ");
    inorder(root);

    FILE *fp = fopen("tree.txt", "w");

    if (fp) {
        savePreorder(root, fp);
        fclose(fp);
        printf("\nTree saved to file.");
    }

    destroy(root);

    return 0;
}
