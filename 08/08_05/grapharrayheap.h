#ifndef _ARRAY_HEAP_
#define _ARRAY_HEAP_

typedef struct HeapElementType
{
	int key;
	int fromVertexID;
	int toVertexID;
} HeapNode;

typedef struct ArrayHeapType
{
	int maxElementCount;		// �ִ� ��� ����
	int currentElementCount;	// ���� ��� ����
	HeapNode *pElement;		// ��� ������ ���� 1���� array
} ArrayMaxHeap, ArrayMinHeap;

// �ִ� ������ ����
ArrayMaxHeap* createArrayMaxHeap(int maxElementCount);

// �ִ� ������ ����
void deleteArrayMaxHeap(ArrayMaxHeap* pArrayHeap);

// �ּ� ������ ����
ArrayMinHeap* createArrayMinHeap(int maxElementCount);

// �ּ� ������ ����
void deleteArrayMinHeap(ArrayMinHeap* pArrayHeap);

// �ִ� ������ ����
void insertMaxHeapAH(ArrayMaxHeap* pArrayHeap, HeapNode element);

// �ִ� ������ ����
HeapNode* deleteMaxHeapAH(ArrayMaxHeap* pArrayHeap);

// �ּ� ������ ����
void insertMinHeapAH(ArrayMinHeap* pArrayHeap, HeapNode element);

// �ּ� ������ ����
HeapNode* deleteMinHeapAH(ArrayMinHeap* pArrayHeap);

// ���� ���� ���
void displayArrayHeap(ArrayMaxHeap* pList);

#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE		1
#define FALSE		0

#endif