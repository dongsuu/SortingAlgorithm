#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"heap.h"
#include"LinkedListQueue.h"
#include"sorting.h"


int main() {
	int* data;
	int num;
	int choice;
	printf("Data의 개수를 입력하세요:");
	scanf_s("%d", &num);				//data개수 입력
	data = malloc(sizeof(int) * num);	//data개수에 따라 data 저장할 공간 할당

	//data random한 수로 할당. 모든 data는 integer로 가정.
	srand(time(NULL));
	for (int i = 0; i < num; i++)
		data[i] = rand() % 100000;  //랜덤 수는 0~1000000으로 정함.

	printf("\n***정렬전***\n");
	print_all(data, num);
	printf("\n\n");

		printf("Exchange sort(1), Mergesort(2), Quicksort(3), Heapsort(4), Radixsort(5) : ");
		scanf_s("%d", &choice);
		if (choice == 1)
			ExchangeSort(data, num);
		else if (choice == 2) {
			clock_t start = clock();
			MergeSort(data, 0, num - 1);
			clock_t end = clock();
			printf("***Merge Sort Result***\n");
			print_all(data, num);
			printf("\n Execute Time: %d(ms)", end - start);
		}
		else if (choice == 3) {
			clock_t start = clock();
			QuickSort(data, 0, num - 1);
			clock_t end = clock();
			printf("***Quick Sort Result***\n");
			print_all(data, num);
			printf("\n Execute Time: %d(ms)", end - start);
		}
		else if (choice == 4) {
			printf("\n***Heap Sort Result***");
			HeapSort(data, num);
		}
		else if (choice == 5) {
			printf("\n***Radix Sort Result***\n");
			clock_t start = clock();
			RadixSort(data, num, 2);
			clock_t end = clock();
			print_all(data, num);
			printf("\n Execute Time: %d(ms)", end - start);
		}

	return 0;
}