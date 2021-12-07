#include <stdio.h>  
#include <inttypes.h>  


int main(int argc, char *argv[])  
{  
	uint64_t u64 = 100;  
	printf("uint64: %"PRIu64"\n", u64);  
	printf("uint64: %"PRIu64, u64);  
	// printf("uint64: %lu\n", u64);   x86_84  
	// printf("uint64: %llu\n", u64);  x86  
	return 0;  
}  
