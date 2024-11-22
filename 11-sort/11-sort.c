#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

// 출력 함수
void print_list(int list[]) {
	for (int i = 0; i < SIZE; i++)
		printf("%d ", list[i]);
	printf("\n\n");
}

// 랜덤 배열 생성 함수
void generateRandomData(int list[]) {
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++)
		list[i] = rand() % 1000;
}

// 선택정렬
void doSelectionSort(int list[]) {
	int i, j, least, temp;
	int step = 0;

	printf("Selection Sort: \n");

	for (i = 0; i < SIZE - 1; i++) {
		least = i;
		for (j = i + 1; j < SIZE; j++) {
			if (list[j] < list[least]) {
				least = j;
			}
		}
		SWAP(list[i], list[least], temp);
		step++;

		if ((i + 1) % 20 == 10 || i == SIZE - 2) {
			printf("Step %d: ", i + 1);
			print_list(list);
		}
	}
	printf("\n");
}

// 삽입 정렬
void doInsertionSort(int list[]) {
	int totalComparisons = 0;
	int averageComparisons = 0; // 평균 비교 횟수 계산
	
	int i, j, key;

	for (int k = 0; k < 20; k++) {
		generateRandomData(list);
		int compare = 0;

		for (i = 1; i < SIZE; i++) {
			key = list[i];
			for (j = i - 1; j >= 0; j--) {
				compare++;
				if (list[j] > key) {
					list[j + 1] = list[j];
					
				}
				else break;
			}
			list[j + 1] = key;
		}
		totalComparisons += compare;
	}

	averageComparisons = totalComparisons / 20;

	printf("Insertion Sort Compare Average : %d\n", averageComparisons);
	printf("Insertion Sort Result : \n");
	print_list(list);
}

// 버블 정렬
void doBubbleSort(int list[]) {
	int i, j, temp;
	int totalSwaps = 0;
	int averageSwaps = 0; // 평균 이동 횟수 계산

	for (int k = 0; k < 20; k++) {
		generateRandomData(list);
		int swaps = 0;
		for (i = SIZE - 1; i > 0; i--) {
			for (j = 0; j < i; j++) {
				if (list[j] > list[j + 1]) {
					SWAP(list[j], list[j + 1], temp);
					swaps += 3;
				}
			}
		}
		totalSwaps += swaps;
	}

	averageSwaps = totalSwaps / 20;

	printf("Bubble Sort Move Average : %d\n", averageSwaps);
	printf("Bubble Sort Result : \n");
	print_list(list);
}

int main() {
	int randomData[SIZE];
	generateRandomData(randomData);

	doSelectionSort(randomData);
	doInsertionSort(randomData);
	doBubbleSort(randomData);

	return 0;
}
