#include <math.h>
#include "cache.h"

int main()
{
    /* get from user */
    cache_ways = 3;  //2^3
    byte_select = 7;
    cache_index = 10 - cache_ways;
    cache_tag = BIN - (cache_index + byte_select + cache_ways);
   
    /* variables */
    int tag_bits[cache_tag];
    int index_bits[cache_index];
    int bs_bits[byte_select];
    unsigned int hex_tag;
    unsigned int hex_index;
    unsigned int hex_bs;
    int cache_location;
    char hex_address_str[HEX];
    unsigned int hex_address_us;
    int binary_address[BIN];
    double cache_sets_max = pow(2,cache_index); 
    struct cache_set s_cache[(int)cache_sets_max];
    printf("Sets: %d\n",(int)cache_sets_max);

    /* read in access file here */
    strcpy(hex_address_str,"A0056FB9");
    /* need function for this */
    hex_address_us = (unsigned int)strtol(hex_address_str,NULL,16);
    printf("New Val: %x\n",hex_address_us);
    get_tag_bits_hex(&hex_address_us,&hex_tag,&hex_index,&hex_bs,
		     cache_index,byte_select);
   	
    printf("Hex Add: %x\n",hex_address_us); 
    printf("Hex Tag: %x\n",hex_tag); 
    printf("Hex Ind: %x\n",hex_index); 
    printf("Hex  BS: %x\n",hex_bs); 
    
/*  JUST FOR TESTING

    hex_to_bin(hex_address_str,binary_address,HEX);
    print_address(hex_address_str,binary_address);
    get_tag_bits(binary_address,tag_bits,index_bits,bs_bits,
		 cache_tag,cache_index,byte_select);
*/
    cache_location = get_cache_index_value(&hex_index);
    printf("Cache loc: %d\n",cache_location);    

    /* store into a cache set */
    s_cache[cache_location].valid[0] = 1;
    s_cache[cache_location].dirty[0] = 0;
    s_cache[cache_location].tag[0] = &hex_tag;
    s_cache[cache_location].tag[1] = &hex_tag;
    s_cache[cache_location].tag[2] = &hex_tag;
    s_cache[cache_location].tag[3] = &hex_tag;

    /* print contents of cache set */
    print_cache_set(s_cache,cache_location,pow(2,cache_ways));
 
    return 0;

}
