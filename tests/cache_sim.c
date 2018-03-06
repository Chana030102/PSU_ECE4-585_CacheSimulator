/* 
 * This is a test program for handling
 * hex address and translating for the
 * necessary tag, index, and byte select bits
 *
 * The address is split up into the following fields:
 *  | tag | index | byte select |
 */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "cache.h"

#define MEM_SIZE 32
#define BS_SIZE 7
#define INDEX_SIZE 10

int main(void)
{
    struct cache_set set[ways*num_set];
    unsigned int bs, tag, index;    
    unsigned int bs_mask = pow(2,BS_SIZE)-1;
    unsigned int index_mask = pow(2,BS_SIZE+INDEX_SIZE+1)-1;
    unsigned int address = 0xA0056FB9;

    bs = (bs_mask & address);
    index = (index_mask & address) >> BS_SIZE;
    tag = address >> (BS_SIZE + INDEX_SIZE);

    printf("Hex address is %x\n",address);
    printf("Byte Select is %x or %d\n",bs,bs);
    printf("Index is %x or %d\n",index,index);
    printf("Tag is %x or %d\n",tag,tag);

    set[index].valid = 1;
    set[index].dirty = 0;
    set[index].LRU = 1;
    set[index].tag = tag;
    
    printf("Verify tag is saved correctly: %x\n",set[index].tag);
    return 0;
}

