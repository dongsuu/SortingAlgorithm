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
void swap(int* data, int index1, int index2) {  //swap 연산. quick sort에서 사용.
	int temp = data[index1];
	data[index1] = data[index2];
	data[index2] = temp;
}

void ExchangeSort(int* data, int num) {
	clock_t start = clock(); //clock을 사용하여 알고리즘 시간 측정. (밑의 print하는 부분은 sort와 관계 없으므로 제외. for loop만 포함)

	for (int i = 0; i < num; i++) {
		for (int j = i + 1; j < num; j++) {
			if (data[i] > data[j]) { //data[i] > data[j]가 있으면 swap(exchange)하면서 sorting한다. 
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
	//분할 마지막에는 각 subarray의 left와 right가 같은 인덱스를 가리킴. 
	int mright = mid + 1; //따라서 병합할때는 subarray끼리 병합해야하므로 divide되기 전의 mid값을 이용하여 옆에있는 subarray를 가리켜야함.

	int* sort_data = malloc(sizeof(int) * (right + 1));
	int sindex = left;

	while (mleft <= mid && mright <= right) {
		if (data[mleft] <= data[mright]) { //이미 정렬되어 있는 경우
			sort_data[sindex] = data[mleft];
			mleft++;
		}
		else {
			sort_data[sindex] = data[mright];
			mright++;
		}
		sindex++; //다음 sort된 값 넣기 위함.
	}


	if (mleft > mid) { //왼쪽 정렬이 끝난경우, 오른쪽도 자동으로 정렬되었을 것이므로 그대로 넣어준다.
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

	//원래 배열에 넣어주기
	for (int i = left; i <= right; i++) {
		data[i] = sort_data[i];
	}


}
void MergeSort(int* data, int left, int right) {
	int mid; // subarray로 나누는 부분(index)

	if (left < right) { //data 개수가 짝수일 때는 left==right이지만, 홀수일 때는 left < right이다.
						//따라서 left<right일때만 더 나눌 수 있다. (left >= right가 되면 더이상 나눌 수 없음)
		mid = (left + right) / 2; // array의 중간 값 구하기.

		MergeSort(data, left, mid); //왼쪽 부분 나누기
		MergeSort(data, mid + 1, right); //오른쪽 부분 나누기

		Merge(data, left, mid, right); // 분할 끝나면 병합한다. 
	}
}
int Divide(int* data, int left, int right) {
	int pivot = data[left];
	int low = left + 1; //low는 pivot을 제외한 가장 왼쪽에 있는 값.
	int high = right; //high는 pivot을 제외한 가장 오른쪽에 있는 값. 

	while (low <= high) { //low > high가 되면 이동과 교환이 완료되었음을 뜻한다.
		while (pivot >= data[low] && low <= right) //low는 pivot보다 클 때까지 이동
			low++;
		while (pivot <= data[high] && high >= left + 1) //high는 pivot보다 작을 때 까지 이동. 
			high--;
		if (low <= high)  //low와 high가 교차되지 않았으면 low와 high의 index가지고 있는 값 위치 바꿈. 
			swap(data, low, high);
	}
	//위의 while문 빠져나온경우. 즉, low와 high가 교차된 경우
	swap(data, left, high); //pivot과 high 바꾼다. 
	return high; //high에는 pivot이 들어있다. 즉, 여기서의 pivot은 정렬 완료 상태. 
}
void QuickSort(int* data, int left, int right) {
	if (left <= right) {
		int pivot = Divide(data, left, right); //Divide()에 의해 high가 반환되는데, 이 index가 pivot의 정렬된 값이다. 
		QuickSort(data, left, pivot - 1);  //따라서 pivot은 정렬되었으므로, pivot-1과 pivot+1로 나눠야한다. 
		QuickSort(data, pivot + 1, right);
	}
}

void HeapSort(int* data, int num) {
	clock_t start = clock();
	Heap heap;
	HeapInit(&heap, data, num + 1); //heap 초기화
	for (int i = 0; i < num; i++) {
		HeapInsert(&heap, data[i]);   //힙에 데이터 하나씩 insert
	}
	int* result = malloc(sizeof(int) * heap.heapSize);  //결과 저장. increasing order로 하기 위함
	int size = heap.heapSize - 1;

	printf("\n\n");
	while (HeapIsEmpty(&heap) != 1) {   //힙에서 root 노드 계속 삭제하면서 increasing order로 저장
		result[size] = HeapDelete(&heap);
		size--;
	}
	clock_t end = clock();
	for (int i = 0; i < num; i++) { //출력
		printf("%d ", result[i]);
	}
	printf("\n Execute Time: %d(ms)", end - start);

}

//10진수를 고려하여 radixSort 구현!
void RadixSort(int* data, int num, int maxlength) {
	Queue buckets[10]; //10진수를 이용해서 구현할 것이므로 bucket은 10개가 필요하다. 
	int div = 1;
	int b;
	int d;
	int radix; //기수
	for (int b = 0; b < 10; b++) {
		QueueInit(&buckets[b]);
	}

	for (int i = 0; i < maxlength; i++) { //maxlength는 data중에서 최대 자릿수 의미. 즉, 최대자리수 보다 자리수 작은 곳은 0으로 생각하여 진행.
		for (d = 0; d < num; d++) {

			radix = (data[d] / div) % 10; //div가 1이면 일의자리 추출, div가 10이면 10의 자리 추출... 

			Enqueue(&buckets[radix], data[d]); //자신에게 맞는 기수의 buckets에 data 저장. 
		}

		//버킷 수 만큼 반복
		for (b = 0, d = 0; b < 10; b++) {
			while (!QueueIsEmpty(&buckets[b])) {
				data[d++] = Dequeue(&buckets[b]); // 버킷에 저장되어있던 것 순서대로 꺼내서 data array에 다시 저장.
			}
		}

		div *= 10;  //자릿수 증가. 
	}
}