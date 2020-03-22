#include "my_lab.h"
#include <stdio.h>

#define CHECK_ERROR(res) (res) >> 32 

int main() {
	Array_t arr;
	uint64_t result = interface(&arr);
	
	switch(CHECK_ERROR(result)) {
		case MAX_NONE:
			printf("Maximums doesn\'t exists.\n");
			printf("Global minimum is %0.2f.\n", *(float *) &result);
			return -1;

		case ARRAY_EMPTY:
			printf("Array is empty.\n");
			return -1;
	};

	printf("Result: ");
	for(int i=0; i<arr.len; i++)
		printf("%0.2f ", arr.arr[i]);
	printf("\n");
	printf("Global minimum: %0.2f\n", *(float *) &result);
}
