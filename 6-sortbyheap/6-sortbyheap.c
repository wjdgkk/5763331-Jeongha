#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 힙 재정렬하는 함수
void resortHeap(int inputData[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // 왼쪽 자식이 더 클 때
    if (left < n && inputData[left] > inputData[largest])
        largest = left;

    // 오른쪽 자식이 더 클 때
    if (right < n && inputData[right] > inputData[largest])
        largest = right;

    // 루트가 가장 큰 값이 아닐 경우 교환하고 재귀적으로 힙 재정렬
    if (largest != i) {
        swap(&inputData[i], &inputData[largest]);
        resortHeap(inputData, n, largest);
    }
}

// 값 추가하고 출력하는 함수
void insertHeap(int inputData[], int n) {
    int i = n - 1;  
    int parent = (i - 1) / 2;  

    // 부모 노드보다 클 경우 두 요소 교환
    while (i > 0 && inputData[i] > inputData[parent]) {
        swap(&inputData[i], &inputData[parent]);
        i = parent;
        parent = (i - 1) / 2;
    }

    // 힙 출력
    for (int j = 0; j < n; j++) {
        printf("%d ", inputData[j]);
    }
    printf("\n");
}

// 배열을 최대 힙으로 변환
void BuildMaxHeap(int inputData[], int n) {
    for (int i = 0; i < n; i++) {
        insertHeap(inputData, i + 1);
    }
}

void BuildMaxHeapAndSort(int inputData[], int n) {
    // max heap 생성하는 함수
    BuildMaxHeap(inputData, n);

    // 하나씩 힙에서 루트(최대값)를 제거하고 정렬
    for (int i = n - 1; i > 0; i--) {
        swap(&inputData[0], &inputData[i]); 
        resortHeap(inputData, i, 0);  

        // 힙 재정렬 후 상태 출력
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

int main() {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]);
    // 힙 정렬 실행
    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);

    // 정렬된 결과 출력
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");
    return 0;
}
