#include "my_lab.h"
#include <stdlib.h> // atoi  exit
#include <ctype.h> // isdigit

#define MASK 0x8888888888888888


static inline int checkNum(const char *buf)
{
	return 1;
    while(*buf && (isdigit(*buf) | *buf == '-'))
        *buf++;
    return !*buf;
};


uint64_t inverse(const char *buf)
{
    if( checkNum(buf) == 0 ) {
        printf("[X] Incorrect input.\n");
        exit(-1);
	}
    
    uint64_t tmp;
	sscanf(buf, "%lu", &tmp);

#ifndef MASK
    uint32_t mask = 0x8;
    
    while(mask && tmp >= mask) {
        tmp ^= mask;
        mask <<= 4;
    }
#else
	tmp ^= MASK;	
#endif
    
    return tmp;
};
