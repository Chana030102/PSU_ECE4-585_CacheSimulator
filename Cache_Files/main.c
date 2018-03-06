#include <math.h>
#include "cache.h"

int main()
{
    /* get from user */
    cache_ways = 8;
    byte_select = 7;
    cache_index = 10;
    cache_tag = BIN - (cache_index + byte_select);
   
    /* variables */
    int tag_bits[cache_tag];
    int index_bits[cache_index];
    int bs_bits[byte_select];
    char hex_address[HEX];
    int binary_address[BIN];
    double cache_sets_max = pow(2,cache_index); 
    struct cache_set s_cache[(int)cache_sets_max];
    printf("Sets: %d\n",(int)cache_sets_max);

    /* read in access file here */
    strcpy(hex_address,"A0056FB9");

    hex_to_bin(hex_address,binary_address,HEX);
    print_address(hex_address,binary_address);
    get_tag_bits(binary_address,tag_bits,index_bits,bs_bits,
		 cache_tag,cache_index,byte_select);
    
    /* store into a cache set */
    s_cache[500].valid[0] = 1;
    s_cache[500].dirty[0] = 0;
    s_cache[500].tag[0] = tag_bits;

    //fix storing tag in cache set
    print_cache_set(s_cache,500,0);
 
    return 0;

}
