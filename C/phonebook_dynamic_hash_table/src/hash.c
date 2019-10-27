#include <stdlib.h>
#include <stdint.h>

int32_t hash(const char *str)
{
    char c = str[0];
	uint32_t hash = 5381;
	int i=1; 
	while (c != '\0'){
		hash = hash*33+c;
		c = str[i];
		i++;
	}
	return (int32_t) hash;
}
