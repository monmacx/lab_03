#ifndef FILE_READ_H
#define FILE_READ_H

#include <stdio.h>
#include <stdlib.h>

struct file_info
{
	char * content;
	int size;
};

struct file_info read_file(char * file_name);
#endif