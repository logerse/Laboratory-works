#include <stdint.h>
#include <stdio.h>

typedef struct archive {
  char **ptr;
  int count;
  int capasity;
} archive_t;

size_t getFileSize(FILE *file);
void fn_memcpy(FILE *file, char *buf, int n);
char *fileToBuffer(const char* filename);
void bufferToFile(const char *buffer, const char *filename);

int parseFile(const char *);
