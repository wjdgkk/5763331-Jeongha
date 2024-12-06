#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 랜덤 배열 생성
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 10000;
    }
}

// 파티션 함수
int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return i + 1;
}

// 퀵 정렬
void QuickSort(int array[], int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        QuickSort(array, low, pi - 1);
        QuickSort(array, pi + 1, high);
    }
}

// 이진 탐색
int binarySearch(int array[], int target) {
    int low = 0, high = SIZE - 1;
    int comparisons = 0;

    while (low <= high) {
        int mid = (low + high) / 2;

        comparisons++;
        if (array[mid] == target)
            return comparisons;

        //comparisons++;
        if (array[mid] < target)
            low = mid + 1;

        else
            high = mid - 1;
    }
    return comparisons;
}

// 이진 탐색 평균 비교
float getAverageBinarySearchCompareCount(int array[]) {
    int totalComparisons = 0;

    for (int i = 0; i < SIZE; i++) {
        int target = array[rand() % SIZE];
        totalComparisons += binarySearch(array, target);
    }

    return (float)totalComparisons / SIZE;
}

// 보간 탐색
int interpolationSearch(int array[], int target) {
    int low = 0, high = SIZE - 1;
    int compareCount = 0;

    while (low <= high && target >= array[low] && target <= array[high]) {

        // 위치 계산
        int pos = low + ((target - array[low]) * (high - low)) / (array[high] - array[low]);

        compareCount++;
        if (array[pos] == target)
            return compareCount;

        compareCount++;
        if (array[pos] < target)
            low = pos + 1;
  
        else
            high = pos - 1;
    }
    return compareCount;
}

// 보간 탐색 평균 비교
float getAverageInterpolationSearchCompareCount(int array[]) {
    int totalComparisons = 0;

    for (int i = 0; i < SIZE; i++) {
        int target = array[rand() % SIZE];
        totalComparisons += interpolationSearch(array, target);
    }

    return (float)totalComparisons / SIZE;
}

// 배열 출력
void printArray(int* array) {
    printf("Array Sorting Result:\n");

    for (int i = 0; i < 20; i++)
        printf("%4d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%4d ", array[i]);
    printf("\n\n");
}

// main 함수
int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];
    generateRandomArray(array);

    QuickSort(array, 0, SIZE - 1);
    printArray(array);

    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));

    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchCompareCount(array));

    return 0;
}
