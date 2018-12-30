#include <stdio.h>
#include <stdlib.h>
#include "graphlinkedlist.h"
#include "linkedstack.h"
#include "linkedgraph.h"
#include "grapharrayheap.h"
#include "graphmst.h"

LinkedGraph* mstKruskal(LinkedGraph* pGraph)
{
	LinkedGraph* pReturn = NULL;
	int i = 0;
	int maxNodeCount = 0;
	int currentNodeCounde = 0;
	int edgeCount = 0;
	int isCycle = 0;
	ArrayMinHeap *pMinHeap = NULL;
	HeapNode *pHeapNode = NULL;

	if (pGraph == NULL) {
		printf("Graph is NULL\n");
		return NULL;
	}

	maxNodeCount = getMaxVertexCountLG(pGraph);
	currentNodeCounde = getVertexCountLG(pGraph);
	edgeCount = getEdgeCountLG(pGraph);

	pReturn = createLinkedGraph(maxNodeCount);
	if (pReturn == NULL) {
		return NULL;
	}
	pMinHeap = orderEdges(pGraph);
	if (pMinHeap == NULL) {
		return NULL;
	}
	for(i = 0; i < edgeCount; i++) {
		pHeapNode = deleteMinHeapAH(pMinHeap);
		if (pHeapNode != NULL) {
			isCycle = checkCycle(pReturn, pHeapNode->fromVertexID, 
								pHeapNode->toVertexID);
			if (isCycle == FALSE) {
				if (pReturn->pVertex[pHeapNode->fromVertexID] != USED) {
					addVertexLG(pReturn, pHeapNode->fromVertexID);
				}
				if (pReturn->pVertex[pHeapNode->toVertexID] != USED) {
					addVertexLG(pReturn, pHeapNode->toVertexID);
				}
				addEdgewithWeightLG(pReturn, pHeapNode->fromVertexID, 
						pHeapNode->toVertexID, pHeapNode->key);
				printf("[%d], �ּ� ����ġ: (%d,%d)->%d\n", 
						i, pHeapNode->fromVertexID, pHeapNode->toVertexID, 
						pHeapNode->key);
			}
			free(pHeapNode);

			if (getVertexCountLG(pReturn) == currentNodeCounde) {
				break;
			}
		}
	}

	return pReturn;
}

ArrayMinHeap *orderEdges(LinkedGraph* pGraph) {
	int i = 0;
	int edgeCount = 0;
	ArrayMinHeap *pReturn = NULL;
	ListNode *pListNode = NULL;
	LinkedList* pEdgeList = NULL;

	if (pGraph == NULL) {
		printf("Graph is NULL\n");
		return pReturn;
	}

	edgeCount = getEdgeCountLG(pGraph);
	if (edgeCount == 0) {
		printf("����, ���� ������ 0��\n");
		return pReturn;
	}

	pReturn = createArrayMinHeap(edgeCount);
	if (pReturn == NULL) {
		return pReturn;
	}

	for(i = 0; i < pGraph->maxVertexCount; i++) {
		if (pGraph->pVertex[i] == USED) {
			pEdgeList = pGraph->ppAdjEdge[i];
			pListNode = pEdgeList->headerNode.pLink;
			while(pListNode != NULL) {
				int vertexID = pListNode->data.vertexID;
				int weight = pListNode->data.weight;

				// ������ �׷������, ������ ������ 2�� ���ϵǹǷ�,
				// ���� ��� id�� ���� ��� id���� ���� ��츸 ���ϵǵ��� �Ѵ�.
				// ��, ���� 1���� ���ϵǵ��� �Ѵ�.
				if (pGraph->graphType == GRAPH_DIRECTED
					|| (pGraph->graphType == GRAPH_UNDIRECTED && i < vertexID)) {
					HeapNode heapNode = {0,};
					heapNode.fromVertexID = i;
					heapNode.toVertexID = vertexID;
					heapNode.key = weight;
					insertMinHeapAH(pReturn, heapNode);
				}

				pListNode = pListNode->pLink;
			}
		}
	}

	return pReturn;
}

int pushLSForDFS(LinkedStack* pStack, int nodeID)
{
	StackNode node = {0,};
	node.data = nodeID;
	return pushLS(pStack, node);
}

// ���� �߰��� ���� ��ȯ�� �߻��ϴ� �� �˻�.
// ������ ��ΰ� �־��ٸ�, ��ȯ�� �߻��Ѵ�.
// ������ ���̿켱Ž��(DFS)�� ���.
int checkCycle(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	int pReturn = FALSE;

	int i = 0;
	int vertextID = 0;
	LinkedStack* pStack = NULL;
	StackNode* pStackNode = NULL; 
	ListNode *pListNode = NULL;
	int *pVisited = NULL;

	if (pGraph == NULL) {
		return pReturn;
	}

	pStack = createLinkedStack();
	if (pStack == NULL) {
		return pReturn;
	}

	pVisited = (int*) malloc(sizeof(int) * pGraph->maxVertexCount);
	if (pVisited == NULL) {
		printf("Error, malloc() in traversalDFS()\n");
		deleteLinkedStack(pStack);
		return pReturn;
	}

	// �ʱ�ȭ.
	for(i = 0; i < pGraph->maxVertexCount; i++) {
		pVisited[i] = FALSE;
	}
	
	pVisited[fromVertexID] = TRUE;
	pushLSForDFS(pStack, fromVertexID);

	while(isLinkedStackEmpty(pStack) == FALSE) {
		pStackNode = popLS(pStack);
		if (pStackNode != NULL) {
			vertextID = pStackNode->data;
			if (vertextID == toVertexID) {
				printf("(%d,%d)-������ ��ΰ� �����մϴ�.\n", 
						fromVertexID, toVertexID);
				pReturn = TRUE;
				break;
			}

			pListNode = pGraph->ppAdjEdge[vertextID]->headerNode.pLink;
			while(pListNode != NULL) {
				int vertexID = pListNode->data.vertexID;
				if (pVisited[vertexID] == FALSE) {
					pVisited[vertexID] = TRUE;
					pushLSForDFS(pStack, vertexID);
				}

				pListNode = pListNode->pLink;
			}
		}
	}

	free(pVisited);
	deleteLinkedStack(pStack);

	return pReturn;
}
