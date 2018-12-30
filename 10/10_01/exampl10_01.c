#include <stdio.h>
#include <stdlib.h>
#include "seqsearch.h"

int main(int argc, char *argv[])
{
	int index = 0;
	int key = 0;
	int notSortedArray[] = {80, 50, 70, 10, 60, 20};
	int ascSortedArray[] = {10, 20, 50, 60, 70, 80};

	// 1. ���ĵǾ� ���� ���� ���.
	showArray(notSortedArray, 6);

	// 1-1.�˻� ������ ���: Ű �� 70.
	key = 70;
	index = sequentialSearchNotSorted(notSortedArray, 6, key);
	if (index >= 0) {
		printf("Ű-%d,��ġ-%d\n", key, index);
	}
	else {
		printf("Ű-%d,�˻� ����\n", key);
	}

	// 1-2.�˻� ������ ���: Ű �� 25.
	key = 25;
	index = sequentialSearchNotSorted(notSortedArray, 6, key);
	if (index >= 0) {
		printf("Ű-%d,��ġ-%d\n", key, index);
	}
	else {
		printf("Ű-%d,�˻� ����\n", key);
	}

	// 2. ���ĵǾ� �ִ� ���.
	showArray(ascSortedArray, 6);

	// 2-1.�˻� ������ ���: Ű �� 70.
	key = 70;
	index = sequentialSearchAsendingSorted(ascSortedArray, 6, key);
	if (index >= 0) {
		printf("Ű-%d,��ġ-%d\n", key, index);
	}
	else {
		printf("Ű-%d,�˻� ����\n", key);
	}

	// 2-2.�˻� ������ ���: Ű �� 25.
	key = 25;
	index = sequentialSearchAsendingSorted(ascSortedArray, 6, key);
	if (index >= 0) {
		printf("Ű-%d,��ġ-%d\n", key, index);
	}
	else {
		printf("Ű-%d,�˻� ����\n", key);
	}

	return 0;
}
