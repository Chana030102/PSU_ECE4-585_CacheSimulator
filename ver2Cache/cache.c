
/* place cache functions in here */

/* # includes */

#include "cache.h"

/* macros */

/* global variables */

/* cache functions */

/*
*	Get Integer Value of Cache Location 
*	(use this to select *cache struct* index)
*
*/
int get_cache_index_value(unsigned int* index)
{
	return (int)*index;
}

/*
*	Store Tag / Index / ByteSelect 
*	as Unsigned Ints
*
*/
int get_tag_bits_hex
(
	unsigned int* hex_add,
	unsigned int* hex_tag,
	unsigned int* hex_index,
	unsigned int* hex_bs,
	int index_size,
	int bs_size
)
{
	unsigned int bs_mask = pow(2,bs_size)-1;
	unsigned int index_mask = pow(2,bs_size+index_size)-1;
	*hex_bs = (*hex_add & bs_mask);
	*hex_index = (*hex_add & index_mask) >> bs_size;
	*hex_tag = *hex_add >> (bs_size + index_size);
} 

/*
*	Store Tag / Index / ByteSelect
*	as Binary Array
*
*/
int get_tag_bits
(
	int* bin,
	int* tag_p,
	int* index_p,
	int* bs_p, 
	int tag, 
	int index, 
	int bs
)
{
	printf("Tag / Index / ByteSelect\n");
	for(int i = 0; i < tag; i++)
	{
		tag_p[i] = bin[i];
		printf("%d",tag_p[i]);
	}
	printf(" / ");
	for(int i = tag; i < (index + tag); i++)
	{
		index_p[i - tag] = bin[i];
		printf("%d",index_p[i-tag]);
	}
	printf(" / ");
	for(int i = (tag + index); i < BIN; i++)
	{
		bs_p[i-(tag+index)] = bin[i];
		printf("%d",bs_p[i-(tag+index)]);
	}
	printf("\n");
return 0;
} 

/*
*	Print Address in Hex and Binary
*
*
*/
int print_address(char* hex, int* bin)
{
	printf("Hex Address: %s\n",hex);
	printf("Binary Address: ");
	for(int i = 0; i < BIN; i++)
	{
		printf("%d",bin[i]);
	}
	printf("\n");
return 0;
}

/*
*	Converts Hex Array to Binary Int Array
*
*
*/
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

/*
*	Print Contents of Cache Set
*
*/

int print_cache_set
(
	struct cache_set* s_cache, 
	int set, 
	int ways
)
{
	printf("Cache Set[%d] Contents:\n",set);
	for(int i = 0; i < ways; i ++)
	{		
		printf("Way[%d] Valid: %d",i,
			s_cache[set].valid[i]);
		printf("  Dirty: %d", s_cache[set].dirty[i]);
		if(s_cache[set].tag[i] == NULL)
		{
			printf("  Tag: NO TAG\n");
		}
		else
		{
		printf("  Tag: %x\n", *s_cache[set].tag[i]);
		}
	}
return 0;
}

