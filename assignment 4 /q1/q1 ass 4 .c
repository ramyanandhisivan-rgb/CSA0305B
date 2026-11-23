
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100003
#define N 100000

unsigned int poorHash(const char *reg)
{
    return (reg[0] + reg[1]) % SIZE;
}

unsigned int goodHash(const char *reg)
{
    unsigned int hash = 0;

    while (*reg)
    {
        hash = hash * 31 + (unsigned char)*reg;
        reg++;
    }

    return hash % SIZE;
}

void generateRegistration(char *reg, int n)
{
    sprintf(reg, "TN%02dAB%04d", (n % 100) + 1, n);
}

void measureHash(unsigned int (*hashFunction)(const char *), char *name)
{
    int *table = calloc(SIZE, sizeof(int));
    int maxChain = 0;

    for (int i = 0; i < N; i++)
    {
        char reg[20];
        generateRegistration(reg, i);

        unsigned int index = hashFunction(reg);
        table[index]++;
    }

    int total = 0;
    int used = 0;

    for (int i = 0; i < SIZE; i++)
    {
        if (table[i] > 0)
        {
            total += table[i];
            used++;
        }

        if (table[i] > maxChain)
            maxChain = table[i];
    }

    printf("\n%s\n", name);
    printf("Maximum chain length: %d\n", maxChain);
    printf("Average chain length: %.2f\n",
           used ? (float)total / used : 0);

    free(table);
}

int main()
{
    measureHash(poorHash, "Poor Hash Function");
    measureHash(goodHash, "Improved Polynomial Hash Function");

    return 0;
}
