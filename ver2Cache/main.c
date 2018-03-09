#include "cache.h"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
	    return 1;
    }

    cache_ways = 3;  //2^3
    byte_select = 6;
    cache_index = 5;
    cache_tag = BIN - (cache_index + byte_select);
   
    unsigned int tag;
    unsigned int index;
    unsigned int bs;

    int cache_location;
    char address_str[HEX];
    unsigned int address_us;

    char buffer[50];
    //all possible cache lines (array)
    int cache_sets_max = pow(2,cache_index); 
    struct cache_set sys_cache[cache_sets_max];
    
    printf("Total Sets: %d\n",cache_sets_max);

    /* read in access file here */
    FILE *fp = fopen(argv[1], "r");
    if(!fp) return 1;
    
    while(fgets(buffer,50,fp) != NULL)
    {
    	printf("Trace: %s\n",buffer);
	    //store r/w bit
        sscanf(&buffer[0],"%d",&r_w_bit);    
	    for(int i = 0; i < HEX; i++)
    	{
	    	//store hex address string
   		    address_str[i] = buffer[i+2];
    	}
	    address_str[HEX] = '\0';

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
        address_us = (unsigned int)strtol(address_str,
        		  NULL,16);
	
	    //retrieve tag/index/byte select
        get_tag_bits_hex(&address_us,&tag,&index,
                         &bs, cache_index,byte_select);
   	
        printf("Hex Add: %x\n",address_us); 
        printf("Hex Tag: %x\n",tag); 
        printf("Hex Ind: %x\n",index); 
        printf("Hex  BS: %x\n",bs); 

        //store set location as integer
        cache_location = get_cache_index_value(&index);
        printf("Cache loc: %d\n",cache_location);  
    
        //print contents of cache set
    

        printf("\n");
    }
    fclose(fp);

    return 0;

}
