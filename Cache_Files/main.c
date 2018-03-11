#include <math.h>
#include <unistd.h>
#include "cache.h"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
	return 1;
    }

    /* get from user */

    cache_ways = 0;  //2^3
    byte_select = 6;
    cache_index = 8;
    cache_tag = BIN - (cache_index + byte_select);
   
    /* variables */

    /* TESTING */
    int tag_bits[cache_tag];
    int index_bits[cache_index];
    int bs_bits[byte_select];

    //hex values
    unsigned int hex_tag;
    unsigned int hex_index;
    unsigned int hex_bs;
    //cache index
    int cache_location;
    //trace address
    char hex_address_str[HEX];
    unsigned int hex_address_us;
    int binary_address[BIN];
    //all possible cache lines (array)
    double cache_sets_max = pow(2,cache_index); 
    struct cache_set s_cache[(int)cache_sets_max];
     
    cache_startup(s_cache, cache_sets_max,
		  (int)pow(2,cache_ways));
 
    /* read in access file here */
    FILE *fp = fopen(argv[1], "r");
    if(!fp)
    {
	return 1;
    }
    char buffer[50];
    while(fgets(buffer,50,fp) != NULL)
    {
	printf("Trace: %s\n",buffer);
	//store r/w bit
        sscanf(&buffer[0],"%d",&r_w_bit);    
	for(int i = 2; i < (HEX + 2); i++)
	{
		//store hex address string
		hex_address_str[i-2] = buffer[i];
	}
	hex_address_str[HEX] = '\0';	
	
        //store hex address as us_int
        hex_address_us = (unsigned int)strtol(hex_address_str,
        		  NULL,16);
	
	//retrieve tag/index/byte select
        get_tag_bits_hex(&hex_address_us, &hex_tag,&hex_index,
                         &hex_bs, cache_index, byte_select);
   	
        printf("Hex Add: %x\n",hex_address_us); 
        printf("Hex Tag: %x\n",hex_tag); 
        printf("Hex Ind: %x\n",hex_index); 
        printf("Hex  BS: %x\n",hex_bs); 
	
	/*
	hex_to_bin(hex_address_str,binary_address,HEX);
	get_tag_bits(binary_address, tag_bits, index_bits,
		     bs_bits, cache_tag, cache_index,
	             byte_select);	
	*/
	
        //store set location as integer
        printf("Cache location: %d\n",
	        (int)hex_index);  
	
        /* start checking r/w, miss/hit behavior */
        if(r_w_bit == 0)
	{
		printf("READ!\n");
		cache_read(s_cache, hex_tag, (int)hex_index,
			   (int)pow(2,cache_ways));
		++cache_reads;
	}
	else
	{
		printf("WRITE!\n");
		cache_write(s_cache, hex_tag, (int)hex_index,
			    (int)pow(2,cache_ways));
		++cache_writes;
	}
 

	++cache_accesses;
        printf("\n");
    }
    fclose(fp);

    cache_hit_ratio = (cache_hits/(float)cache_accesses)
		       *100;
    cache_miss_ratio = (cache_misses/(float)cache_accesses)
			*100;
	
    printf("CACHE PARAMETERS\n");
    printf("Number of Sets: %d\n", (int)cache_sets_max);
    printf("Associativity: %d\n", (int)pow(2,cache_ways));
    printf("Cache Line Size: %d\n\n", (int)pow(2,byte_select));
    printf("CACHE STATISTICS\n");
    printf("Total Number of Cache Accesses: %d\n", 
	    cache_accesses);
    printf("Number of Cache Reads: %d\n", cache_reads);
    printf("Number of Cache Writes: %d\n", cache_writes);
    printf("Number of Cache Hits: %d\n", cache_hits);
    printf("Number of Cache Misses: %d\n", cache_misses);
    printf("Cache Hit Ratio: %.2f%\n", cache_hit_ratio);
    printf("Cache Miss Ratio: %.2f%\n", cache_miss_ratio);
    printf("Number of Evictions: %d\n", cache_evictions);
    printf("Number of Writebacks: %d\n\n", cache_writebacks);

    return 0;

}
