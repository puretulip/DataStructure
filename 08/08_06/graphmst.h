#ifndef _GRAPH_MST_
#define _GRAPH_MST_

typedef struct GraphEdgeType
{
	int vertexIDFrom;		// Tail ��� ID
	int vertexIDTo;			// Head ��� ID
	int	weight;				// ����ġ
} GraphEdge;

// ��ȯ �˻�.
int checkCycle(LinkedGraph* pGraph, int fromVertexID, int toVertexID);

// Prim �˰���
LinkedGraph *mstPrim(LinkedGraph* pGraph, int vertexID);

// ����(mstVertexID)�� �μӵ� ��� ������ ��, 
// ����ġ�� ���� �����鼭 ��ȯ�� �߻���Ű�� �ʴ� ������ ����.
void getMinWeightEdge(LinkedGraph* pGraph, LinkedGraph* pMST,
					  int mstVertexID, GraphEdge *pMinWeightEdge);

int checkEdge(LinkedGraph* pGraph, int fromVertexID, int toVertexID);

#define		MAX_INT		99999
#endif
