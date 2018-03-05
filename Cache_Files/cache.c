
/* place cache functions in here */

/* # includes */

#include "cache.h"

/* macros */

/* global variables */

/* cache functions */

int get_byte_select(int* bin_address,int* byte_sel_tag,
		    int byte_sel_size)
{
for(int i = 31; i > (31 - byte_sel_size); i--)
{
	byte_sel_tag[i-25] = bin_address[i];
}
return 0;
}

int hex_to_bin(char* hex, int* binary,int size)
{
int j = 0;

for(int i = 0; i < size; i++)
{
	j = i*4;

	switch(hex[i])
	{
	case '0':
		binary[j]   = 0;
		binary[j+1] = 0;
		binary[j+2] = 0;
		binary[j+3] = 0;
		break;
	case '1':
		binary[j]   = 0;
		binary[j+1] = 0;
		binary[j+2] = 0;
		binary[j+3] = 1;
		break;
	case '2':
		binary[j]   = 0;
		binary[j+1] = 0;
		binary[j+2] = 1;
		binary[j+3] = 0;
		break;
	case '3':
		binary[j]   = 0;
		binary[j+1] = 0;
		binary[j+2] = 1;
		binary[j+3] = 1;
		break;

	case '4':
		binary[j]   = 0;
		binary[j+1] = 1;
		binary[j+2] = 0;
		binary[j+3] = 0;
		break;
	case '5':
		binary[j]   = 0;
		binary[j+1] = 1;
		binary[j+2] = 0;
		binary[j+3] = 1;
		break;
	case '6':
		binary[j]   = 0;
		binary[j+1] = 1;
		binary[j+2] = 1;
		binary[j+3] = 0;
		break;
	case '7':
		binary[j]   = 0;
		binary[j+1] = 1;
		binary[j+2] = 1;
		binary[j+3] = 1;
		break;
	case '8':
		binary[j]   = 1;
		binary[j+1] = 0;
		binary[j+2] = 0;
		binary[j+3] = 0;
		break;
	case '9':
		binary[j]   = 1;
		binary[j+1] = 0;
		binary[j+2] = 0;
		binary[j+3] = 1;
		break;
	case 'A':
		binary[j]   = 1;
		binary[j+1] = 0;
		binary[j+2] = 1;
		binary[j+3] = 0;
		break;
	case 'B':
		binary[j]   = 1;
		binary[j+1] = 0;
		binary[j+2] = 1;
		binary[j+3] = 1;
		break;
	case 'C':
		binary[j]   = 1;
		binary[j+1] = 1;
		binary[j+2] = 0;
		binary[j+3] = 0;
		break;
	case 'D':
		binary[j]   = 1;
		binary[j+1] = 1;
		binary[j+2] = 0;
		binary[j+3] = 1;
		break;	
	case 'E':
		binary[j]   = 1;
		binary[j+1] = 1;
		binary[j+2] = 1;
		binary[j+3] = 0;
		break;
	case 'F':	
		binary[j]   = 1;
		binary[j+1] = 1;
		binary[j+2] = 1;
		binary[j+3] = 1;
		break;
	default:
		printf("Invalid Value: Hex to Bin\n");
        }
}

return 0;
} 

int test_struct(struct cache_set* s_cache)
{	
	s_cache[0].valid[0] = 1;
	s_cache[0].dirty[0] = 1;
	s_cache[0].tag[0] = "ABCDEFG";
return 0;
}

int print_struct(struct cache_set* s_cache)
{
	printf("cache valid = %d\n",s_cache[0].valid[0]);
	printf("cache dirty = %d\n",s_cache[0].dirty[0]);
	printf("cache tag = %s\n",s_cache[0].tag[0]);
return 0;
}

