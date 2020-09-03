#include "my_lab.h"

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef STRING_H
#define STRING_H
#include <string.h>
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

  fclose(file);
};


int deleteComments(const char * filename)
{
  char *buffer =  fileToBuffer(filename);

  if( buffer == NULL ) return -1;

  bufferToFile(buffer, filename);

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
  char *buffer = (char*) malloc(len + 1);
  char *ptr = buffer;

  while(*word && (*ptr++ = *word++))
    ;

  *ptr = 0;

  return buffer;
};

void addReadedFile(archive_t *archive, const char *filename)
{
  if(archive->count == archive->capasity) {
    archive->capasity += 10;
    archive->ptr = (char **) realloc(archive->ptr, archive->capasity * 8);
  };

  int len = getLen(filename);
  archive->ptr[archive->count++] = copyWordInDynamic(filename, len);
};

void destructArchive(archive_t *archive)
{
  for(int i=0; i<archive->count; i++)
    free(archive->ptr[i]);
  free(archive->ptr);
};

int fileIsReaded(archive_t *archive, const char *filename)
{
  for(int i=0; i<archive->count; i++) {
    if( !strcmp(archive->ptr[i], filename) )
      return 1;
  };
  return 0;
};


//-- PARSER PART --//


int findPattern(FILE * file, int whence)
{
  char includePattern[] = "#include \"";
  char *ptr = includePattern;

  fseek(file, 0, whence);

  int c = fgetc(file);
  while( !feof(file) ) {
    if( c == *ptr ) {
      while( *ptr && c == *ptr ) {
        c = fgetc(file);
        ptr++;
      };
    
      if( !*ptr && c != EOF )
        return ftell(file);
      
      ptr = includePattern;
    } else {
      c = fgetc(file);
    };
  };
  
  return -1;
};


static int getLenFileName(FILE *file, int position)
{
  fseek(file, position, SEEK_SET);
  int c = fgetc(file);
  int len = 0;
  while( !feof && c != '"' ) {
    c = fgetc(file);
    len++;
  };

  return len;
};

//---//
struct fn_struct{
    char *ptr;
    int capasity;
};
//---//

void getFileName(struct fn_struct *filename, FILE *file, int position)
{
  int len = getLenFileName(file, position);
  
  if(len >= filename->capasity) {
    filename->capasity += len + 1;
    filename->ptr = (char *)realloc(filename->ptr, filename->capasity);
  };

  fseek(file, position-1, SEEK_SET);
  int i = 0;
  int c = fgetc(file);
  while( !feof(file) ) {
    if( c == '"' ) {
      filename->ptr[i] = 0;
      break;
    };
    filename->ptr[i++] = c;
    c = fgetc(file);
  };
};


int isHeader(struct fn_struct filename)
{
  char *ptr = filename.ptr;
  while( *ptr && *ptr != '.' )
    ptr++;

  if( !*ptr )
    return 0;

  if( ptr[1] == 'h' )
    return 1;

  return 0;
};


void getCppFile(struct fn_struct *filename)
{
  char *ptr = filename->ptr;
  while( *ptr++ != '.' )
    ;
  
  int len = ptr - filename->ptr;
  if(len + 4 >= filename->capasity) {
    filename->capasity += len + 4;
    filename->ptr = realloc(filename->ptr, filename->capasity);
  };

  const char cpp[] = "cpp";
  for(int i=0; i<=3; i++) {
    ptr[i] = cpp[i];
  };
};


int parseFile(const char *FILENAME)
{
  FILE * file = fopen(FILENAME, "r");

  if(file == NULL) return -1;

  static  int __id__ = 0;
  
  puts("#-----------#");

  for(int i=0; i<__id__; i++)
    printf("  ");
  
  printf("[*] File %s open.\n", FILENAME);

  __id__++;

  struct fn_struct filename = {(char*)malloc(10), 10};

  static archive_t readedFiles = {0, 0, 0};

  int result = findPattern(file, 0);

  while( result != -1 ) {
    getFileName(&filename, file, result);
    if( fileIsReaded(&readedFiles, filename.ptr) == 0 ) {
      addReadedFile(&readedFiles, filename.ptr);
      parseFile(filename.ptr);
      if( isHeader(filename) ) {
        getCppFile(&filename);
        parseFile(filename.ptr);
      };
    };
    result = findPattern(file, result);
  };

  if( (--__id__) == 0) {
    free(filename.ptr);
    destructArchive(&readedFiles);
  };
  
  fclose(file);
  deleteComments(FILENAME);

  for(int i=0; i<__id__; i++)
    printf("  ");

  printf("[*] File %s ready.\n", FILENAME);    
  puts("#-----------#");
  return 0;
};


/*
fatcat is not basya
   ^    ^
  | O  O |
  |   T  |
  \ __^__/
*/
