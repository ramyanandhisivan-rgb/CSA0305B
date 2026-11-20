
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Trie {
    struct Trie *child[26];
    int words;
    int end;
} Trie;

Trie *node(void) {
    return calloc(1, sizeof(Trie));
}

void insert(Trie *t, const char *w) {
    for (int i = 0; w[i] != '\0'; i++) {
        int index = w[i] - 'a';

        if (t->child[index] == NULL)
            t->child[index] = node();

        t = t->child[index];
        t->words++;
    }

    t->end = 1;
}

int count_prefix(const Trie *t, const char *p) {
    for (int i = 0; p[i] != '\0'; i++) {
        int index = p[i] - 'a';

        if (t->child[index] == NULL)
            return 0;

        t = t->child[index];
    }

    return t->words;
}

int search(Trie *t, const char *w) {
    for (int i = 0; w[i] != '\0'; i++) {
        int index = w[i] - 'a';

        if (!t->child[index])
            return 0;

        t = t->child[index];
    }

    return t->end;
}

void autocomplete(Trie *t, char *buffer, int level) {
    if (t->end) {
        buffer[level] = '\0';
        printf("%s ", buffer);
    }

    for (int i = 0; i < 26; i++) {
        if (t->child[i]) {
            buffer[level] = 'a' + i;
            autocomplete(t->child[i], buffer, level + 1);
        }
    }
}

void destroy(Trie *t) {
    if (!t) return;

    for (int i = 0; i < 26; i++)
        destroy(t->child[i]);

    free(t);
}

int main(void) {
    const char *contacts[] = {
        "anand", "anitha", "anu",
        "arun", "bala", "anusuya"
    };

    Trie *root = node();

    for (int i = 0; i < 6; i++)
        insert(root, contacts[i]);

    const char *typed[] = {"a", "an", "anu", "b", "z"};

    printf("Prefix Counts:\n");

    for (int i = 0; i < 5; i++)
        printf("%s:%d ", typed[i],
               count_prefix(root, typed[i]));

    printf("\n\nSearch anand: %s",
           search(root, "anand") ? "Found" : "Not Found");

    char buffer[100];

    printf("\nAutocomplete for 'an': ");
    Trie *temp = root;

    temp = temp->child['a' - 'a'];
    temp = temp->child['n' - 'a'];

    if (temp)
        autocomplete(temp, buffer, 0);

    printf("\n");

    destroy(root);
    return 0;
}
