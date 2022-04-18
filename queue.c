#include"LinkedListQueue.h";
#include<stdio.h>
#include<stdlib.h>

void QueueInit(Queue* q) { //큐의 초기화. front와 null을 모두 null을 가리키게 한다.
	q->front = NULL;
	q->rear = NULL;

}

int QueueIsEmpty(Queue* q) {
	if (q->front == NULL)  //queue의 front가 0인것은 빼낼 것이 없다는 것. queue가 empty맞음 
		return 1;  //1반환
	else //queue 비어있지 않으면 0 반환
		return 0;
}

void Enqueue(Queue* q, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node)); //새 노드 생성
	newNode->next = NULL;  //새 노드는 null을 가리킨다. 
	newNode->data = data; //새 노드에 data 삽입

	if (QueueIsEmpty(q)) { //첫 번째 노드 생성했을 경우. 
		q->front = newNode; //새 노의 front와 rear은 모두 null을 가리킨다. (하나밖에 없으므로)
		q->rear = newNode;
	}
	else { //두 번째 노드의 삽입부터는
		q->rear->next = newNode;  // 큐를 연결하기 위하여 큐의 꼬리부분이 새 노드를 가리키게 하여 연결한다.
		q->rear = newNode; //rear는 이제 새 노드를 가리킨다.
	}
}

int Dequeue(Queue* q) {
	Node* deleteNode; //삭제할 노드
	int temp; //삭제할 노드의 데이터 임시 저장

	if (QueueIsEmpty(q)) { //큐가 비어있으면 삭제할 것이 없으므로 error
		printf("Queue is empty!");
		exit(-1);
	}

	deleteNode = q->front; //삭제할 노드는 front로 control하기 때문에 삭제할 노드는 현재 큐의 front이다.
	temp = deleteNode->data; //삭제할 노드의 데이터 temp에 저장
	q->front = q->front->next; //삭제했으므로 queue의 front는 원래 연결되어있던 것 다음 것을 가리키게 한다.
	free(deleteNode);
	return temp; //삭제한 노드 데이터 반환
}

int QueuePeek(Queue* q) {
	if (QueueIsEmpty(q)) { //큐가 비어있으면 삭제할 것이 없으므로 error
		printf("Queue is empty!");
		exit(-1);
	}
	return q->front->data;
}
