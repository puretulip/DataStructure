#include <stdio.h>
#include <stdlib.h>
#include "graphlinkedlist.h"
#include "linkedgraph.h"
#include "graphsp.h"

int main(int argc, char *argv[])
{
	int i = 0;
	LinkedGraph *pG = NULL;
	int *pResult = NULL;
	int **A = NULL;

	// �׷��� ����
	pG = createLinkedGraph(6);
	if (pG != NULL) {
		// �׷��� �ʱ�ȭ: ��� �߰�
		for(i = 0; i < 6; i++) {
			addVertexLG(pG, i);
		}

		// �׷��� �ʱ�ȭ: ���� �߰�
		addEdgewithWeightLG(pG, 0, 1, 1);
		addEdgewithWeightLG(pG, 0, 2, 4);
		addEdgewithWeightLG(pG, 1, 2, 2);
		addEdgewithWeightLG(pG, 2, 3, 1);
		addEdgewithWeightLG(pG, 3, 4, 8);
		addEdgewithWeightLG(pG, 3, 5, 3);
		addEdgewithWeightLG(pG, 4, 5, 4);

		printf("G1:\n");
		displayLinkedGraph(pG);

		printf("\nDijkstra:\n");
		pResult = shortestPathDijkstra(pG, 0);

		printf("\nFloyd:\n");
		A = shortestPathFloyd(pG);

		// �׷��� ����
		if (pResult != NULL) {
			free(pResult);
		}
		if (A != NULL) {
			int r = 0;
			int maxNodeCount = getMaxVertexCountLG(pG);
			for(r = 0; r < maxNodeCount; r++) {
				free(A[r]);
			}
			free(A);
		}
		deleteLinkedGraph(pG);
	}

	return 0;
}
