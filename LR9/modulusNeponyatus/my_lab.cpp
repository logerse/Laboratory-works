#include "my_lab.h"
#include <math.h>

inline static uint8_t getSpecialShift(const int num)
{
	return (int) log2(num);
};


// Input: a
// a*x = 1 (mod 2**32)
// Return: x
static int32_t reverse(uint32_t num)
{
	uint32_t rslt = 1;

	for(int i=0; i < 31; i++)
	{
		rslt = (rslt * num);
		num = (num * num);
	};

	return rslt;		
};


static const char isPowerOfTwo(const uint32_t mod)
{
	const int bitCount = log2(mod);
	const int _mask = 1 << bitCount;
	return !( mod & ~_mask );
};


const uint32_t getMod(const uint32_t mod, const int num)
{
	if( isPowerOfTwo(mod) ) 
	{ return (num & (mod - 1)); }

	register const uint32_t rev_mod = reverse(mod);
	register uint64_t rax = num;
	rax = (rev_mod * rax); // imul rax, rdx
	rax = (rax >> 32); 	   // shr  rax, 32
	rax = (rax >> getSpecialShift(mod)); // shr rax, (number of significant binary digits) - 1
	
	/*
	* Next instructions in assembly is just optimized multiplication by mod
	*/
	rax = (rax * mod);
	return (num - rax);   // sub ecx, eax; mov eax,ecx; ret
};
