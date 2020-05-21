#include "my_lab.h"
#include <stdlib.h> // atof
#include <ctype.h> // isdigit

#define FAIL(code) (uint64_t)((uint64_t) (code) << 32)
#define SUCCESS(min) 0x00000000ffffffff & (min)

#define NEND(c) ((c) != EOF && (c) != '\n')
#define CLEANUP(ptr, buf)\
        (ptr) = (buf); \
        while(*(ptr)) *(ptr)++=0; \
        (ptr) = (buf);

#define IS_VALID(x) (((x) <= '9' && (x) >= '0') || ((x) == '-') || ((x) == '.'))

static Array_t getArray()
{
	int count;
	Array_t array;
	array.len = 0;
	
	puts("Input your array:");

	int c;
	char buffer[1025] = {-1};

	buffer[1024] = '\n';

    fgets(buffer, 1024, stdin);

	c = (count = 0);

	while(c < 1024 && buffer[c] != '\n')
	{
		if(IS_VALID(buffer[c]))
		{
			if( !sscanf(buffer + c, "%f", &array.arr[count++]) )
				count--;
			else
				array.len++;
			
			while(IS_VALID(buffer[c])) c++;
		} 
		else
			c++;
	};

    return array;
};


#define ADDTOARR(ptr,tmp,i)\
        *(ptr)++ = (array)->arr[(i)];\
        (tmp).len++;

static int comparF(const void *s1, const void *s2)
{
    float *ptr1 = (float *) s1;
    float *ptr2 = (float *) s2;

	return *ptr1 - *ptr2;
}

static float deleteLocalMin(Array_t *const array)
{
    Array_t tmp;
    tmp.len = 0;
    float *ptr = tmp.arr;
    float min = array->arr[0];
    for(int i=0; i<array->len ; i++)
    {
            if(min > array->arr[i])
                min = array->arr[i];

            if(i == 0){
                if(array->arr[i] > 0 && array->arr[i] >= array->arr[i+1]){
                	ADDTOARR(ptr,tmp,i);
                }
            } else if(i == array->len - 1){
                if(array->arr[i] > 0 && array->arr[i] >= array->arr[i-1]) {
        	        ADDTOARR(ptr,tmp,i);
                }
            } else {
                if(array->arr[i] >= array->arr[i-1] && array->arr[i] >= array->arr[i+1]){
                    ADDTOARR(ptr,tmp,i);
                }
            }
    }

    if(tmp.len)
        qsort(tmp.arr, tmp.len, sizeof(float), comparF);

    ptr = array->arr;
    for(int i=0; i<tmp.len; i++){
        *ptr++ = tmp.arr[i];
    }
    array->len = tmp.len;
    
    return min;
};

#undef ADDTOARR


/*
 * RESULT: is 32-bit value (global minimum) in eax. First half of rax use for error flags.
 */
uint64_t interface(Array_t *array)
{
    *array = getArray();
    float_int32_u min;

    if(array->len > 2){
        min.f = deleteLocalMin(array);
        if(array->len == 0)
            return FAIL(MAX_NONE) |  min.i;

    } else {
        return FAIL(ARRAY_EMPTY);
    }

    return SUCCESS(min.i); // Success
}


void printResult(Array_t arr, float glbMin)
{
    printf("Result: ");
    for(int i=0; i<arr.len; i++)
    {
        printf("%f ", arr.arr[i]);
    }
    printf("\nGlobal minimum is %0.2f\n", glbMin);
}
