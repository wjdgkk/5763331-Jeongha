#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100

void print_list(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}

void generateRandomNumbers(int list[]) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        list[i] = rand() % 1000;
    }
}

void doShellSort(int arr[], int div, int* comparisonCount, int* moveCount) {
    int n[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++) {
        n[i] = arr[i];
    }

    for (int gap = ARRAY_SIZE / div; gap > 0; gap /= div) {
        printf("Sorting With Gap = %d : \n", gap);
        for (int i = gap; i < ARRAY_SIZE; i++) {
            int temp = n[i];
            int j;
            for (j = i; j >= gap && n[j - gap] > temp; j -= gap) {
                n[j] = n[j - gap];
            }
            n[j] = temp;
        }
        print_list(n, 20);
        printf("...\n\n");
    }
    printf("Sorted shellArray (gap = %d)\n", div);
    print_list(n, ARRAY_SIZE);
    printf("\n\n");


    // 평균 횟수 출력
    int totalComparisons = 0;
    int totalMoves = 0;

    for (int k = 0; k < 20; k++) {
        int tempArray[ARRAY_SIZE];
        generateRandomNumbers(tempArray);
        *comparisonCount = 0;
        *moveCount = 0;

        for (int gap = ARRAY_SIZE / div; gap > 0; gap /= div) {
            for (int i = gap; i < ARRAY_SIZE; i++) {
                int temp = tempArray[i];
                
                (*moveCount)++;
                int j;
                for (j = i; j >= gap && tempArray[j - gap] > temp; j -= gap) {
                    tempArray[j] = tempArray[j - gap];
                    (*comparisonCount)++;
                    (*moveCount)++;
                }
                if (j >= gap) {
                    (*comparisonCount)++;
                }
                if (j != i) {
                    tempArray[j] = temp;
                    (*moveCount)++;
                }
            }
        }
        totalComparisons += *comparisonCount;
        totalMoves += *moveCount;
    }

    *comparisonCount = totalComparisons / 20;
    *moveCount = totalMoves / 20;
}

void doInsertionSort(int arr[], int* comparisonCount, int* moveCount) {
    int tArray[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++) {
        tArray[i] = arr[i];
    }

    for (int i = 1; i < ARRAY_SIZE; i++) {
        int temp = tArray[i];
        int j;
        for (j = i - 1; j >= 0 && tArray[j] > temp; j--) {
            tArray[j + 1] = tArray[j];
        }

        tArray[j + 1] = temp;
    }
    print_list(tArray, ARRAY_SIZE);
    printf("\n\n");
    

    // 평균 횟수 출력
    int totalComparisons = 0;
    int totalMoves = 0;

    for (int k = 0; k < 20; k++) {
        int tempArray[ARRAY_SIZE];
        generateRandomNumbers(tempArray);
        *comparisonCount = 0;
        *moveCount = 0;

        for (int i = 1; i < ARRAY_SIZE; i++) {
            int temp = tempArray[i];
            (*moveCount)++;
            int j;
            for (j = i - 1; j >= 0 && tempArray[j] > temp; j--) {
                tempArray[j + 1] = tempArray[j];
                (*comparisonCount)++;
                (*moveCount)++;
            }
            tempArray[j + 1] = temp;
            (*moveCount)++;
        }
        totalComparisons += *comparisonCount;
        totalMoves += *moveCount;
    }

    *comparisonCount = totalComparisons / 20;
    *moveCount = totalMoves / 20;
}

int main() {
    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    generateRandomNumbers(array);

    // Shell Sort
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons : %d, Moves : %d\n\n", comparisonCount, moveCount);

    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons : %d, Moves : %d\n\n", comparisonCount, moveCount);

    // Insertion Sort - 보너스
    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons : %d, Moves : %d\n", comparisonCount, moveCount);

    return 0;
}
