
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKETS 7

typedef struct Member
{
    char id[12];
    char name[20];
    struct Member *next;
} Member;

Member *table[BUCKETS];

unsigned hash(const char *s)
{
    unsigned h = 0;

    while (*s)
        h = h * 31 + (unsigned char)*s++;

    return h % BUCKETS;
}

void put(const char *id, const char *name)
{
    Member *newNode = (Member *)malloc(sizeof(Member));

    if (newNode == NULL)
        return;

    strcpy(newNode->id, id);
    strcpy(newNode->name, name);

    unsigned index = hash(id);

    newNode->next = table[index];
    table[index] = newNode;
}

const char *get(const char *id, int *probes)
{
    *probes = 0;

    unsigned index = hash(id);
    Member *current = table[index];

    while (current != NULL)
    {
        (*probes)++;

        if (strcmp(current->id, id) == 0)
            return current->name;

        current = current->next;
    }

    return NULL;
}

int main()
{
    const char *ids[] = {
        "CSE1043", "ECE2210", "MEC3307",
        "CSE1044", "BME4120", "CIV5009"
    };

    const char *names[] = {
        "Kavya", "Arjun", "Fathima",
        "Rahul", "Deepa", "Manoj"
    };

    for (int i = 0; i < 6; i++)
        put(ids[i], names[i]);

    for (int b = 0; b < BUCKETS; b++)
    {
        int len = 0;

        for (Member *m = table[b]; m; m = m->next)
            len++;

        printf("%d", len);
    }

    int p;

    const char *who = get("CSE1044", &p);
    printf("\nCSE1044 -> %s (%d probes)\n",
           who ? who : "not found", p);

    who = get("CSE9999", &p);
    printf("CSE9999 -> %s (%d probes)\n",
           who ? who : "not found", p);

    for (int b = 0; b < BUCKETS; b++)
    {
        while (table[b])
        {
            Member *n = table[b]->next;
            free(table[b]);
            table[b] = n;
        }
    }

    return 0;
}
