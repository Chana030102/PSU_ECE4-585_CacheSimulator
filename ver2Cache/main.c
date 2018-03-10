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
   
    unsigned int address;
    unsigned int tag;
    unsigned int index;
   // unsigned int bs;
//    unsigned int bs_mask = pow(2,byte_select)-1;
    unsigned int index_mask = pow(2,byte_select+cache_index)-1;

    int cache_sets_max = pow(2,cache_index); 
    int total_ways = pow(2,cache_ways);
    char address_str[HEX];
    char buffer[50];
    struct cache_set sys_cache[cache_sets_max];

    // Attempt to open file
    FILE *fp = fopen(argv[1], "r");
    if(!fp) 
    {
        printf("Failed to open file %s\n",argv[1]);
        return -1;
    }

    // Read in traces and process
    while(fgets(buffer,50,fp) != NULL)
    {
    	printf("Trace: %s\n",buffer);
        sscanf(&buffer[0],"%d",&r_w_bit); //parse op bit

	    // store hex address and convert to unsigned int
        for(int i = 0; i < HEX; i++)
   		    address_str[i] = buffer[i+2];
	    address_str[HEX] = '\0';
        address = (unsigned int)strtol(address_str,NULL,16);
    
        // mask for cache fields    
        //bs = address & bs_mask;
        index = (address & index_mask)>> byte_select;
        tag = address >> (byte_select+cache_index);
        printf("Index = %d or %x\n",index,index);

        cache_op(tag,&sys_cache[index]);
        total_accesses++;
    }
    fclose(fp); // close file
    cache_stats();
    return 0;
}
