#include <stdio.h>
#include <string.h>

void main(int arc, char **argv) {
	int size = 0;
	
	int	int_value = 100;
	int	*ptr_int = NULL;
	int	**pptr_int = NULL;

	float	float_value = 5.23f;
	float	*ptr_float = & float_value;

	char char_value_A = 'A';
	char char_value_B = 'B';
	char *ptr_char = NULL;

	ptr_int = &int_value;
	printf("���� int_value�� ��: %d\n", int_value);
	printf("������ ���� ptr_int�� ��: %x\n", ptr_int);
	printf("������ ���� ptr_int�� ����Ű�� �ּ��� ��: %d\n", *ptr_int);

	printf("���� float_value�� ��: %f\n", float_value);
	printf("������ ���� ptr_float�� ��: %x\n", ptr_float);
	printf("������ ���� ptr_float�� ����Ű�� �ּ��� ��: %f\n", *ptr_float);

	ptr_char = &char_value_A;
	printf("���� char_value_A�� ��: %c\n", char_value_A);
	printf("���� char_value_B�� ��: %c\n", char_value_B);
	printf("������ ���� ptr_char�� ��: %x\n", ptr_char);
	printf("������ ���� ptr_char�� ����Ű�� �ּ��� ��: %c\n", *ptr_char);

	*ptr_char = char_value_B;
	printf("���� char_value_A�� ��: %c\n", char_value_A);
	printf("���� char_value_B�� ��: %c\n", char_value_B);
	printf("������ ���� ptr_char�� ��: %x\n", ptr_char);
	printf("������ ���� ptr_char�� ����Ű�� �ּ��� ��: %c\n", *ptr_char);

	char_value_A = 'A';
	char_value_B = 'B';
	ptr_char = &char_value_A;
	char_value_B = *ptr_char;
	printf("���� char_value_A�� ��: %c\n", char_value_A);
	printf("���� char_value_B�� ��: %c\n", char_value_B);
	printf("������ ���� ptr_char�� ��: %x\n", ptr_char);
	printf("������ ���� ptr_char�� ����Ű�� �ּ��� ��: %c\n", *ptr_char);

	pptr_int = &ptr_int;
	printf("���� int_value�� ��: %d\n", int_value);
	printf("������ ���� ptr_int�� ��: %x\n", ptr_int);
	printf("������ ���� ptr_int�� ����Ű�� �ּ��� ��: %d\n", *ptr_int);
	printf("���� ������ ���� pptr_int�� ��: %x\n", pptr_int);
	printf("���� ������ ���� pptr_int�� ����Ű�� �ּ��� ��: %x\n", *pptr_int);
	printf("���� ������ ���� pptr_int�� ����Ű�� �ּҰ� ����Ű�� ��: %d\n", **pptr_int);
}
