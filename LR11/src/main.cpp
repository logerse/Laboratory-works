#include "my_lab.h"
#include <stdlib.h>
#include <assert.h>


int main(int argc, char **argv)
{
  if(argc != 2) {
    printf("[*] Usage: %s <main.c>\n", argv[0]);
    return -1;
  }

  FILE *main_file = fopen(argv[1],"r");
  if(main_file == NULL) {
    printf("[*] File %s doesn\'t exist.\n", argv[1]);
    return -1;
  };

  parseFile(main_file);
}
