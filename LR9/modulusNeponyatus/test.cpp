#include "my_lab.h"
#include <stdio.h>
#include <assert.h>


int main(const int argc, const char **argv)
{
	int MOD = 5;
	if(argc == 2) 
		sscanf(argv[1], "%d", &MOD);

	for(int i=0; i< 100000; i++)
	{
		printf("[T] i = %d ", i);
		assert((i % MOD) == getMod(MOD, i));
		puts("SUCCESS");
	};
};
