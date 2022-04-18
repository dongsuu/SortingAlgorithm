#include"heap.h"

int HeapIsEmpty(Heap* h) { //힙이 비어있는지 확인
	if (h->heapSize  == 0)
		return 1;
	else
		return 0;
}

void HeapInit(Heap * h, int *data, int num) { //힙의 초기화
	h->heapSize = 0;
	h->heapArray = malloc(sizeof(Heap) * num+1);
	
}
int getParent(int index) { //parent node index 반환
	return index / 2;
}
int getLeftChild(int index) { //left child node index 반환
	return index * 2;
}
int getRightChild(int index) { //right child node index 반환
	return index * 2 + 1;
}

int getBiggerChild(Heap* h, int index) {
	if (getLeftChild(index) > h->heapSize) // 자식 노드가 없으면 왼쪽 자식 노드의 index는 heapsize보다 크게된다.
		return 0;

	else if (getLeftChild(index) == h->heapSize) //왼쪽 자식 노드만 있으면 heapSize와 leftchild의 자식 노드 index 동일하다.
		return getLeftChild(index);
	else {
		if (h->heapArray[getLeftChild(index)] > h->heapArray[getRightChild(index)]) // 왼쪽 자식이 더 크면 왼쪽 자식 return
			return getLeftChild(index);
		else { //오른쪽 자식이 더 크면 오른쪽 자식 return
			return getRightChild(index);
		}
	}
}

void HeapInsert(Heap* h, int data) {
	int index = h->heapSize + 1; //데이터가 삽입될 위치는 현 데이터 개수 +1
	
	while (index != 1) {
		if (h->heapArray[getParent(index)] < data) { //새 노드의 값이 더 크다면 
			h->heapArray[index] = h->heapArray[getParent(index)]; // 새로 들어갈 자리에 원래 부모가 들어간다.
			index = getParent(index); // 새 노드 들어가기 위해 index값 갱신
		}
		else //새 노드 값이 더 작으면 그냥 원래 들어가려던 위치에 그대로 들어가면 된다. 
			break;
	}
	h->heapArray[index] = data; //새 노드 배열에 저장. 
	h->heapSize += 1; //size 1만큼 증가
}

int HeapDelete(Heap* h) {
	int temp = h->heapArray[1]; //root노드가 삭제 대상임. 삭제할 데이터 임시 저장
	int lastTemp = h->heapArray[h->heapSize]; //마지막 위치에 저장되어 있는 값 임시 저장
	int parentIndex = 1;
	int childIndex;
	
	while (childIndex = getBiggerChild(h, parentIndex)) { //2개의 자식 노드에서 큰 값부터 반복 시작
		if (lastTemp >= h->heapArray[childIndex]) //마지막 위치의 값이 제거 대상의 자식 노드의 큰 값 보다 크면 break.
			break; //이때 heapArray[parentIndex]에 마지막 위치의 노드 값 들어가야한다. 

		//비교 대상 노드 한 레벨 올린다. 
		h->heapArray[parentIndex] = h->heapArray[childIndex];
		parentIndex = childIndex; 
	} //이렇게 반복을 끝내면 parentIndex에는 마지막 노드에 들어가야할 배열 인덱스가 된다. 

	h->heapArray[parentIndex] = lastTemp;
	h->heapSize -= 1;
	return temp;
}