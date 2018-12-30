#ifndef _STATIC_HASHING_
#define _STATIC_HASHING_

#define HASH_KEY_SIZE	30

typedef enum HashElementStatusType { EMPTY = 0, USED, DELETED  } HashElementStatus;

typedef struct HashElementType {
	char key[HASH_KEY_SIZE + 1];
	int value;
	HashElementStatus status;
} HashElement;

typedef struct HashTableType {
	int bucketSize;
	int currentElementCount;
	HashElement *pElement;
} HashTable;

// �ؽ� ���̺��� ����.
HashTable* createHashTable(int bucketSize);

// �ڷ��� �߰�.
int addElementSHT(HashTable* pHashTable, HashElement element);

// �ڷ��� ����.
int deleteElementHT(HashTable* pHashTable, char* key);

int hashFunction(char *pKey, int bucketSize);

unsigned int stringToInt(char *pKey);

int isEmptyBucket(HashElement* pElement);

int isEmptyOrDeletedBucket(HashElement* pElement);

// �ڷ��� �˻�.
HashElement* searchHT(HashTable* pHashTable, char* key);

// �ؽ� ���̺� ���� ǥ��.
void displayHashTable(HashTable *pHashTable);

// �ؽ� ���̺��� ���� �ڷ��� ����.
int getElementCountHT(HashTable *pHashTable);

// �ؽ� ���̺��� ����.
void deleteHashTable(HashTable *pHashTable);

#endif

#ifndef _COMMON_HASHING_DEF_
#define _COMMON_HASHING_DEF_

#define TRUE		1
#define FALSE		0

#endif