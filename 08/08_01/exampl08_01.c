#include <stdio.h>
#include <stdlib.h>
#include "arraygraph.h"

int main(int argc, char *argv[])
{
	int i = 0;
	ArrayGraph *pG1 = NULL;
	ArrayGraph *pG2 = NULL;
	ArrayGraph *pG4 = NULL;

	// �׷��� ����
	pG1 = createArrayGraph(6);
	pG2 = createArrayDirectedGraph(6);
	pG4 = createArrayDirectedGraph(6);
	if (pG1 != NULL && pG2 != NULL && pG4 != NULL)
	{
		// �׷��� �ʱ�ȭ: ���� �߰�
		for(i = 0; i < 6; i++)
		{
			addVertexAG(pG1, i);
			addVertexAG(pG2, i);
			addVertexAG(pG4, i);
		}

		// �׷��� �ʱ�ȭ: ���� �߰�
		addEdgeAG(pG1, 0, 1);
		addEdgeAG(pG1, 0, 2);
		addEdgeAG(pG1, 1, 2);
		addEdgeAG(pG1, 2, 3);
		addEdgeAG(pG1, 3, 4);
		addEdgeAG(pG1, 3, 5);
		addEdgeAG(pG1, 4, 5);

		addEdgeAG(pG2, 0, 1);
		addEdgeAG(pG2, 1, 2);
		addEdgeAG(pG2, 2, 0);
		addEdgeAG(pG2, 2, 1);
		addEdgeAG(pG2, 2, 3);
		addEdgeAG(pG2, 3, 2);
		addEdgeAG(pG2, 3, 4);
		addEdgeAG(pG2, 4, 5);
		addEdgeAG(pG2, 5, 3);

		addEdgewithWeightAG(pG4, 0, 1, 4);
		addEdgewithWeightAG(pG4, 1, 2, 1);
		addEdgewithWeightAG(pG4, 2, 0, 2);
		addEdgewithWeightAG(pG4, 2, 1, 3);
		addEdgewithWeightAG(pG4, 2, 3, 2);
		addEdgewithWeightAG(pG4, 3, 2, 1);
		addEdgewithWeightAG(pG4, 3, 4, 1);
		addEdgewithWeightAG(pG4, 4, 5, 1);
		addEdgewithWeightAG(pG4, 5, 3, 2);

		// �׷��� ���� ���
		printf("G1: ������ �׷���\n");
		displayArrayGraph(pG1);
		printf("\nG2: ���� �׷���\n");
		displayArrayGraph(pG2);
		printf("\nG3: ���� ���� �׷���\n");
		displayArrayGraph(pG4);

		// �׷��� ����
		deleteArrayGraph(pG1);
		deleteArrayGraph(pG2);
		deleteArrayGraph(pG4);
	}

	return 0;
}
