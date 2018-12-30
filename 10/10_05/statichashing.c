#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashingdef.h"
#include "hashinglinkedlist.h"
#include "statichashing.h"

int addLLElementLast(LinkedList* pList, HashElement element)
{
	int ret = FALSE;
	ListNode node = {0,};
	int position = 0;
	if (pList != NULL) {
		int position = getLinkedListLength(pList);
		node.data = element;
		ret = addLLElement(pList, position, node);
	}
	return ret;
}


// �ؽ� ���̺��� ����.
HashTable* createHashTable(int bucketSize)
{
	HashTable *pReturn = NULL;
	int i = 0, j = 0;

	if (bucketSize <= 0) {
		printf("���� ũ��� 0���� Ŀ�� �մϴ�\n");
		return NULL;
	}

	pReturn = (HashTable *)malloc(sizeof(HashTable));
	if (pReturn != NULL) {
		memset(pReturn, 0, sizeof(HashTable));
		pReturn->bucketSize = bucketSize;
	}
	else {
		printf("����, ù��° malloc(), createHashTable()\n");
		return NULL;
	}

	pReturn->ppElement = (LinkedList **)malloc(sizeof(LinkedList*) * bucketSize);
	if (pReturn->ppElement != NULL) {
		memset(pReturn->ppElement, 0, sizeof(LinkedList*) * bucketSize);

		for(i = 0; i < bucketSize; i++) {
			pReturn->ppElement[i] = createLinkedList();
			if (pReturn->ppElement[i] == NULL) {
				for(j = 0; j < i-1; j++) {
					if (pReturn->ppElement[j] != NULL) free(pReturn->ppElement[j]);
				}
				if (pReturn->ppElement != NULL) free(pReturn->ppElement);
				if (pReturn != NULL) free(pReturn);
				break;
			}
		}
	}
	else {
		if (pReturn != NULL) free(pReturn);
		printf("����, �ι�° malloc(), createHashTable()\n");
		return NULL;
	}

	return pReturn;	
}

// �ڷ��� �߰�.
int addSHT(HashTable* pHashTable, HashElement element) {
	int ret = FALSE;
	LinkedList* pList = NULL;
	if (pHashTable != NULL) {
		pList = searchBucket(pHashTable, element.key);
		if (pList != NULL) {
			addLLElementLast(pList, element);
			pHashTable->currentElementCount++;
			ret = TRUE;
		}
		else {
			printf("����, �߸��� �ؽ� ���̺� �ּҰ� ���Ǿ����ϴ�, addSHT()\n");
		}
	}

	return ret;
}

LinkedList* searchBucket(HashTable* pHashTable, char* key) {
	LinkedList* pReturn = NULL;
	int bucketIndex = 0;

	if (pHashTable != NULL) {
		bucketIndex = hashFunction(key, pHashTable->bucketSize);
		if (bucketIndex >= 0) {
			pReturn = pHashTable->ppElement[bucketIndex];
		}
		else {
			printf("����, �߸��� �ؽ� ���̺� �ּҰ� ���Ǿ����ϴ�, searchHT()\n");
		}
	}

	return pReturn;
}

int hashFunction(char *pKey, int bucketSize) {
	int ret = -1;
	unsigned int temp_key = 0;

	if (pKey == NULL) {
		return ret;
	}

	temp_key = stringToInt(pKey);
	if (bucketSize > 0) {
		ret = temp_key % bucketSize;
	}

	return ret;
}

// ���ڿ��� ���ڷ� ��ȯ.
unsigned int stringToInt(char *pKey) {
	unsigned int ret = 0;
	while(*pKey != '\0') {
		ret = (ret * 31) + (*pKey);
		*pKey++;
	}
	if (ret < 0) {
		ret = ret * (-1);
	}

	return ret;
}

// �ڷ��� �˻�.
HashElement* searchHT(HashTable* pHashTable, char* key) {
	HashElement* pReturn = NULL;
	LinkedList* pList = NULL;
	int position = 0;

	pList = searchBucket(pHashTable, key);
	if (pList != NULL) {
		pReturn = searchSlot(pList, key, &position); 
	}

	return pReturn;
}

HashElement* searchSlot(LinkedList* pList, char* key, int* pPosition) {
	HashElement* pReturn = NULL;
	HashElement *pElement = NULL;
	ListNode* pNode = NULL;
	int position = 0;

	if (pList != NULL && pPosition != NULL) {
		pNode = getLLElement(pList, 0);

		while(pNode != NULL) {
			if (strcmp(pNode->data.key, key) == 0) {
				pReturn = &(pNode->data);
				*pPosition = position;
				break;
			}
			pNode = pNode->pLink;
			position++;
		}
		if (pReturn == NULL) {
			printf("�˻� ����, �˻�Ű-[%s]�� �������� �ʽ��ϴ�, searchHT()\n", key);
		}
	}

	return pReturn;
}

// �ڷ��� ����.
int deleteElementHT(HashTable* pHashTable, char* key) {
	int ret = FALSE;
	
	HashElement *pElement = NULL;
	LinkedList* pList = NULL;
	int position = 0;

	pList = searchBucket(pHashTable, key);
	if (pList != NULL) {
		pElement = searchSlot(pList, key, &position); 
		if (pElement != NULL) {
			removeLLElement(pList, position);
			pHashTable->currentElementCount--;
			ret = TRUE;
		}
	}

	return ret;
}

// �ؽ� ���̺��� ����.
void deleteHashTable(HashTable *pHashTable) {
	int i = 0;
	if (pHashTable != NULL) {
		for(i = 0; i < pHashTable->bucketSize; i++) {
			deleteLinkedList( pHashTable->ppElement[i] );
		}
		free(pHashTable->ppElement);
	}
	free(pHashTable);
}

void displayHashTable(HashTable *pHashTable) {
	int i = 0, j = 0;
	int slotSize = 0;
	LinkedList* pList = NULL;
	ListNode* pNode = NULL;
	HashElement *pElement = NULL;

	if (pHashTable != NULL) {
		for(i = 0; i < pHashTable->bucketSize; i++) {
			printf("[%d]", i);

			pList = pHashTable->ppElement[i];

			slotSize = getLinkedListLength( pList );
			if (slotSize == 0) {
				printf(",Empty \n");
			}
			else {
				for(j = 0; j < slotSize; j++) {
					pNode = getLLElement(pList, j);
					if (pNode != NULL) {
						pElement = &(pNode->data);
						printf(",(%s, %d) ", pElement->key, pElement->value);
					}
				}
				printf("\n");
			}
		}
	}
}
