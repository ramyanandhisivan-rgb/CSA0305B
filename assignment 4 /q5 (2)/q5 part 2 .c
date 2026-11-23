
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000000

void merge(int a[], int l, int m, int r)
{
    int *temp = malloc((r-l+1) * sizeof(int));

    int i = l, j = m+1, k = 0;

    while (i <= m && j <= r)
    {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= m) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];

    for (i = 0; i < k; i++)
        a[l+i] = temp[i];

    free(temp);
}

void mergeSort(int a[], int l, int r, int depth)
{
    if (l >= r) return;

    int m = (l+r)/2;

    if (depth > 0)
    {
        #pragma omp task shared(a) firstprivate(l,m,depth)
        mergeSort(a, l, m, depth-1);

        #pragma omp task shared(a) firstprivate(m,r,depth)
        mergeSort(a, m+1, r, depth-1);

        #pragma omp taskwait
    }
    else
    {
        mergeSort(a, l, m, 0);
        mergeSort(a, m+1, r, 0);
    }

    merge(a, l, m, r);
}

int main()
{
    int *a = malloc(N * sizeof(int));

    if (a == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < N; i++)
        a[i] = rand() % 1000000;

    int threads[] = {1, 2, 4, 8};

    for (int t = 0; t < 4; t++)
    {
        omp_set_num_threads(threads[t]);

        double start = omp_get_wtime();

        #pragma omp parallel
        {
            #pragma omp single
            mergeSort(a, 0, N-1, 4);
        }

        double end = omp_get_wtime();

        printf("Threads: %d\n", threads[t]);
        printf("Execution Time: %.4f seconds\n\n", end-start);
    }

    printf("Sorting completed successfully\n");

    free(a);
    return 0;
}
