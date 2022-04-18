#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"heap.h"
#include"LinkedListQueue.h"

void print_all(int* data, int num) {
	for (int i = 0; i < num; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");
}
void swap(int* data, int index1, int index2) {  //swap ����. quick sort���� ���.
	int temp = data[index1];
	data[index1] = data[index2];
	data[index2] = temp;
}

void ExchangeSort(int* data, int num) {
	clock_t start = clock(); //clock�� ����Ͽ� �˰��� �ð� ����. (���� print�ϴ� �κ��� sort�� ���� �����Ƿ� ����. for loop�� ����)

	for (int i = 0; i < num; i++) {
		for (int j = i + 1; j < num; j++) {
			if (data[i] > data[j]) { //data[i] > data[j]�� ������ swap(exchange)�ϸ鼭 sorting�Ѵ�. 
				int temp = data[i];
				data[i] = data[j];
				data[j] = temp;
			}
		}
	}

	clock_t end = clock();
	printf("***Exchange Sort Result***\n");
	print_all(data, num);
	printf("Execute Time: %d(ms)", end - start);
}

void Merge(int* data, int left, int mid, int right) {
	int mleft = left;
	//���� ���������� �� subarray�� left�� right�� ���� �ε����� ����Ŵ. 
	int mright = mid + 1; //���� �����Ҷ��� subarray���� �����ؾ��ϹǷ� divide�Ǳ� ���� mid���� �̿��Ͽ� �����ִ� subarray�� �����Ѿ���.

	int* sort_data = malloc(sizeof(int) * (right + 1));
	int sindex = left;

	while (mleft <= mid && mright <= right) {
		if (data[mleft] <= data[mright]) { //�̹� ���ĵǾ� �ִ� ���
			sort_data[sindex] = data[mleft];
			mleft++;
		}
		else {
			sort_data[sindex] = data[mright];
			mright++;
		}
		sindex++; //���� sort�� �� �ֱ� ����.
	}


	if (mleft > mid) { //���� ������ �������, �����ʵ� �ڵ����� ���ĵǾ��� ���̹Ƿ� �״�� �־��ش�.
		for (int i = mright; i <= right; i++) {
			sort_data[sindex] = data[i];
			sindex++;
		}
	}
	else {
		for (int i = mleft; i <= mid; i++) {
			sort_data[sindex] = data[i];
			sindex++;
		}
	}

	//���� �迭�� �־��ֱ�
	for (int i = left; i <= right; i++) {
		data[i] = sort_data[i];
	}


}
void MergeSort(int* data, int left, int right) {
	int mid; // subarray�� ������ �κ�(index)

	if (left < right) { //data ������ ¦���� ���� left==right������, Ȧ���� ���� left < right�̴�.
						//���� left<right�϶��� �� ���� �� �ִ�. (left >= right�� �Ǹ� ���̻� ���� �� ����)
		mid = (left + right) / 2; // array�� �߰� �� ���ϱ�.

		MergeSort(data, left, mid); //���� �κ� ������
		MergeSort(data, mid + 1, right); //������ �κ� ������

		Merge(data, left, mid, right); // ���� ������ �����Ѵ�. 
	}
}
int Divide(int* data, int left, int right) {
	int pivot = data[left];
	int low = left + 1; //low�� pivot�� ������ ���� ���ʿ� �ִ� ��.
	int high = right; //high�� pivot�� ������ ���� �����ʿ� �ִ� ��. 

	while (low <= high) { //low > high�� �Ǹ� �̵��� ��ȯ�� �Ϸ�Ǿ����� ���Ѵ�.
		while (pivot >= data[low] && low <= right) //low�� pivot���� Ŭ ������ �̵�
			low++;
		while (pivot <= data[high] && high >= left + 1) //high�� pivot���� ���� �� ���� �̵�. 
			high--;
		if (low <= high)  //low�� high�� �������� �ʾ����� low�� high�� index������ �ִ� �� ��ġ �ٲ�. 
			swap(data, low, high);
	}
	//���� while�� �������°��. ��, low�� high�� ������ ���
	swap(data, left, high); //pivot�� high �ٲ۴�. 
	return high; //high���� pivot�� ����ִ�. ��, ���⼭�� pivot�� ���� �Ϸ� ����. 
}
void QuickSort(int* data, int left, int right) {
	if (left <= right) {
		int pivot = Divide(data, left, right); //Divide()�� ���� high�� ��ȯ�Ǵµ�, �� index�� pivot�� ���ĵ� ���̴�. 
		QuickSort(data, left, pivot - 1);  //���� pivot�� ���ĵǾ����Ƿ�, pivot-1�� pivot+1�� �������Ѵ�. 
		QuickSort(data, pivot + 1, right);
	}
}

void HeapSort(int* data, int num) {
	clock_t start = clock();
	Heap heap;
	HeapInit(&heap, data, num + 1); //heap �ʱ�ȭ
	for (int i = 0; i < num; i++) {
		HeapInsert(&heap, data[i]);   //���� ������ �ϳ��� insert
	}
	int* result = malloc(sizeof(int) * heap.heapSize);  //��� ����. increasing order�� �ϱ� ����
	int size = heap.heapSize - 1;

	printf("\n\n");
	while (HeapIsEmpty(&heap) != 1) {   //������ root ��� ��� �����ϸ鼭 increasing order�� ����
		result[size] = HeapDelete(&heap);
		size--;
	}
	clock_t end = clock();
	for (int i = 0; i < num; i++) { //���
		printf("%d ", result[i]);
	}
	printf("\n Execute Time: %d(ms)", end - start);

}

//10������ ����Ͽ� radixSort ����!
void RadixSort(int* data, int num, int maxlength) {
	Queue buckets[10]; //10������ �̿��ؼ� ������ ���̹Ƿ� bucket�� 10���� �ʿ��ϴ�. 
	int div = 1;
	int b;
	int d;
	int radix; //���
	for (int b = 0; b < 10; b++) {
		QueueInit(&buckets[b]);
	}

	for (int i = 0; i < maxlength; i++) { //maxlength�� data�߿��� �ִ� �ڸ��� �ǹ�. ��, �ִ��ڸ��� ���� �ڸ��� ���� ���� 0���� �����Ͽ� ����.
		for (d = 0; d < num; d++) {

			radix = (data[d] / div) % 10; //div�� 1�̸� �����ڸ� ����, div�� 10�̸� 10�� �ڸ� ����... 

			Enqueue(&buckets[radix], data[d]); //�ڽſ��� �´� ����� buckets�� data ����. 
		}

		//��Ŷ �� ��ŭ �ݺ�
		for (b = 0, d = 0; b < 10; b++) {
			while (!QueueIsEmpty(&buckets[b])) {
				data[d++] = Dequeue(&buckets[b]); // ��Ŷ�� ����Ǿ��ִ� �� ������� ������ data array�� �ٽ� ����.
			}
		}

		div *= 10;  //�ڸ��� ����. 
	}
}