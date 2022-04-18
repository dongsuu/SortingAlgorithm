#include"heap.h"

int HeapIsEmpty(Heap* h) { //���� ����ִ��� Ȯ��
	if (h->heapSize  == 0)
		return 1;
	else
		return 0;
}

void HeapInit(Heap * h, int *data, int num) { //���� �ʱ�ȭ
	h->heapSize = 0;
	h->heapArray = malloc(sizeof(Heap) * num+1);
	
}
int getParent(int index) { //parent node index ��ȯ
	return index / 2;
}
int getLeftChild(int index) { //left child node index ��ȯ
	return index * 2;
}
int getRightChild(int index) { //right child node index ��ȯ
	return index * 2 + 1;
}

int getBiggerChild(Heap* h, int index) {
	if (getLeftChild(index) > h->heapSize) // �ڽ� ��尡 ������ ���� �ڽ� ����� index�� heapsize���� ũ�Եȴ�.
		return 0;

	else if (getLeftChild(index) == h->heapSize) //���� �ڽ� ��常 ������ heapSize�� leftchild�� �ڽ� ��� index �����ϴ�.
		return getLeftChild(index);
	else {
		if (h->heapArray[getLeftChild(index)] > h->heapArray[getRightChild(index)]) // ���� �ڽ��� �� ũ�� ���� �ڽ� return
			return getLeftChild(index);
		else { //������ �ڽ��� �� ũ�� ������ �ڽ� return
			return getRightChild(index);
		}
	}
}

void HeapInsert(Heap* h, int data) {
	int index = h->heapSize + 1; //�����Ͱ� ���Ե� ��ġ�� �� ������ ���� +1
	
	while (index != 1) {
		if (h->heapArray[getParent(index)] < data) { //�� ����� ���� �� ũ�ٸ� 
			h->heapArray[index] = h->heapArray[getParent(index)]; // ���� �� �ڸ��� ���� �θ� ����.
			index = getParent(index); // �� ��� ���� ���� index�� ����
		}
		else //�� ��� ���� �� ������ �׳� ���� ������ ��ġ�� �״�� ���� �ȴ�. 
			break;
	}
	h->heapArray[index] = data; //�� ��� �迭�� ����. 
	h->heapSize += 1; //size 1��ŭ ����
}

int HeapDelete(Heap* h) {
	int temp = h->heapArray[1]; //root��尡 ���� �����. ������ ������ �ӽ� ����
	int lastTemp = h->heapArray[h->heapSize]; //������ ��ġ�� ����Ǿ� �ִ� �� �ӽ� ����
	int parentIndex = 1;
	int childIndex;
	
	while (childIndex = getBiggerChild(h, parentIndex)) { //2���� �ڽ� ��忡�� ū ������ �ݺ� ����
		if (lastTemp >= h->heapArray[childIndex]) //������ ��ġ�� ���� ���� ����� �ڽ� ����� ū �� ���� ũ�� break.
			break; //�̶� heapArray[parentIndex]�� ������ ��ġ�� ��� �� �����Ѵ�. 

		//�� ��� ��� �� ���� �ø���. 
		h->heapArray[parentIndex] = h->heapArray[childIndex];
		parentIndex = childIndex; 
	} //�̷��� �ݺ��� ������ parentIndex���� ������ ��忡 ������ �迭 �ε����� �ȴ�. 

	h->heapArray[parentIndex] = lastTemp;
	h->heapSize -= 1;
	return temp;
}