#pragma once
typedef struct node {
	int data;
	struct node* next; //다음 노드를 가리키는 노드 포인터 변수
} Node;

typedef struct queue {
	Node* front; //큐의 머리
	Node* rear;  //큐의 꼬리
} Queue;

void QueueInit(Queue* q); //queue 초기화
int QueueIsEmpty(Queue* q); //queue 비어있는지 확인
void Enqueue(Queue* q, int data); //queue에 data 넣는 연산
int Dequeue(Queue* q); //queue에서 data 빼기
int QueuePeek(Queue* q); //queue에서 다음 삭제될 노드 
