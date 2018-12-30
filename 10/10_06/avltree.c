#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avldef.h"
#include "avllinkedstack.h"
#include "avltree.h"

// Ʈ���� ����
AVLTree* createAVLTree()
{
	AVLTree *pReturn = NULL;

	pReturn = (AVLTree *)malloc(sizeof(AVLTree));
	if (pReturn != NULL) {	// �޸� �Ҵ� ���� ����
		// ������ �ʱ�ȭ.
		memset(pReturn, 0, sizeof(AVLTree));
	}
	else {
		printf("����, malloc() in createAVLTree()\n");
		return NULL;
	}

	return pReturn;
}

// (�ݺ���) Ž��.
AVLTreeNode* searchAVL(AVLTree* pAVLTree, int key)
{
	AVLTreeNode* pReturn = NULL;
	AVLTreeNode* pNode = NULL;

	if (pAVLTree == NULL) {
		return NULL;
	}

	pNode = pAVLTree->pRootNode;
	if (pNode == NULL) {
		return NULL;
	}

	while(pNode != NULL) {
		if (key == pNode->data.key) {
			pReturn = pNode;
			break;
		}
		else if (key < pNode->data.key) {
			pNode = pNode->pLeftChild;
		}
		else {
			pNode = pNode->pRightChild;
		}
	}

	return pReturn;
}

// ���ο� ��� ����.
int insertNodeAVL(AVLTree* pAVLTree, AVLTreeNodeData element)
{
	int ret = TRUE;
	AVLTreeNode* pParentNode = NULL;
	AVLTreeNode* pNewNode = NULL;
	LinkedStack* pStack = NULL;

	if (pAVLTree == NULL) {
		ret = FALSE;
		return ret;
	}

	pStack = createLinkedStack();
	if (pStack == NULL) {
		ret = FALSE;
		return ret;
	}

	pParentNode = pAVLTree->pRootNode;
	while(pParentNode != NULL) {
		pushAVLTreeNode(pStack, pParentNode);

		if (element.key == pParentNode->data.key) {
			printf("����, �ߺ��� Ű[%d]�� �����մϴ�,insertNodeAVL()\n", element.key);
			ret = FALSE;
			return ret;
		}
		else if (element.key < pParentNode->data.key) {
			if (pParentNode->pLeftChild == NULL) {
				break;
			}
			else {
				pParentNode = pParentNode->pLeftChild;
			}
		}
		else {
			if (pParentNode->pRightChild == NULL) {
				break;
			}
			else {
				pParentNode = pParentNode->pRightChild;
			}
		}
	}

	pNewNode = (AVLTreeNode *)malloc(sizeof(AVLTreeNode));
	if (pNewNode != NULL) {	// �޸� �Ҵ� ���� ����
		// ������ �ʱ�ȭ.
		memset(pNewNode, 0, sizeof(AVLTreeNode));
		pNewNode->data = element;
		pNewNode->height = 1;
	}
	else {
		printf("����, malloc() in insertNodeAVL()\n");
		deleteLinkedStack(pStack);
		return FALSE;
	}

	if (pParentNode == NULL) {
		pAVLTree->pRootNode = pNewNode;
	}
	else {
		if (pNewNode->data.key < pParentNode->data.key) {
			pParentNode->pLeftChild = pNewNode;
		}
		else {
			pParentNode->pRightChild = pNewNode;
		}
	}
	ret = TRUE;

	balanceAVLTree(pAVLTree, pStack);

	deleteLinkedStack(pStack);

	return ret;
}

// ���� ���.
void balanceAVLTree(AVLTree* pAVLTree, LinkedStack* pStack)
{
	AVLTreeNode *pParentNode = NULL;
	AVLTreeNode *pNode = NULL;
	AVLTreeNode *pChildNode = NULL;
	AVLTreeNode *pNewNode = NULL;

	if (pAVLTree == NULL || pStack == NULL) {
		return;
	}

	while(isLinkedStackEmpty(pStack) == FALSE) {
		pNode = popAVLTreeNode(pStack);
		if (pNode != NULL) {
			updateHeightAndBalanceAVL(pNode);

			if (pNode->balance >= -1 && pNode->balance <= 1) {
				continue;			
			}

			if (pNode->balance > 1) {
				pChildNode = pNode->pLeftChild;
				if (pChildNode->balance > 0) {
					pNewNode = rotateLLAVLTree(pNode);
				}
				else {
					pNewNode = rotateLRAVLTree(pNode);
				}
			}
			else if (pNode->balance < -1) {
				pChildNode = pNode->pRightChild;
				if (pChildNode->balance < 0) {
					pNewNode = rotateRRAVLTree(pNode);
				}
				else {
					pNewNode = rotateRLAVLTree(pNode);
				}
			}

			pParentNode = peekAVLTreeNode(pStack);
			if (pParentNode != NULL) {
				if (pParentNode->pLeftChild == pNode) {
					pParentNode->pLeftChild = pNewNode;
				}
				else {
					pParentNode->pRightChild = pNewNode;
				}
			}
			else {
				pAVLTree->pRootNode = pNewNode;
			}
		}
	}
}

int pushAVLTreeNode(LinkedStack* pStack, AVLTreeNode* data)
{
	StackNode node = {0,};
	node.data = data;

	return pushLS(pStack, node);
}

AVLTreeNode *popAVLTreeNode(LinkedStack* pStack)
{
	AVLTreeNode *pReturn = NULL;

	if (isLinkedStackEmpty(pStack) == FALSE) {
		StackNode* pNode = popLS(pStack);
		if (pNode != NULL) {
			pReturn = pNode->data;

			free(pNode);
		}
	}

	return pReturn;
}

AVLTreeNode *peekAVLTreeNode(LinkedStack* pStack)
{
	AVLTreeNode *pReturn = NULL;

	if (isLinkedStackEmpty(pStack) == FALSE) {
		StackNode* pNode = peekLS(pStack);
		if (pNode != NULL) {
			pReturn = pNode->data;
		}
	}

	return pReturn;
}

// ���� ���: LL ȸ��
AVLTreeNode* rotateLLAVLTree(AVLTreeNode *pParentNode)
{
	AVLTreeNode *pLeftNode = NULL;

	if (pParentNode != NULL) {
		pLeftNode = pParentNode->pLeftChild;
		pParentNode->pLeftChild = pLeftNode->pRightChild;
		pLeftNode->pRightChild = pParentNode;

		updateHeightAndBalanceAVL(pParentNode);
		updateHeightAndBalanceAVL(pLeftNode);
	}

	return pLeftNode;
}

// ���� ���: RR ȸ��
AVLTreeNode* rotateRRAVLTree(AVLTreeNode *pParentNode)
{
	AVLTreeNode *pRightNode = NULL;

	if (pParentNode != NULL) {
		pRightNode = pParentNode->pRightChild;
		pParentNode->pRightChild = pRightNode->pLeftChild;
		pRightNode->pLeftChild = pParentNode;

		updateHeightAndBalanceAVL(pParentNode);
		updateHeightAndBalanceAVL(pRightNode);
	}

	return pRightNode;
}

// ���� ���: LR ȸ��
AVLTreeNode* rotateLRAVLTree(AVLTreeNode *pParentNode)
{
	AVLTreeNode *pReturn = NULL;
	AVLTreeNode *pLeftNode = NULL;

	if (pParentNode != NULL) {
		pLeftNode = pParentNode->pLeftChild;
		pParentNode->pLeftChild = rotateRRAVLTree(pLeftNode);

		pReturn = rotateLLAVLTree(pParentNode);
	}

	return pReturn;
}

// ���� ���: RL ȸ��
AVLTreeNode* rotateRLAVLTree(AVLTreeNode *pParentNode)
{
	AVLTreeNode *pReturn = NULL;
	AVLTreeNode *pRightNode = NULL;

	if (pParentNode != NULL) {
		pRightNode = pParentNode->pRightChild;
		pParentNode->pRightChild = rotateLLAVLTree(pRightNode);
		pReturn = rotateRRAVLTree(pParentNode);
	}

	return pReturn;
}

// ���� �� ���� �μ� ���� ����.
void updateHeightAndBalanceAVL(AVLTreeNode *pNode)
{
	int leftHeight = 0;
	int rightHeight = 0;
	if (pNode != NULL) {
		if (pNode->pLeftChild != NULL) {
			
			leftHeight = pNode->pLeftChild->height;
		}

		if (pNode->pRightChild != NULL) {
			
			rightHeight = pNode->pRightChild->height;
		}

		if (leftHeight > rightHeight) {
			pNode->height = leftHeight + 1;
		}
		else {
			pNode->height = rightHeight + 1;
		}

		pNode->balance = leftHeight - rightHeight;
	}
}

// ���� ��� ����.
int deleteNodeAVL(AVLTree* pAVLTree, int key)
{
	int ret = TRUE;
	AVLTreeNode* pDelNode = NULL;
	AVLTreeNode* pParentNode = NULL;

	AVLTreeNode* pPredecessor = NULL;
	AVLTreeNode* pSuccessor = NULL;

	AVLTreeNode* pChild = NULL;
	LinkedStack* pStackMain = NULL;
	LinkedStack* pStackSub = NULL;

	if (pAVLTree == NULL) {
		ret = FALSE;
		return ret;
	}

	pStackMain = createLinkedStack();
	pStackSub = createLinkedStack();
	if (pStackMain == NULL || pStackSub == NULL) {
		ret = FALSE;
		return ret;
	}

	pParentNode = NULL;
	pDelNode = pAVLTree->pRootNode;
	while(pDelNode != NULL) {
		if (key == pDelNode->data.key) {
			break;
		}
		pParentNode = pDelNode;
		pushAVLTreeNode(pStackMain, pParentNode);

		if (key < pDelNode->data.key) {
			pDelNode = pDelNode->pLeftChild;
		}
		else {
			pDelNode = pDelNode->pRightChild;
		}
	}
	if (pDelNode == NULL) {
		printf("����,�˻� Ű[%d]�� �ڷᰡ �����ϴ�,deleteNodeAVL()\n", key);
		ret = FALSE;
		return ret;
	}

	if (pDelNode->pLeftChild == NULL && pDelNode->pRightChild == NULL) {
		if (pParentNode != NULL) {
			if (pParentNode->pLeftChild == pDelNode) {
				pParentNode->pLeftChild = NULL;
			}
			else {
				pParentNode->pRightChild = NULL;
			}
		}
		else {
			pAVLTree->pRootNode = NULL;
		}
	}
	else if (pDelNode->pLeftChild != NULL && pDelNode->pRightChild != NULL) {
		pPredecessor = NULL;
		pSuccessor = pDelNode->pLeftChild;
		pushAVLTreeNode(pStackSub, pSuccessor);

		while(pSuccessor->pRightChild != NULL) {
			pPredecessor = pSuccessor;

			pSuccessor = pSuccessor->pRightChild;
			pushAVLTreeNode(pStackSub, pSuccessor);
		}
		pushAVLTreeNode(pStackMain, popAVLTreeNode(pStackSub));

		if (pPredecessor != NULL) {
			pPredecessor->pRightChild = pSuccessor->pLeftChild;
			pSuccessor->pLeftChild = pDelNode->pLeftChild;

			pushAVLTreeNode(pStackSub, pPredecessor->pRightChild);
		}
		pSuccessor->pRightChild = pDelNode->pRightChild;

		if (pParentNode != NULL) {
			if (pParentNode->pLeftChild == pDelNode) {
				pParentNode->pLeftChild = pSuccessor;
			}
			else {
				pParentNode->pRightChild = pSuccessor;
			}
		}
		else {
			pAVLTree->pRootNode = pSuccessor;
		}
	}
	else {
		if (pDelNode->pLeftChild != NULL) {
			pChild = pDelNode->pLeftChild;
		}
		else {
			pChild = pDelNode->pRightChild;
		}

		if (pParentNode != NULL) {
			if (pParentNode->pLeftChild == pDelNode) {
				pParentNode->pLeftChild = pChild;
			}
			else {
				pParentNode->pRightChild = pChild;
			}
		}
		else {
			pAVLTree->pRootNode = pChild;
		}
	}
	free( pDelNode );

	balanceAVLTree(pAVLTree, pStackSub);
	balanceAVLTree(pAVLTree, pStackMain);

	deleteLinkedStack(pStackMain);
	deleteLinkedStack(pStackSub);

	return ret;
}

// Ʈ���� ����
void deleteAVLTree(AVLTree* pAVLTree)
{
	if (pAVLTree != NULL) {
		deleteAVLTreeNode(pAVLTree->pRootNode);
		free(pAVLTree);
	}
}

// Ʈ�� ����� ����(�����)
void deleteAVLTreeNode(AVLTreeNode* pAVLTreeNode)
{
	if (pAVLTreeNode != NULL) {
		deleteAVLTreeNode(pAVLTreeNode->pLeftChild);
		deleteAVLTreeNode(pAVLTreeNode->pRightChild);
		free(pAVLTreeNode);
	}
}

void displayAVLTree(AVLTree *pTree)
{
	displayAVLTreeInternal(pTree->pRootNode, 0, ' ');
}

void displayAVLTreeInternal(AVLTreeNode *pTreeNode, int level, char type)
{
    int i = 0;
	for (i = 0; i < level ; i++) {
		printf("    ");
	}

	if (pTreeNode != NULL) {
		printf("-[%i,%i,%c],%i-%s\n", pTreeNode->height, pTreeNode->balance, type, 
			pTreeNode->data.key, pTreeNode->data.value);

		displayAVLTreeInternal(pTreeNode->pLeftChild, level + 1, 'L');
		displayAVLTreeInternal(pTreeNode->pRightChild, level + 1, 'R');
	}
	else {
		printf("NULL\n");
	}
}
