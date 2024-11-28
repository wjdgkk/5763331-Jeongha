#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define SIZE 100

int comparisonCount = 0, moveCount = 0, isFirst = 0;
double totalComparisons = 0, totalMoves = 0;
int rounds = 0;
int sorted[SIZE];

void generateRandomArray(int list[]) {
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000;
    }
    Sleep(1000);
}

// 병합 함수
void merge(int list[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left, l;

    while (i <= mid && j <= right) {
        comparisonCount++;
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++];
        }
        else {
            sorted[k++] = list[j++];
        }
        moveCount++;
    }

    while (i <= mid) {
        sorted[k++] = list[i++];
        moveCount++;
    }

    while (j <= right) {
        sorted[k++] = list[j++];
        moveCount++;
    }

    for (l = left; l <= right; l++) {
        list[l] = sorted[l];
        moveCount++;
    }

    rounds++;

    // 10번에 한 번씩 출력
    if (rounds % 10 == 0 && isFirst == 0) {
        for (int i = 0; i < 10; i++)
            printf("%3d ", list[i]);
        printf("| ");
        for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) 
            printf("%3d ", list[i]);
        printf("\n\n");
        
    }
}

// 재귀적 방법
void doMergeSort(int list[], int left, int right) {
    int mid;

    if (left < right) {
        mid = (left + right) / 2;
        doMergeSort(list, left, mid);
        doMergeSort(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}

// 반복적 방법 - 보너스
void doMergeSortIterative(int list[], int size) {
    for (int width = 1; width <= size - 1; width *= 2) {
        for (int leftStart = 0; leftStart < size - 1; leftStart += 2 * width) {
            int mid = leftStart + width - 1;

            int rightEnd = (leftStart + 2 * width - 1 < size - 1) ?
                (leftStart + 2 * width - 1) : (size - 1);

            merge(list, leftStart, mid, rightEnd);
        }
    }   
}

// 배열 출력 함수
void printArray(int arr[], int size) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int array[SIZE];


    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Merge Sort Run\n");
            //doMergeSort(array, 0, SIZE - 1);
            doMergeSortIterative(array, SIZE);

            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        }
        else {
            //doMergeSort(array, 0, SIZE - 1);
            doMergeSortIterative(array, SIZE);
        }

        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
