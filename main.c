#include <math.h>
#include "cache.h"

int main()
{
/* get from user */
cache_ways = 8;
byte_select = 7;
cache_index = 10;

int cache_tag = 32 - (cache_index + byte_select);
double cache_sets_max = pow(2,cache_index);
printf("Sets: %d\n",(int)cache_sets_max);

/* variables */
int bs_bits[byte_select];
char hex_address[HEX];
int binary_address[BIN];
struct cache_set s_cache[(int)cache_sets_max];

strcpy(hex_address,"A0056FB9");

hex_to_bin(hex_address,binary_address,HEX);
get_byte_select(binary_address,bs_bits,byte_select);
test_struct(s_cache);
print_struct(s_cache);

printf("Hex: %s\n",hex_address);
printf("Binary: ");
for(int i = 0; i < BIN; i++)
{	
	printf("%d",binary_address[i]);
}
	printf("\n");
for(int i = 0; i < byte_select; i++)
{
	printf("%d",bs_bits[i]);
}
	printf("\n");
return 0;

}
