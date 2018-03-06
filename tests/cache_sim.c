/* 
 * This is a test program for handling
 * hex address and translating for the
 * necessary tag, index, and byte select bits
 *
 * The fields of the address are split up in the
 * following order:
 *  | tag | index | byte select |
 */
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MEM_SIZE 32
#define BS_SIZE 7
#define INDEX_SIZE 10

static int global = 10;
int main(void)
{
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

    printf("Global variable is %d\n",global);
    global = 12;
    printf("Global variable is now %d\n",global);

    return 0;
}

