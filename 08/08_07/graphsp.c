#include <stdio.h>
#include <stdlib.h>
#include "graphlinkedlist.h"
#include "linkedgraph.h"
#include "graphsp.h"

// Dijkstra �˰���
int *shortestPathDijkstra(LinkedGraph* pGraph, int startVertexID) {
	int *pReturn = NULL;
	int *pSelected = NULL;
	int nodeCount = 0, maxNodeCount = 0;
	int i = 0, j = 0, weight = 0;
	int vertexID = 0, y_w = 0, y_v = 0;
	ListNode *pListNode = NULL;
	LinkedList *pEdgeList = NULL;

	if (pGraph == NULL) {
		printf("Graph is NULL\n");
		return pReturn;
	}
	maxNodeCount = getMaxVertexCountLG(pGraph);
	nodeCount = getVertexCountLG(pGraph);

	pReturn = (int *)malloc(sizeof(int) * maxNodeCount);
	pSelected = (int *)malloc(sizeof(int) * maxNodeCount);
	if (pReturn == NULL || pSelected == NULL) {
		if (pReturn != NULL) free(pReturn);
		printf("����, �޸� �Ҵ� in shortestPathDijkstra()\n");
		return NULL;
	}

	// Step 0. �ʱ�ȭ
	for(i = 0; i < maxNodeCount; i++) {
		if (i == startVertexID) {
			pReturn[i] = 0;
		}
		else {
			if (pGraph->pVertex[i] == USED) {
				pSelected[i] = TRUE;
				pReturn[i] = getEdgeWeight(pGraph, startVertexID, i);
			}
			else {
				pSelected[i] = FALSE;
				pReturn[i] = MAX_INT;
			}
		}
	}
	for(i = 0; i < maxNodeCount; i++) {
		printf("(%d,%d)->%d\n", startVertexID, i, pReturn[i]);
	}

	for(i = 0; i < nodeCount - 1; i++) {
		printf("[%d]-Iteration\n", i+1);

		// Step-1.
		// ���� S�� �ִ� �Ÿ��� ������ ����(vertexID)�� ����
		vertexID = getMinDistance(pReturn, pSelected, maxNodeCount);
		pSelected[vertexID] = FALSE;
	
		// ���õ� ����(vertexID)�� ������ �����鿡 ���� �Ÿ� ���� ���� ����.
		pEdgeList = pGraph->ppAdjEdge[vertexID];
		pListNode = pEdgeList->headerNode.pLink;
		while(pListNode != NULL) {
			int toVertexID = pListNode->data.vertexID;
			int weight = pListNode->data.weight;

			// y_v + c_v,w �� y_w ��
			y_v = pReturn[vertexID];
			y_w = pReturn[toVertexID];
			if (y_v + weight < y_w) {
				pReturn[toVertexID] = y_v + weight;
			}
			pListNode = pListNode->pLink;
		}

		for(j = 0; j < maxNodeCount; j++) {
			printf("\t(%d,%d)->%d\n", startVertexID, j, pReturn[j]);
		}
	}

	free(pSelected);
	
	return pReturn;
}

int getMinDistance(int* distance, int *pSelected, int maxNodeCount) {
	int pReturn = 0;
	int min_distance = MAX_INT;
	int i = 0;

	for(i = 0; i < maxNodeCount; i++) {
		if (pSelected[i] == TRUE && distance[i] < min_distance) {
			min_distance = distance[i];
			pReturn = i;
		}
	}

	return pReturn;
}

int getEdgeWeight(LinkedGraph* pGraph, int fromVertexID, int toVertexID) {
	int pReturn = MAX_INT;
	int position = 0;
	LinkedList* pEdgeList = NULL;
	ListNode* pListNode = NULL;

	if (pGraph != NULL) {
		pEdgeList = pGraph->ppAdjEdge[fromVertexID];
		if (pEdgeList != NULL) {
			position = findGraphNodePosition(pEdgeList, toVertexID);
			if (position >= 0) {
				pListNode = getLLElement(pEdgeList, position);
				if (pListNode != NULL) {
					pReturn = pListNode->data.weight;
				}
			}
		}
	}

	return pReturn;
}

// Floyd �˰���
int** shortestPathFloyd(LinkedGraph* pGraph) {
	int **pReturn = NULL;
	int r = 0, s = 0, v = 0;
	int weight = 0;
	int maxNodeCount = 0;

	if (pGraph == NULL) {
		printf("Graph is NULL\n");
		return NULL;
	}
	maxNodeCount = getMaxVertexCountLG(pGraph);
	printf("��� ����: %d\n", maxNodeCount);

	pReturn = (int **)malloc(sizeof(int*) * maxNodeCount);
	if (pReturn == NULL) {
		printf("����, �޸��Ҵ�(1) in shortestPathFloyd()\n");
		return NULL;
	}

	for(r = 0; r < maxNodeCount; r++) {
		pReturn[r] = (int *)malloc(sizeof(int) * maxNodeCount);
		if (pReturn[r] == NULL) {
			for(s = 0; s < r - 1; s++) {
				if (pReturn[s] != NULL) free(pReturn[s]);
			}
			if (pReturn != NULL)  free(pReturn);
			printf("����, �޸��Ҵ�(2) in shortestPathFloyd()\n");
			return NULL;
		}
	}
	// �ʱ�ȭ. �迭 pReturn�� �ʱ�ȭ
	for(r = 0; r < maxNodeCount; r++) {
		for(s = 0; s < maxNodeCount; s++) {
			if (r == s) {
				pReturn[r][s] = 0;
			}
			else {
				pReturn[r][s] = getEdgeWeight(pGraph, r, s);
			}
		}
	}
	printMatrix(pReturn, maxNodeCount);

	// Step 1. ���� Loop
	for(v = 0; v < maxNodeCount; v++) {
		for(r = 0; r < maxNodeCount; r++) {
			for(s = 0; s < maxNodeCount; s++) {
				if (pReturn[r][v] + pReturn[v][s] < pReturn[r][s]) {
					pReturn[r][s] = pReturn[r][v] + pReturn[v][s];
				}
			}
		}
		printf("[%d]-����\n", v+1);
		printMatrix(pReturn, maxNodeCount);
	}

	return pReturn;
}

void printMatrix(int **A, int maxNodeCount) {
	int r = 0;
	int s = 0;

	for(s = 0; s < maxNodeCount; s++) {
		printf("\t%d", s);
	}
	printf("\n");

	for(r = 0; r < maxNodeCount; r++) {
		printf("%d:\t", r);
		for(s = 0; s < maxNodeCount; s++) {
			printf("%d\t", A[r][s]);
		}
		printf("\n");
	}
}