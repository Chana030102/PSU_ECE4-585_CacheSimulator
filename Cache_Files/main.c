#include <math.h>
#include "cache.h"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
	return 1;
    }

    /* get from user */

    cache_ways = 3;  //2^3
    byte_select = 6;
    cache_index = 5;
    cache_tag = BIN - (cache_index + byte_select);
   
    /* variables */

    /* TESTING ONLY
    int tag_bits[cache_tag];
    int index_bits[cache_index];
    int bs_bits[byte_select];
    */

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
    printf("Total Sets: %d\n",(int)cache_sets_max);
    

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

	//check read/write
	if(r_w_bit == 1)
	{
		printf("Cache Write!\n");
	}
	else
	{
		printf("Cache Read!\n");
	}	
	
        //store hex address as us_int
        hex_address_us = (unsigned int)strtol(hex_address_str,
        		  NULL,16);
	
	//retrieve tag/index/byte select
        get_tag_bits_hex(&hex_address_us,&hex_tag,&hex_index,
                         &hex_bs, cache_index,byte_select);
   	
        printf("Hex Add: %x\n",hex_address_us); 
        printf("Hex Tag: %x\n",hex_tag); 
        printf("Hex Ind: %x\n",hex_index); 
        printf("Hex  BS: %x\n",hex_bs); 

        //store set location as integer
        cache_location = get_cache_index_value(&hex_index);
        printf("Cache loc: %d\n",cache_location);  
    
        //print contents of cache set
	// TESTING
        print_cache_set(s_cache,cache_location,
                        pow(2,cache_ways));
	

        /* start checking r/w, miss/hit behavior */
        for(int i=0;i<pow(2,cache_ways);i++)
        {
            if(s_cache[cache_location].valid[i]==0)
                printf("Invalid %d",i);
        }

        printf("\n");
    }
    fclose(fp);

      
/*  JUST FOR TESTING

    hex_to_bin(hex_address_str,binary_address,HEX);
    print_address(hex_address_str,binary_address);
    get_tag_bits(binary_address,tag_bits,index_bits,bs_bits,
		 cache_tag,cache_index,byte_select);
*/
     
    
    return 0;

}
