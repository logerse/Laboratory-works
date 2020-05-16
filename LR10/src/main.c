#include "my_lab.h"
#include <stdint.h>
#include <assert.h>

#define ERROR_EXIT(s) puts((s)); return -1

int main()
{
  char fileName[BUF_SIZE] = {0};

//-------//

  printf("[*] Input file name:\n");
  getFileName(fileName);
  FILE *fileIn = fopen(fileName,"r");
  if(fileIn == NULL)
  {
    ERROR_EXIT("[X] File doesn\'t exists.");
  }

  int fileSize;
  getFileSize(fileIn, &fileSize);
  if( fileSize == 0 ) 
  {	
    fclose(fileIn);
    ERROR_EXIT("[X] Input file is empty.");
  };

//-------//

  printf("[*] New file name:\n");
  getFileName(fileName);
  FILE *fileOut = fopen(fileName, "w");
  if( fileOut == NULL ) 
  { 
    ERROR_EXIT("[X] Incorrect output path."); 
  };

  copyFile(fileOut, fileIn, fileSize);

  fclose(fileOut);
};
