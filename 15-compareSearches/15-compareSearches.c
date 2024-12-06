#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

int compareCount = 0; 

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 랜덤 배열 생성
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

// 파티션 함수
int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        compareCount++; 
        if (array[j] < pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return i + 1;
}

// 퀵정렬 함수
void quickSort(int array[], int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

// 퀵 정렬 비교 횟수 계산
void getQuickSortCompareCount(int array[]) {
    compareCount = 0; 
    quickSort(array, 0, SIZE - 1);
}

// 이진 탐색
int binarySearch(int array[], int target) {
    int left = 0, right = SIZE - 1;
    int compareCount = 0;
    int mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        compareCount++;
        if (array[mid] == target) {
            return compareCount;
        }
        if (array[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return compareCount;
}

// 이진 탐색 평균 비교
float getAverageBinarySearchCompareCount(int array[]) {
    int totalComparisons = 0;
    int key;
    for (int i = 0; i < 100; i++) {
        key = rand() % 1000;       
        int target = array[key];
        totalComparisons += binarySearch(array, target);
    }
    return totalComparisons / 100.0;
}

// 선형 탐색
int linearSearch(int array[], int target) {
    int comparisons = 0;
    for (int i = 0; i < SIZE; i++) {
        comparisons++;
        if (array[i] == target) {
            return comparisons;
        }
    }
    return comparisons;
}

// 선형 탐색 평균 비교
float getAverageLinearSearchCompareCount(int array[]) {
    int totalComparisons = 0;
    int key;
    for (int i = 0; i < 100; i++) {
        key = rand() % 1000;
        int target = array[key];
        totalComparisons += linearSearch(array, target);
    }
    return totalComparisons / 100.0;
}

// 배열 출력 함수
void printArray(int* array) {
    printf("Array Sorting Result:\n");

    for (int i = 0; i < 20; i++) {
        printf("%3d ", array[i]);
    }
    printf("\n");
    for (int j = SIZE - 20; j < SIZE; j++) {
        printf("%3d ", array[j]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    srand(time(NULL)); 
    int array[SIZE];

    generateRandomArray(array);

    //평균값을 반환받기 위한 조치
    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array));

    //compareCount가 global variable이므로, 다음과 같이 구현
    //array에 대해서 직접 정렬하면 된다.
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);

    //정렬된 Array에 대해서 Binary Search 100회 수행 및 평균 비교횟수 출력
    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array));

    printArray(array);
    return 0;
}
