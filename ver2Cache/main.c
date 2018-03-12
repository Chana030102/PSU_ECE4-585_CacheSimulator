#include "cache.h"

int main(int argc, char *argv[])
{
    int num_of_sets, line_size;

    // If user doesn't include trace file name in 
    // commandline argument, then warn and quit
    if(argc != 2)
    {
        printf("Include trace file as argument:\n"
               " \t./simcache <trace_file>\n\n");
	    return 1;
    }

    // Prompt user for:
    // * Number of Sets
    // * Associativity
    // * Cache line size
    printf("Input number of sets: ");
    scanf("%d",&num_of_sets);

    printf("Input associativiy: ");
    scanf("%d",&cache_ways);
    while(cache_ways==7 || cache_ways==5 || cache_ways==3)
    {
        printf("Associativity must be a power of 2.\n"
               "Input associativity: ");
        scanf("%d",&cache_ways);
    }

    printf("Input cache line size: ");
    scanf("%d",&line_size);
    while(line_size!=32 && line_size!=64 && line_size!=128)
    {
        printf("Cache line size can only be on of the following:"
                "\n32 Bytes\t64 Bytes\t 128 Bytes\n\n");
        printf("Input cache line size(bytes): ");
        scanf("%d",&line_size);
    }
   
    // Use inputs for line size and sets
    // and determine number of bits by using
    // log base 2
    cache_index = log2(num_of_sets); 
    byte_select = log2(line_size);

    unsigned int address;
    unsigned int tag;
    unsigned int index;
    unsigned int index_mask = pow(2,byte_select+cache_index)-1;

    int cache_sets_max = pow(2,cache_index); 
    char address_str[HEX];
    char buffer[50];
    struct cache_set sys_cache[cache_sets_max];
    
    for(int i=0;i<cache_sets_max;i++)
        init_cache(&sys_cache[i]);
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
    	
        printf("Trace: %s\n",buffer);
        printf("Index = %d or %x\n",index,index);
        printf("Tag   = %d or %x\n",tag,tag);

        cache_op(tag,&sys_cache[index]);
        total_accesses++;
    }
    fclose(fp); // close file
    cache_stats();
    return 0;
}
