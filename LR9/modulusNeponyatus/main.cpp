#include <stdio.h>
#include <limits.h>
#include "my_lab.h"

#define CHECK(num) ((num) >= 0 && (num) <= INT_MAX)

int main(const int argc, const char **argv)
{
	if( argc != 3 )
	{
		printf("[*] Usage: %s <MOD> <NUM>\n", argv[0]);
		return -1;
	};

	int N;
	uint32_t MOD;
	
	sscanf(argv[1],"%d", &MOD);
	sscanf(argv[2],"%d", &N);
	
	if( !CHECK(N) ) 
	{
		printf("[!] NUM must belong to the interval from 0 to %d", INT_MAX);
		return -1;
	};
	printf("Result: %d\n", getMod(MOD, N));
};
