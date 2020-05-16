#include <stdio.h>
#define BUF_SIZE 100

void getFileName(char *buf);
void copyFile(FILE *_in, FILE *_out, const int _in_size);
void getFileSize(FILE *file, int *fileSize);
