#include <stdio.h>
#include <stdlib.h>
#include "simdef.h"
#include "simlinkedqueue.h"
#include "simutil.h"

int main(int argc, char *argv[])
{
	int currentTime = 0;
	int endTime = 10;
	int serviceUserCount = 0;
	int totalWaitTime = 0;

	LinkedQueue *pArrivalQueue = NULL, *pWaitQueue = NULL;
	QueueNode* pServiceNode1 = NULL;

	pArrivalQueue = createLinkedQueue();
	pWaitQueue = createLinkedQueue();
	if (pArrivalQueue != NULL && pWaitQueue == NULL) {
		printf("����, createLinkedQueue()\n");
		return FALSE;
	}

	insertCutomer(0, 3, pArrivalQueue);	// ���� �ð�: 0, ���� �ð�: 3
	insertCutomer(2, 2, pArrivalQueue);	// ���� �ð�: 2, ���� �ð�: 2
	insertCutomer(4, 1, pArrivalQueue);	// ���� �ð�: 4, ���� �ð�: 1
	insertCutomer(6, 1, pArrivalQueue);	// ���� �ð�: 6, ���� �ð�: 1
	insertCutomer(8, 3, pArrivalQueue);	// ���� �ð�: 8, ���� �ð�: 3

	for(currentTime = 0; currentTime < endTime; currentTime++) {
		processArrival(currentTime, pArrivalQueue, pWaitQueue);

		// ���� ���� ó��.
		if (pServiceNode1 != NULL) {
			pServiceNode1 = processServiceNodeEnd(currentTime, 
				pServiceNode1, &serviceUserCount, &totalWaitTime);
		}

		// ���� ���� ó��.
		if (pServiceNode1 == NULL) {
			pServiceNode1 = processServiceNodeStart(currentTime, pWaitQueue);
		}

		// ��� ť�� ���� ���.
		printWaitQueueStatus(currentTime, pWaitQueue);
	}

	// ���� �ùķ��̼� ��� ���.
	printReport(pWaitQueue, serviceUserCount, totalWaitTime);

	// �޸� ����.
	if (pServiceNode1 != NULL) {
		free(pServiceNode1);
	}
	deleteLinkedQueue(pArrivalQueue);
	deleteLinkedQueue(pWaitQueue);

	return 0;
}
