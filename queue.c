#include"LinkedListQueue.h";
#include<stdio.h>
#include<stdlib.h>

void QueueInit(Queue* q) { //ť�� �ʱ�ȭ. front�� null�� ��� null�� ����Ű�� �Ѵ�.
	q->front = NULL;
	q->rear = NULL;

}

int QueueIsEmpty(Queue* q) {
	if (q->front == NULL)  //queue�� front�� 0�ΰ��� ���� ���� ���ٴ� ��. queue�� empty���� 
		return 1;  //1��ȯ
	else //queue ������� ������ 0 ��ȯ
		return 0;
}

void Enqueue(Queue* q, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node)); //�� ��� ����
	newNode->next = NULL;  //�� ���� null�� ����Ų��. 
	newNode->data = data; //�� ��忡 data ����

	if (QueueIsEmpty(q)) { //ù ��° ��� �������� ���. 
		q->front = newNode; //�� ���� front�� rear�� ��� null�� ����Ų��. (�ϳ��ۿ� �����Ƿ�)
		q->rear = newNode;
	}
	else { //�� ��° ����� ���Ժ��ʹ�
		q->rear->next = newNode;  // ť�� �����ϱ� ���Ͽ� ť�� �����κ��� �� ��带 ����Ű�� �Ͽ� �����Ѵ�.
		q->rear = newNode; //rear�� ���� �� ��带 ����Ų��.
	}
}

int Dequeue(Queue* q) {
	Node* deleteNode; //������ ���
	int temp; //������ ����� ������ �ӽ� ����

	if (QueueIsEmpty(q)) { //ť�� ��������� ������ ���� �����Ƿ� error
		printf("Queue is empty!");
		exit(-1);
	}

	deleteNode = q->front; //������ ���� front�� control�ϱ� ������ ������ ���� ���� ť�� front�̴�.
	temp = deleteNode->data; //������ ����� ������ temp�� ����
	q->front = q->front->next; //���������Ƿ� queue�� front�� ���� ����Ǿ��ִ� �� ���� ���� ����Ű�� �Ѵ�.
	free(deleteNode);
	return temp; //������ ��� ������ ��ȯ
}

int QueuePeek(Queue* q) {
	if (QueueIsEmpty(q)) { //ť�� ��������� ������ ���� �����Ƿ� error
		printf("Queue is empty!");
		exit(-1);
	}
	return q->front->data;
}
