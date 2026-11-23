
#include <stdio.h>

#define MAX 32

typedef struct
{
    int severity;
    int patient;
} Case;

Case heap[MAX];
int size = 0;

void swap(Case *a, Case *b)
{
    Case t = *a;
    *a = *b;
    *b = t;
}

void push(int severity, int patient)
{
    if (size == MAX)
        return;

    heap[size] = (Case){severity, patient};

    int i = size++;

    // Sift up
    while (i > 0 && heap[(i - 1) / 2].severity < heap[i].severity)
    {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Case pop(void)
{
    Case top = heap[0];

    heap[0] = heap[--size];

    int i = 0;

    // Sift down
    while (1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < size &&
            heap[left].severity > heap[largest].severity)
            largest = left;

        if (right < size &&
            heap[right].severity > heap[largest].severity)
            largest = right;

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);
        i = largest;
    }

    return top;
}

int main()
{
    int sev[] = {3, 9, 5, 7, 1, 8};

    for (int p = 0; p < 6; p++)
        push(sev[p], 101 + p);

    while (size > 0)
    {
        Case c = pop();
        printf("P%d(%d) ", c.patient, c.severity);
    }

    printf("\n");

    return 0;
}
