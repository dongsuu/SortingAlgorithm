#pragma once

typedef struct heap { //��
	int *heapArray; //�� �迭
	int heapSize; //�� ũ��
}Heap;

void HeapInit(Heap *h, int* data, int num); //�� �ʱ�ȭ
int HeapIsEmpty(Heap* h); //�� ����ִ��� Ȯ��
int getParent(int index);  //�θ� ��� �ε��� ��ȯ
int getLeftChild(int index);  //���� �ڽĳ�� �ε��� ��ȯ
int getRightChild(int index); //������ �ڽĳ�� �ε��� ��ȯ
int getBiggerChild(Heap* h, int index); //�ڽ� ��� �� ū �� ��ȯ
void HeapInsert(Heap* h, int data); //���� data Insert
int HeapDelete(Heap* h);  //������ data delete


