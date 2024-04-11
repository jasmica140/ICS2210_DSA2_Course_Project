#include <algorithm>
#include "knuthShuffle.h"


void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void knuthShuffle(int* arr, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }
}

