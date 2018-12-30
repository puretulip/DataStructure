#ifndef _GRAPH_MST_KRUSKAL_
#define _GRAPH_MST_KRUSKAL_

// Kruskal �˰���
LinkedGraph *mstKruskal(LinkedGraph* pGraph);

// ���� �׷���G�� ������ ����ġ ���� ������������ ����.
ArrayMinHeap *orderEdges(LinkedGraph* pGraph);

// ��ȯ �˻�.
int checkCycle(LinkedGraph* pGraph, int fromVertexID, int toVertexID);

#endif
