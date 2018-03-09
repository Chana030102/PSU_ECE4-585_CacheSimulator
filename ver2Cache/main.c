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
    unsigned int bs;
    unsigned int bs_mask = pow(2,byte_select)-1;
    unsigned int index_mask = pow(2,byte_select+cache_index)-1;

    int cache_sets_max = pow(2,cache_index); 
    
    char address_str[HEX];
    char buffer[50];
    struct cache_set sys_cache[cache_sets_max];

//    for(int i=0;i<cache_sets_max;i++)
//        init_sys_cache(&sys_cache[i]);

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
        
        bs = address & bs_mask;
        index = (address & index_mask);
        tag = address >> (byte_select+cache_index);
        
        if(r_w_bit)
            if(cache_write(tag,&sys_cache[index]) < 0)
                printf("Failed to write\n");
        else
          printf("Cache Read\n");      
        	
        total_accesses++;
    }
    printf("Total Accesses: %d\n",total_accesses);
    printf("Hits: %d\nMisses: %d\n",hits,misses);
    printf("Writes: %d\n",writes);
    fclose(fp);
    return 0;
}
