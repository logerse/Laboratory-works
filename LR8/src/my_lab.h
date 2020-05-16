#include <stdint.h>
#include <stdio.h>

#define ARR_SIZE 1024
#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0

// ERRORS
#define MAX_NONE 1
#define ARRAY_EMPTY 2

typedef struct {
    float arr[ARR_SIZE];
    uint16_t len;
} Array_t;

typedef union {
    float f;
    uint32_t i;
} float_int32_u;


// foo.c
uint64_t interface(Array_t *);
void printResult(Array_t , float);


//test.c

