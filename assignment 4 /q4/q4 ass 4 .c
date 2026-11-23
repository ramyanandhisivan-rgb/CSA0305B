
#include <stdio.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void quick(int a[], int lo, int hi)
{
    if (lo >= hi)
        return;

    int p = a[hi];
    int i = lo - 1;

    for (int j = lo; j < hi; j++)
    {
        if (a[j] <= p)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[hi]);

    quick(a, lo, i);
    quick(a, i + 2, hi);
}

int main()
{
    int a[] = {7, 2, 9, 4, 3, 8, 5};
    int n = 7;

    quick(a, 0, n - 1);

    printf("Sorted array: ");

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    return 0;
}
