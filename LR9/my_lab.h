#include <stdint.h>
#include <stdio.h>

#define INCORRECT_NUM 0x100000000

#define CHECK_EFLAG(val) ((val) >> 32)
#define SET_EFLAG(eflag, val) ((val) |= ((uint64_t) (eflag)))
#define GET_VAL(val) (*(int *) &(val))

uint64_t inverse(const char *);
