#include <stdio.h>
#include <stdlib.h>
#include "linkedqueue.h"

void displayLinkedQueue(LinkedQueue *pQueue)
{
	QueueNode *pNode = NULL;
	int i = 0;
	if (pQueue != NULL) {
		printf("���� ��� ����: %d\n",
				pQueue->currentElementCount);
		pNode = pQueue->pFrontNode;
		while(pNode != NULL) {
			printf("[%d]-[%c]\n", i, pNode->data);
			i++;
			pNode = pNode->pLink;
		}
	}
}

int enqueueLQChar(LinkedQueue* pQueue, char data)
{
	QueueNode node = {0,};
	node.data = data;
	return enqueueLQ(pQueue, node);
}

int main(int argc, char *argv[])
{
	LinkedQueue *pQueue = NULL;
	QueueNode *pNode = NULL;
	char value = 0;

	// �迭 ť ����
	pQueue = createLinkedQueue();
	if (pQueue != NULL) {
		// ť �ʱ�ȭ: 'A', 'B', 'C', 'D' �߰�.
		enqueueLQChar(pQueue, 'A');
		enqueueLQChar(pQueue, 'B');
		enqueueLQChar(pQueue, 'C');
		enqueueLQChar(pQueue, 'D');
		displayLinkedQueue(pQueue);

		pNode = dequeueLQ(pQueue);
		if (pNode != NULL) {
			printf("Dequeue Value-[%c]\n", pNode->data);
			free( pNode );
		}

		pNode = dequeueLQ(pQueue);
		if (pNode != NULL) {
			printf("Dequeue Value-[%c]\n", pNode->data);
			free( pNode );
		}
		displayLinkedQueue(pQueue);

		pNode = peekLQ(pQueue);
		if (pNode != NULL) {
			printf("Peek Value-[%c]\n", pNode->data);
		}
		displayLinkedQueue(pQueue);

		// ť�� 'E', 'F' �߰�.
		enqueueLQChar(pQueue, 'E');

		displayLinkedQueue(pQueue);
	}
	return 0;
}
