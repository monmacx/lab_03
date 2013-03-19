#include "file_read.h"

// Function for reading file
struct file_info read_file(char * file_name) 
{
 	FILE *pFile;
 	int lSize;
 	size_t result;
 	struct file_info info;

 	// Opening file
 	pFile = fopen(file_name, "r");
 	if (pFile == NULL) {
		fputs("Opening file error", stderr);
		exit(1);
  	}

	// Obtaining file size
	fseek(pFile, 0, SEEK_END);
	info.size = ftell(pFile);
	rewind(pFile);

	// Allocating memory for storing file
	info.content = (char*)malloc(sizeof(char)*info.size);
	if (info.content == NULL) {
		fputs("Memory error", stderr);
		exit(2);
	}

	// Reading file
	result = fread(info.content, 1, info.size, pFile);
	if (result != info.size) {
		fputs("Reading error", stderr);
		exit(3);
	}
	fclose(pFile);
	return info;
}
