#include <stdio.h>
#include <string.h>

struct 	student {
	char	name[20+1];
	int		year;
	float	score;
};

void main(int arc, char **argv) {
	int size = 0;

	struct student	student_hong = {"hong", 2009, 95.5};

	struct student	student_lee = {0, };
	strcpy(student_lee.name, "lee");
	student_lee.year = 2009;
	student_lee.score = 95.5;

	size = sizeof(student_hong);
	printf("����ü ���� student_hong�� ũ��: %d\n", size);
	printf("student_hong�� name: %s\n", student_hong.name);
	printf("student_hong�� year: %d\n", student_hong.year);
	printf("student_hong�� score: %f\n", student_hong.score);

	printf("student_lee�� name: %s\n", student_lee.name);
	printf("student_lee�� year: %d\n", student_lee.year);
	printf("student_lee�� score: %f\n", student_lee.score);
}
