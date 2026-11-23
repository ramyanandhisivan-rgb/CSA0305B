
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000

long long comparisons = 0;

void bubbleSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
        {
            comparisons++;
            if (a[j] > a[j + 1])
            {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
}

void insertionSort(int a[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = a[i], j = i - 1;

        while (j >= 0)
        {
            comparisons++;
            if (a[j] > key)
            {
                a[j + 1] = a[j];
                j--;
            }
            else break;
        }
        a[j + 1] = key;
    }
}

void selectionSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;

        for (int j = i + 1; j < n; j++)
        {
            comparisons++;
            if (a[j] < a[min])
                min = j;
        }

        int t = a[i];
        a[i] = a[min];
        a[min] = t;
    }
}

void merge(int a[], int l, int m, int r)
{
    int *temp = malloc((r - l + 1) * sizeof(int));
    int i = l, j = m + 1, k = 0;

    while (i <= m && j <= r)
    {
        comparisons++;
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= m) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];

    for (i = 0; i < k; i++)
        a[l + i] = temp[i];

    free(temp);
}

void mergeSort(int a[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int partition(int a[], int low, int high)
{
    int pivot = a[high], i = low - 1;

    for (int j = low; j < high; j++)
    {
        comparisons++;
        if (a[j] <= pivot)
        {
            i++;
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }

    int t = a[i + 1];
    a[i + 1] = a[high];
    a[high] = t;

    return i + 1;
}

void quickSort(int a[], int low, int high)
{
    if (low < high)
    {
        int p = partition(a, low, high);
        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

void heapify(int a[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1, r = 2 * i + 2;

    if (l < n)
    {
        comparisons++;
        if (a[l] > a[largest]) largest = l;
    }

    if (r < n)
    {
        comparisons++;
        if (a[r] > a[largest]) largest = r;
    }

    if (largest != i)
    {
        int t = a[i];
        a[i] = a[largest];
        a[largest] = t;
        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        int t = a[0];
        a[0] = a[i];
        a[i] = t;
        heapify(a, i, 0);
    }
}

int main()
{
    int n = 1000;
    int *a = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        a[i] = rand() % 10000;

    clock_t start, end;

    printf("SORTING ALGORITHM COMPARISON\n");

    start = clock();
    comparisons = 0;
    bubbleSort(a, n);
    end = clock();
    printf("Bubble Sort: Comparisons = %lld, Time = %.4f sec\n",
           comparisons, (double)(end-start)/CLOCKS_PER_SEC);

    for (int i = 0; i < n; i++) a[i] = rand() % 10000;
    start = clock();
    comparisons = 0;
    insertionSort(a, n);
    end = clock();
    printf("Insertion Sort: Comparisons = %lld, Time = %.4f sec\n",
           comparisons, (double)(end-start)/CLOCKS_PER_SEC);

    for (int i = 0; i < n; i++) a[i] = rand() % 10000;
    start = clock();
    comparisons = 0;
    selectionSort(a, n);
    end = clock();
    printf("Selection Sort: Comparisons = %lld, Time = %.4f sec\n",
           comparisons, (double)(end-start)/CLOCKS_PER_SEC);

    for (int i = 0; i < n; i++) a[i] = rand() % 10000;
    start = clock();
    comparisons = 0;
    mergeSort(a, 0, n-1);
    end = clock();
    printf("Merge Sort: Comparisons = %lld, Time = %.4f sec\n",
           comparisons, (double)(end-start)/CLOCKS_PER_SEC);

    for (int i = 0; i < n; i++) a[i] = rand() % 10000;
    start = clock();
    comparisons = 0;
    quickSort(a, 0, n-1);
    end = clock();
    printf("Quick Sort: Comparisons = %lld, Time = %.4f sec\n",
           comparisons, (double)(end-start)/CLOCKS_PER_SEC);

    for (int i = 0; i < n; i++) a[i] = rand() % 10000;
    start = clock();
    comparisons = 0;
    heapSort(a, n);
    end = clock();
    printf("Heap Sort: Comparisons = %lld, Time = %.4f sec\n",
           comparisons, (double)(end-start)/CLOCKS_PER_SEC);

    free(a);
    return 0;
}
