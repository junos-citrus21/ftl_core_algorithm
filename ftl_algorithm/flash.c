#include "include.h"

void init(int const number)
{
	int i;
	int megabyte;
	flash data;
	FILE* fp = fopen("flash_memory.txt", "wb");

	if (fp == NULL)
	{
		printf("파일을 열 수 없습니다.\n");
		return;
	}

	if (number <= 0)
	{
		printf("명령 구문이 올바르지 않습니다.\n");
		return;
	}

	//할당할 MB : 섹터 * 블록 * 사용자 의향
	megabyte = SECTOR * BLOCK * number;

	//전부 hex값을 00으로 초기화합니다.
	memset(data.byte, 0x00, sizeof(data.byte));

	//파일의 처음으로 간다.
	fseek(fp, 0, SEEK_SET);

	//데이터를 파일에 쓴다.
	for (i = 0; i <= megabyte - 1; i++)
	{
		fwrite(&data, sizeof(data), 1, fp);
	}

	printf("%d megabytes flash memory\n", number);

	fclose(fp);
}

void flash_read(int const number)
{
	int i;
	flash data;
	FILE* fp = fopen("flash_memory.txt", "rb");

	if (fp == NULL)
	{
		printf("파일을 열 수 없습니다.\n");
		return;
	}

	if (number <= -1)
	{
		printf("명령 구문이 올바르지 않습니다.\n");
		return;
	}

	//구조체 초기화
	memset(data.byte, 0x00, sizeof(data.byte));

	//처음에서 number만큼 섹터를 이동한다.
	fseek(fp, number * sizeof(data), SEEK_SET);

	//구조체를 읽어온다.
	fread(&data, sizeof(data), 1, fp);
	printf("오프셋 : %d \n16진수 : ", number);

	for (i = 0; i <= sizeof(data.byte) - 1; i++)
	{
		printf("%2X ", data.byte[i]);
	}

	printf("\n문자열 : ");

	for (i = 0; i <= sizeof(data.byte) - 1; i++)
	{
		printf("%2c ", data.byte[i]);
	}

	printf("\n");

	fclose(fp);
}

void flash_write(int const number, const char* string, int* const write)
{
	flash data;
	FILE* fp = fopen("flash_memory.txt", "rb+");

	if (fp == NULL)
	{
		printf("파일을 열 수 없습니다.\n");
		return;
	}

	if (number <= -1)
	{
		printf("명령 구문이 올바르지 않습니다.\n");
		return;
	}

	fseek(fp, number * sizeof(data), SEEK_SET);
	fread(data.byte, sizeof(data), 1, fp);

	//데이터가 기록되어있을 경우 반환 처리
	if (data.byte[0] != 0x00)
	{
		printf("overwrite error\n");
		fclose(fp);

		return;
	}

	fseek(fp, number * sizeof(data), SEEK_SET);

	fwrite(string, strlen(string), 1, fp);
	printf("done\n");

	(*write)++;

	fclose(fp);
}

void flash_erase(int const number, int* const erase)
{
	int i;
	flash data;
	FILE* fp = fopen("flash_memory.txt", "rb+");

	if (number <= -1)
	{
		printf("명령 구문이 올바르지 않습니다.\n");
		return;
	}

	memset(data.byte, 0x00, sizeof(data.byte));

	//처음에서 number만큼 블록을 이동한다.
	fseek(fp, SECTOR * number * sizeof(data), SEEK_SET);

	for (i = 0; i <= SECTOR - 1; i++)
	{
		fwrite(&data, sizeof(data), 1, fp);
	}

	printf("%dth block erase\n", number);

	(*erase)++;

	fclose(fp);
}