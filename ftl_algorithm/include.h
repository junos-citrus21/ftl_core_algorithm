#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE (0)
#define TRUE (1)
#define SECTOR (32) //1개의 블록은 32개 섹터로 구성
#define BLOCK (64)
#define MAX (512) //기본적으로 1섹터는 512byte이다.
#define SIZE (32) //크기 줄이기

typedef struct _flash {
	char byte[MAX / SIZE];
} flash;

void init(int const);
void flash_read(int const);
void flash_write(int const, const char*, int* const);
void flash_erase(int const, int* const);
void count(int* const, int* const);
void help();