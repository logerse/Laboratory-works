#include "my_lab.h"
#include <stdlib.h>
#include <assert.h>


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


int main(int argc, char **argv)
{
  if(argc != 3) {
    printf("[*] Usage: %s <input.txt> <output.txt>\n", argv[0]);
    return -1;
  }

  // Copy data from file to buffer //
  FILE *file = fopen(argv[1], "r");
          if(file == NULL) {
    printf("[*] File %s doesn\'t exist.\n", argv[1]);
    return -1;
  }
  size_t fileSize = getFileSize(file);
          if(fileSize == 0) {
    printf("[*] %s is empty file.\n", argv[1]);
    return -1;
  }

  char *buffer = (char *) malloc(fileSize + 1);
  fn_memcpy(file, buffer, fileSize);
  fclose(file);
  //--------------------------------//

  // Copy data from buffer to outfile //
  enum {
    NOT_COMMENT  = 0,
    LINE_COMMENT = 1,
    TEXT_COMMENT = 2,
  } flag = NOT_COMMENT;

  char *buf = buffer;
  uint32_t storage = *buf++;
  file = fopen(argv[2], "w");
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
  free(buffer);
  fclose(file);
}*/
