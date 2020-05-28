#include "my_lab.h"
#include <stdlib.h>
#include <assert.h>


int main(int argc, char **argv)
{
  if(argc != 2) {
    printf("[*] Usage: %s <main.c>\n", argv[0]);
    return -1;
  }

  parseFile(argv[1]);
}
