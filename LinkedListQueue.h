#pragma once
typedef struct node {
	int data;
	struct node* next; //���� ��带 ����Ű�� ��� ������ ����
} Node;

typedef struct queue {
	Node* front; //ť�� �Ӹ�
	Node* rear;  //ť�� ����
} Queue;

void QueueInit(Queue* q); //queue �ʱ�ȭ
int QueueIsEmpty(Queue* q); //queue ����ִ��� Ȯ��
void Enqueue(Queue* q, int data); //queue�� data �ִ� ����
int Dequeue(Queue* q); //queue���� data ����
int QueuePeek(Queue* q); //queue���� ���� ������ ��� 
