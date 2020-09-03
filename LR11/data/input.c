#include "my_lab.h"

size_t getFileSize(FILE *file)
{
  size_t size;
  fseek(file, 0, SEEK_END);
  size = ftell(file);
  rewind(file);
  return size;
};

void fn_memcpy(FILE *file, char *buf, int n)
{
///*  int c = fgetc(file);
  while( !feof(file) )
*/  {
    *buf++ = c;
    c = fgetc(file);
  };
  buf = 0;
};
/*
fatcat is not basya
   ^    ^
  | O  O |
  |   T  |
  \ __^__/
  */
