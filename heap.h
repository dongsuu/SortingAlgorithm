#pragma once

typedef struct heap { //힙
	int *heapArray; //힙 배열
	int heapSize; //힙 크기
}Heap;

void HeapInit(Heap *h, int* data, int num); //힙 초기화
int HeapIsEmpty(Heap* h); //힙 비어있는지 확인
int getParent(int index);  //부모 노드 인덱스 반환
int getLeftChild(int index);  //왼쪽 자식노드 인덱스 반환
int getRightChild(int index); //오른쪽 자식노드 인덱스 반환
int getBiggerChild(Heap* h, int index); //자식 노드 중 큰 값 반환
void HeapInsert(Heap* h, int data); //힙에 data Insert
int HeapDelete(Heap* h);  //힙에서 data delete


