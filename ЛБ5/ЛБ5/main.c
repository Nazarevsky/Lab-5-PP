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

char* sliceStr(char buffer[], int start, int end) {
	char* str = (char*)malloc(sizeof(char) * (end - start));
	memcpy(str, &buffer[start], end);
	str[(end - start)] = '\0';
	return str;
}

void file1Split() {

}

void main() {
	char buffer[BUF_LEN];
	int len = readFile("files/file1.txt", buffer, BUF_LEN);

	// finding num in file
	int i = 0;
	for (; i < len; i++) {
		if (buffer[i] == '\n')
			break;
	}

	int keyCount = atoi(sliceStr(buffer, 0, i));

	char** keyArr = malloc(sizeof(char) * 15 * keyCount);
	i += 16;
	for (; i < len; i+=16) {
		//printf("%c", buffer[i]);
		printf(sliceStr(buffer, i-16, i));
	}
}