#include <math.h>
#include <unistd.h>
#include "cache.h"

int main(int argc, char *argv[])
{
    //Cache Variables
    int cache_ways;
    int byte_select;
    int cache_index;

    if(argc != 5)
    {
	printf("Invalid # of Parameters!\n\n"
		"Run as Follows: " 
		"./sim_cache (filename) (log2associativity) "
		"(#byte select bits) (#index bits)\n");  
	return -1;
    }
    else
    {
	cache_ways = atoi(argv[2]);
	byte_select = atoi(argv[3]);
	cache_index = atoi(argv[4]);
	
	if((cache_ways != 0) && (cache_ways != 1) &&
	   (cache_ways != 2) && (cache_ways != 3))
	{
		printf("Invalid Associativity Parameter!\n"
		        "Must be log2(1), log2(2), log2(4), or "
			"log2(8)\n");
		return -1;
	}
	else if((byte_select != 5) && (byte_select != 6) &&
		(byte_select != 7))
	{
		printf("Invalid Byte Select Parameter!\n"
			"Must be log2(32), log2(64), or "
			"log2(128)\n");
		return -1;
	}
	else if(!(cache_index < 
		 (32 - (byte_select + byte_select))))
	{
		printf("Total Cache Sets Out of Range!\n"
			"Bits Allocated to Cache are Exceeding "
			"Total Address Bits\n");
		return -1;
	}
	else
	{
		printf("\nRunning Simulation!\n\n");
	}
    }

    /* variables */

    //hex values for tag, index, byte select
    unsigned int hex_tag;
    unsigned int hex_index;
    unsigned int hex_bs;
    //trace address as string and unsigned int
    char hex_address_str[HEX];
    unsigned int hex_address_us;
    //all possible cache lines (max sets array)
    double cache_sets_max = pow(2,cache_index); 
    struct cache_set s_cache[(int)cache_sets_max];
     
    //initialize the cache at startup
    cache_startup(s_cache, cache_sets_max,
		  (int)pow(2,cache_ways));
 
    /* read in access file here */
    FILE *fp = fopen(argv[1], "r");
    if(!fp)
    {
	printf("Unable to Read from File!\n");
	return -1;
    }
    //temporary file buffer
    char buffer[50];
    while(fgets(buffer,50,fp) != NULL)
    {
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
        set_tag_ind_bs( &hex_address_us, &hex_tag, &hex_index,
                        &hex_bs, cache_index, byte_select);
   		
        /* start checking r/w, miss/hit behavior */
        if(r_w_bit == 0)
	{
		//Perform a Read Operation
		if((cache_read(s_cache, hex_tag, (int)hex_index,
			       (int)pow(2,cache_ways))) != 0)
		{
			printf("READ FAILURE!\n");
		}
		else
		{
			++cache_reads;
		}
	}
	else
	{
		//Perform a Write Operation
		if((cache_write(s_cache, hex_tag, 
				(int)hex_index,
			        (int)pow(2,cache_ways))) != 0)
		{
			printf("WRITE FAILURE!\n");
		}
		else
		{
			++cache_writes;
		}
	}
 	//Cache was Accessed
	++cache_accesses;
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
    printf("Cache Hit Ratio: %2.2f%\n", cache_hit_ratio);
    printf("Cache Miss Ratio: %2.2f%\n", cache_miss_ratio);
    printf("Number of Evictions: %d\n", cache_evictions);
    printf("Number of Writebacks: %d\n\n", cache_writebacks);

    return 0;

}
