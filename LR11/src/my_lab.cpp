#include "my_lab.h"

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

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
  int c = fgetc(file);
  while( !feof(file) )
  {
    *buf++ = c;
    c = fgetc(file);
  };
  buf = 0;
};


static inline uint8_t refreshFlag(uint32_t data, int valOfFlag)
{
  if(valOfFlag == 0){
    switch(data)
    {
      case 0x2f2f: // is '//'
        return 1;
      case 0x2f2a: // is '/*'
        return 2;
      default:
        return 0;
    };
  }
  else if(valOfFlag == 1) {
    if( (data & 0xff) == '\n'  && (data >> 8) != '\\')
      return 3;
  }
  else if(valOfFlag == 2) {
    if( data == 0x2a2f ) // is '*/'
      return 4;
  }

  return valOfFlag;
};

static inline int getPrev(uint32_t data)
{
  return (char) (data >> 8);
};


char *fileToBuffer(const char *filename)
{
  FILE *file = fopen(filename, "r");
          if(file == NULL) {
    printf("[*] File %s doesn\'t exist.\n", filename);
    return NULL;
  }
  size_t fileSize = getFileSize(file);
          if(fileSize == 0) {
    printf("[*] %s is empty file.\n", filename);
    return NULL;
  }

  char *buffer = (char *) malloc(fileSize + 1);
  fn_memcpy(file, buffer, fileSize);
  fclose(file);

  return buffer;
};


void bufferToFile(const char *buffer, const char *fileOut)
{
  // Copy data from buffer to outfile //
  enum {
    NOT_COMMENT  = 0,
    LINE_COMMENT = 1,
    TEXT_COMMENT = 2,
  } flag = NOT_COMMENT;

  const char *buf = buffer;
  uint32_t storage = *buf++;
  FILE *file = fopen(fileOut, "w");
  while(*buf)
  {
    storage = ((storage << 8) | *buf++) & 0x0000ffff;

    switch(storage & 0xff)
    {
      case 0x2f: // is '/'
      case 0x2a: // is '*'
      case 0x0a: // is '\n'
        switch(refreshFlag(storage, flag)) {
          case 0:
            flag = NOT_COMMENT;
            break;
          case 1:
            flag = LINE_COMMENT;
            break;
          case 2:
            flag = TEXT_COMMENT;
            break;
          case 3:
            flag = NOT_COMMENT;
            continue;
          case 4:
            flag = NOT_COMMENT;
            storage = ((storage << 8) | *buf++) & 0x0000ffff;
            continue;
          default:
            break;
        };
      default:
        break;
    };

    if( !flag )
      fputc(getPrev(storage), file);
  };

  if(storage & 0xff)
    fputc((int) (storage & 0xff), file);
  //---------------------------------//

  puts("Success\n");

  fclose(file);
};


int deleteComments(const int filename)
{
  char *buffer =  fileToBuffer(argv[1]);

  if( buffer == NULL ) return -1;

  bufferToFile(buffer, argv[2]);

  free(buffer);

  return 0;
};


//-- Archive functions --//

int getLen(const char *word)
{
  int len = 0;
  while( word[len++] )
    ;
  return len;
};

char *copyWordInDynamic(const char *word, const int len)
{
  int i=0;
  char *buffer = malloc(len);
  char *ptr = buffer;

  while(*word && )

};

void addReadedFile(const char *filename, archive_t *archive)
{
  if(archive->count == archive->capasity) {
    archive->capasity *= 2;
    realloc(archive->ptr, archive->capasity * 8);
  };

  int len = getLen(filename);

};


//-- PARSER PART --//


int parseFile(const FILE *file)
{
  static archive_t readedFiles = {malloc(10*8), 0, 10};

  findPattern()
};



/*
fatcat is not basya
   ^    ^
  | O  O |
  |   T  |
  \ __^__/
  */x`
