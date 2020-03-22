#include "my_lab.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> // malloc free

#define NEND(c) ((c) != EOF && (c) != '\n')


typedef struct {
	size_t size;
	char content[0];
} line_t;


void getFileName(char *buf)
{
  int i = 0;
  int c = getchar();
  for(; i<BUF_SIZE-1; i++)
  {
    if( !NEND(c) )
      break;
    buf[i] = c;
    c = getchar();
  }
  buf[i] = 0;
};


int getLineLen(void)
{
  int lineLen = 100;
  printf("[*] Input line length [default: 100]: ");
  if( scanf("%d", &lineLen) == 0 || lineLen < 1)
	return 100;
  return lineLen;
};

/*
int getMaxLen(FILE  *file)
{
  int max = 0;
  int count = 0;
  int c = fgetc(file);
  while( !feof(file) )
  {
    if(c != '\n')
      count++;
    else
    {
      if(count > max)
        max = count;
      count = 0;
    }

    c = fgetc(file);
  }
  if(count > max)
    max = count;

  return max;
};
*/


static void
getFileSize(FILE *file, const int* fileSize)
{
	fseek(file, 0L, SEEK_END);
	*fileSize = ftell(file);
	rewind(file);
};


static const char*
loadInputFile(FILE *_in)
{
	if(_in == NULL) return NULL;
	int fileSize = 0;
	getFileSize(_in, &fileSize);
	if( fileSize == 0 ) return NULL;
	
	char c;
	char *buffer = (char*)  malloc(fileSize + 1);

	for(int $pos=0; $pos < fileSize; $pos++)
		buffer[$pos] = (isspace( c = fgetc(_in) )) c:' ';

	buffer[fileSize - 1] = 0;
	
	return (const char*) buffer;
};


void copyFile(FILE *_out, FILE *_in, const int lineLen)
{
  const char *inputBuffer = loadInputFile(_in);
  if( inputBuffer == NULL )
  {
    puts("[X] Corrupted input file.");
	exit(-1);	
  };  
  fclose(_in);

  for(int i=0; inputBuffer[i] != 0 ; i++)
  {
	if(inputBuffer[i] != 0)

  };  

  free(inputBuffer);
};

// #---------------------------------#
// #aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa#
// #aaaaaaaa aaaaaaaaaaa aaaaaaaaaaaa#
// # aaaaaaaa aaaaaaaaaaa aaaaaaaa aa#
