#ifndef _AVL_TREE_
#define _AVL_TREE_

typedef struct AVLTreeType
{
	AVLTreeNode *pRootNode;
} AVLTree;

// Ʈ���� ����
AVLTree* createAVLTree();

// Ʈ���� ����
void deleteAVLTree(AVLTree* pAVLTree);

// Ʈ�� ����� ����(�����)
void deleteAVLTreeNode(AVLTreeNode* pAVLTreeNode);

// ���ο� ��� ����.
int insertNodeAVL(AVLTree* pAVLTree, AVLTreeNodeData data);

// ���� ��� ����.
int deleteNodeAVL(AVLTree* pAVLTree, int key);

// ���� ���.
void balanceAVLTree(AVLTree* pAVLTree, LinkedStack* pStack);

int pushAVLTreeNode(LinkedStack* pStack, AVLTreeNode* data);

AVLTreeNode *popAVLTreeNode(LinkedStack* pStack);

AVLTreeNode *peekAVLTreeNode(LinkedStack* pStack);

// ���� ���: LL ȸ��
AVLTreeNode* rotateLLAVLTree(AVLTreeNode *pParentNode);

// ���� ���: LR ȸ��
AVLTreeNode* rotateLRAVLTree(AVLTreeNode *pParentNode);

// ���� ���: RR ȸ��
AVLTreeNode* rotateRRAVLTree(AVLTreeNode *pParentNode);

// ���� ���: RL ȸ��
AVLTreeNode* rotateRLAVLTree(AVLTreeNode *pParentNode);

// ����, ���� ���� ����.
void updateHeightAndBalanceAVL(AVLTreeNode* pNode);

// (�ݺ���) Ž��.
AVLTreeNode* searchAVL(AVLTree* pAVLTree, int key);

void displayAVLTree(AVLTree *pTree);

void displayAVLTreeInternal(AVLTreeNode *pTreeNode, int level, char type);

#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE		1
#define FALSE		0

#endif