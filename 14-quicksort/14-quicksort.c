#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int comparisonCount = 0, moveCount = 0, isFirst = 0;
double totalComparisons = 0, totalMoveCount = 0;
int rounds = 0;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    moveCount += 3;
}

void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

// partition 함수
int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        comparisonCount++;
        if (array[j] < pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return i + 1;
}

// 재귀적 방법
void doQuickSort(int array[], int low, int high) {
    if (rounds % 10 == 0 && isFirst == 0) {
        for (int i = 40; i < 60; i++)
            printf("%d ", array[i]);
        printf("\n\n");
    }
    rounds++;

    if (low < high) {
        int q = partition(array, low, high);
        doQuickSort(array, low, q - 1);
        doQuickSort(array, q + 1, high);
    }
}

//반복적 방법 - 보너스
void doQuickSortIterative(int array[], int low, int high) {
    int stack[SIZE];
    int top = -1;

    stack[++top] = low;
    stack[++top] = high;

    while(top >= 0){ // 스택이 비어있지 않은 동안 반복
        high = stack[top--];
        low = stack[top--];

        int pivotIndex = partition(array, low, high);

        // // 10번에 한 번씩 출력
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++)
                printf("%d ", array[i]);
            printf("\n\n");
        }
        rounds++;

        // 왼쪽 하위 배열 스택에 push
        if (pivotIndex - 1 > low) {
            stack[++top] = low;
            stack[++top] = pivotIndex - 1;
        }

        // 오른쪽 하위 배열 스택에 push
        if (pivotIndex + 1 < high) {
            stack[++top] = pivotIndex + 1;
            stack[++top] = high;
        }
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Quick Sort Run\n");
           //doQuickSort(array, 0, SIZE - 1);
            doQuickSortIterative(array, 0, SIZE - 1);

            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        }
        else {
            //doQuickSort(array, 0, SIZE - 1);
            doQuickSortIterative(array, 0, SIZE - 1);
        }
        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}
