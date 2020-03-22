#include "my_lab.h"

int main(int argc, char **argv)
{
    if(argc == 1) {
        printf("[*] Usage: %s {num}\n", argv[0]);
        return -1;
    }

    uint64_t result = inverse(argv[1]);
    printf("Result: %lu\n", result);
}
