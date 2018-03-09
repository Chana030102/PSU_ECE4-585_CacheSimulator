/*
 * Define necessary functions to work with the cache
 */
#include "cache.h"

/*
// Initialize valid, dirty, and LRU to be zero for the
// cache sets being used
void init_sys_cache(struct cache_set* setup)
{
    setup = malloc(sizeof(struct cache_set*));
    for(int j=0;j<cache_ways;j++)
    {

        setup->valid[j]=0;
        setup->dirty[j]=0;
        setup->LRU[j]  =0;
    }
}
*/

/*
 * Search for corresponding tag from trace.
 * Upon hit, return corresponding way
 * Upon miss, return -1 
 */
int cache_compare_tag(unsigned int tag, struct cache_set* req_set)
{
   for(int i=0;i<cache_ways;i++)
   {
      printf("%d ",i);
      if(req_set->tag[i] == tag)
      {
         hits++;
         return i;
      }
   }
   misses++;
   return -1;
}

/*
 * Look for invalid cache lines we can replace.
 * Return corresponding way when invalid found.
 * If all lines valid, then return -1.
 */
int cache_compare_valid(struct cache_set* req_set)
{
    for(int i=0;i<cache_ways;i++)
    {
        if(req_set->valid[i]==0)
            return i;
    }
    return -1;
}

/* 
 * Compare LRU bits and evict a cache line
 * If all LRU bits set to 1, reset all to 0
 */
int cache_evict(struct cache_set* req_set)
{
    // Check for LRU bit = 0
    for(int i=0;i<cache_ways;i++)
    {
        if(req_set->LRU[i]==0)
            return i;
    }

    // All LRU bits were 1. Set all to 0
    // and tell cache to evict the first way
    for(int i=0;i<cache_ways;i++)
        req_set->LRU[i] = 0;
    return 0;

}

/* 
 *  Perform cache write. Update evictions and writebacks
 *  when necessary. Also set dirty bit.
 */
int cache_write( unsigned int tag, struct cache_set* req_set)
{
    int way = cache_compare_tag(tag,&req_set); // determine cache hit/miss

    if(way < 0)
    {
        
    }
    
    // Write in cache line
    req_set->valid[way] = 1;
    req_set->dirty[way] = 1;
    req_set->LRU[way] = 1;
    req_set->tag[way] = tag;

    return 1;
}

    


