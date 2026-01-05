#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

void *monkey_sort(void *arr);
void quicksort(int *arr, int low, int high);

int main() {
   int arr[] = {3, 6, 8, 10, 1, 2, 1};
   int arr_len = sizeof(arr) / sizeof(arr[0]);

   clock_t start = clock();
   pthread_t t1, t2;
   int arr1[arr_len], arr2[arr_len];

   for (int i = 0; i < arr_len; i++) {
       arr1[i] = arr2[i] = arr[i];
   }

   pthread_create(&t1, NULL, monkey_sort, (void *)arr1);
   pthread_create(&t2, NULL, monkey_sort, (void *)arr2);

   pthread_join(t1, NULL);
   pthread_join(t2, NULL);

   quicksort(arr, 0, arr_len - 1);

   clock_t end = clock();
   double time_used = (double)(end - start) / CLOCKS_PER_SEC;

   printf("Monkey Sort Time Used: %.2lf seconds\n", time_used);

   start = clock();
   quicksort(arr, 0, arr_len - 1);
   end = clock();
   time_used = (double)(end - start) / CLOCKS_PER_SEC;

   printf("Quicksort Time Used: %.2lf seconds\n", time_used);

   return 0;
}

void *monkey_sort(void *arr) {
   int *a = (int *)arr;
   int n = sizeof(arr) / sizeof(arr[0]);

   for (int i = 0; i < n - 1; i++) {
       for (int j = 0; j < n - 1 - i; j++) {
           if (a[j] > a[j + 1]) {
               int temp = a[j];
               a[j] = a[j + 1];
               a[j + 1] = temp;
           }
       }
   }

   return NULL;
}

void quicksort(int *arr, int low, int high) {
   if (low < high) {
       int pivot_index = partition(arr, low, high);
       quicksort(arr, low, pivot_index - 1);
       quicksort(arr, pivot_index + 1, high);
   }
}

int partition(int *arr, int low, int high) {
   int pivot = arr[high];
   int i = low - 1;

   for (int j = low; j < high; j++) {
       if (arr[j] <= pivot) {
           i++;
           swap(arr[i], arr[j]);
       }
   }

   swap(arr[i + 1], arr[high]);
   return i + 1;
}

void swap(int &a, int &b) {
   int temp = a;
   a = b;
   b = temp;
}