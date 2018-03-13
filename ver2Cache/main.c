/*
 * Single Level Cache Simulator
 *
 * ECE4/585 (Winter 2018) 
 * Microprocessor System Design Project
 * 
 * No data implemenation. 
 * A file with trace(s) will be provided which each
 * trace will be in the following format:
 *     <Access Type> <Hex_Address>
 *
 * Access_Type will indicate the operation:
 *   0 - Read         1 - Write
 *
 * The hex address will be split up into the
 * following fields:
 *    |   Tag   |   Index   |   Byte Select   |
 *
 * Process each trace and keep track of requests 
 * and report them.
 */
#include "cache.h"

int main(int argc, char *argv[])
{
    int cache_sets_max, line_size;

    unsigned int address;
    unsigned int tag;
    unsigned int index;
    unsigned int index_mask;

    char address_str[HEX];
    char buffer[50];
    
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
    printf("Provide the following cache parameters."
           "All numbers must be a power of 2.\n\n");
    printf("Number of sets: ");
    scanf("%d",&cache_sets_max);

    printf("Associativiy: ");
    scanf("%d",&cache_ways);
    while(cache_ways!=1 && cache_ways!=2 && cache_ways!=4 && cache_ways!=8)
    {
        printf("Associativity must be a power of 2.\n"
               "Associativity: ");
        scanf("%d",&cache_ways);
    }

    printf("Cache line size(bytes): ");
    scanf("%d",&line_size);
    while(line_size!=32 && line_size!=64 && line_size!=128)
    {
        printf("Cache line size can only be on of the following:"
                "\n32 Bytes\t64 Bytes\t 128 Bytes\n\n");
        printf("Cache line size(bytes): ");
        scanf("%d",&line_size);
    }
    printf("\n\n");
   
    // Use inputs for line size and sets
    // and determine number of bits by using
    // log base 2
    cache_index = log2(cache_sets_max); 
    byte_select = log2(line_size);

    index_mask = pow(2,byte_select+cache_index)-1;
    
    // initialize cache with valid, dirty, and LRU
    // bits as 0
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

    // Read in traces from file and process
    while(fgets(buffer,50,fp) != NULL)
    {
        sscanf(&buffer[0],"%d",&r_w_bit); //parse op bit

	    // store hex address and convert to unsigned int
        for(int i = 0; i < HEX; i++)
   		    address_str[i] = buffer[i+2];
	    address_str[HEX] = '\0';
        address = (unsigned int)strtol(address_str,NULL,16);
    
        // mask for cache fields    
        index = (address & index_mask)>> byte_select;
        tag = address >> (byte_select+cache_index);
    
        // Perform requested cache operation    
        cache_op(tag,&sys_cache[index]);
        total_accesses++; // increment access count
    }
    fclose(fp); // close file
    cache_stats(); // display cache performance results
    return 0;
}
