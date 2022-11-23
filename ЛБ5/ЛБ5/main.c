#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 1000

int readFile(const char* filename, char buffer[], int bufLen) {
	FILE* fp = fopen(filename, "r");
	int len;

	if (fp != NULL) {
		len = fread(buffer, 1, bufLen, fp);
		buffer[len] = '\0';
		fclose(fp);
		return len;
	}
	else {
		printf("Error when open a file!");
	}
	return -1;
}

int file1GetKeyCount(char* buffer, int len, int *i) {
	int a = 0;
	for (; a < len; a++) {
		if (buffer[a] == '\n')
			break;
	}
	*i = a;
	char* strNum = (char*)malloc(sizeof(char) * a);
	memcpy(strNum, &buffer[0], a);
	strNum[a] = '\0';

	return atoi(strNum);
}

char** fileSplit(char* buffer, int len, int keyCount) {
	char** keyArr = malloc(sizeof(char) * 15 * keyCount);
	for (int j = 0; j <= len; j += 16) {
		char* substr = malloc(11);
		strncpy(substr, buffer + j, 15);
		substr[15] = '\0';
		int arrInd = j / 16;
		keyArr[arrInd] = malloc(sizeof(char) * 15);
		keyArr[arrInd] = substr;
	}
	return keyArr;
}

char** file1Split(int* count) {
	char buffer[BUF_LEN];
	int len = readFile("files/file1.txt", buffer, BUF_LEN);
	int i = 0;
	int keyCount = file1GetKeyCount(buffer, len, &i);
	strncpy(buffer, buffer + i+1, strlen(buffer));
	char** keyArr = fileSplit(buffer, len, keyCount);
	*count = keyCount;
	return keyArr;
}

char** file2Split(int* count) {
	char buffer[BUF_LEN];
	int len = readFile("files/file2.txt", buffer, BUF_LEN);
	int keyCount = (int)(len / 15.);
	char** keyArr = fileSplit(buffer, len, keyCount);
	*count = keyCount;
	return keyArr;
}

void printArrStr(char** arr, int len) {
	for (int i = 0; i < len; i++) {
		printf("%s|\n", arr[i]);
	}
}

void main() { // fseek to get file length
	int keys1Count = 0;
	int keys2Count = 0;
	char** keys1 = file1Split(&keys1Count);
	char** keys2 = file2Split(&keys2Count);

	int* countArr = malloc(sizeof(int) * keys2Count);
	for (int i = 0; i < keys2Count; i++) {
		for (int j = 0; j < keys1Count; j++) {
			if (strcmp(keys1[j], keys2[i]) == 0) 
				countArr[i] = j;

		}
	}

	for (int i = 0; i < keys2Count; i++) {
		printf("%d\n", countArr[i]);
	}
}