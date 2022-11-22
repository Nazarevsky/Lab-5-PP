#include <stdio.h>
#include <string.h>

#define BUF_LEN 1000

void readFile(const char* filename, char buffer[], int bufLen) {
	FILE* fp = fopen(filename, "r");
	int len;

	if (fp != NULL) {
		len = fread(buffer, 1, bufLen, fp);
		buffer[len] = '\0';
		fclose(fp);
	}
	else {
		printf("Error when open a file!");
	}
}

void main() {
	char buffer[BUF_LEN];
	readFile("files/file1.txt", buffer, BUF_LEN);
	printf(buffer);
}