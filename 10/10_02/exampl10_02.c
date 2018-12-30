#include <stdio.h>
#include <stdlib.h>
#include "seqindexsearch.h"

// �迭�� ������ ���.
void showArray(int value[], int size)
{
	int i = 0;

	printf("��ġ,Ű��\n");
	printf("------------\n");
	for(i = 0; i < size; i++) {
		printf("%d,%d\n", i, value[i]);
	}
}

int main(int argc, char *argv[])
{
	IndexTable* pIndexTable = NULL;
	int indexSize = 3;
	int index = 0;
	int key = 0;
	int ascSortedArray[] = {10, 20, 50, 60, 70, 80};
	int arraySize = 6;

	showArray(ascSortedArray, arraySize);
	pIndexTable = createIndexTable(ascSortedArray, arraySize, indexSize);
	if (pIndexTable != NULL) {
		showIndexTable(pIndexTable, indexSize);

		key = 60;
		index = sequentialIndexSearch(ascSortedArray, arraySize, pIndexTable, indexSize, key);
		if (index >= 0) {
			printf("Ű-%d,��ġ-%d\n", key, index);
		}
		else {
			printf("Ű-%d,�˻� ����\n", key);
		}

		key = 65;
		index = sequentialIndexSearch(ascSortedArray, arraySize, pIndexTable, indexSize, key);
		if (index >= 0) {
			printf("Ű-%d,��ġ-%d\n", key, index);
		}
		else {
			printf("Ű-%d,�˻� ����\n", key);
		}

		free(pIndexTable);
	}

	return 0;
}
