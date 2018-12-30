#ifndef _GRAPH_SP_
#define _GRAPH_SP_

#define		MAX_INT		99999

// Dijkstra �˰���
int *shortestPathDijkstra(LinkedGraph* pGraph, int startVertexID);
int getMinDistance(int* distance, int *isSelected, int maxNodeCount);
int getEdgeWeight(LinkedGraph* pGraph, int fromVertexID, int toVertexID);

// Floyd �˰���
int** shortestPathFloyd(LinkedGraph* pGraph);
void printMatrix(int **A, int maxNodeCount);

#endif
