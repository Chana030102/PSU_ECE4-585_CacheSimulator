
/* place cache functions in here */

/* # includes */

#include "cache.h"

/* cache functions */

/*
*	Initialize All Cache Parameters 
*	to Zero on Reboot
*
*/
int cache_startup
(
	struct cache_set* s_cache,
	int tot_sets,
	int tot_ways
)
{
	for(int i = 0; i < tot_sets; i++)
	{
		for(int j = 0; j < tot_ways; j++)
		{
			s_cache[i].valid[j] = 0;
			s_cache[i].dirty[j] = 0;
			s_cache[i].LRU[j] = 0;
			s_cache[i].tag[j] = 0;
		}
	}
return 0;
}

/*
*	Write to the Cache 
*	-determine hit/miss/replace
*
*/
int cache_write
(
	struct cache_set* s_cache,
	unsigned int tag,
	int index,
	int tot_ways
)
{
	int LRU_counter = 0;
	
	//check if valid == 1 and Tags match, Hit for Write
	for(int i = 0; i < tot_ways; i++)
	{
		//write hit
		if((s_cache[index].valid[i] == 1) &&
		   (s_cache[index].tag[i] == tag))
		{
			s_cache[index].dirty[i] = 1;
			s_cache[index].LRU[i] = 1;
			++cache_hits;
			return 0;
		}
	}
	
	//check if valid == 0, Cache Line Empty, Miss for Write
	for(int i = 0; i < tot_ways; i++)
	{
		if(s_cache[index].valid[i] == 0)
		{
			s_cache[index].valid[i] = 1;
			s_cache[index].dirty[i] = 1;
			s_cache[index].LRU[i] = 1;
			s_cache[index].tag[i] = tag;
			++cache_misses;
			return 0;
		}
	}

	//first check LRU and reset if needed
	for(int j = 0; j < tot_ways; j++)
	{
		if(s_cache[index].LRU[j] == 1)
		{
			++LRU_counter;
		}
	}

	//if all LRU bits 1, then RESET to 0
	if(LRU_counter == tot_ways)
	{
		for(int j = 0; j < tot_ways; j++)
		{
			s_cache[index].LRU[j] = 0;
		}
	}

	//valid == 1, No Tag match, Miss/Cast Out Victim
	for(int i = 0; i < tot_ways; i++)
	{
		//Cast Out LRU victim
		if(s_cache[index].LRU[i] == 0)
		{
			s_cache[index].tag[i] = tag;
			s_cache[index].LRU[i] = 1;
			++cache_misses;
			++cache_evictions;
			
			//Writeback if Line was Dirty
			if(s_cache[index].dirty[i] == 1)
			{
				++cache_writebacks;
			}
			//Update Newly written Line to Dirty
			s_cache[index].dirty[i] = 1;
			return 0;
		}
	}

//Cache Write Failure		
return -1;
}

/*
*	Read the Cache 
*	-determine hit/miss/replace
*
*/
int cache_read
(
	struct cache_set* s_cache,
	unsigned int tag,
	int index, 
	int tot_ways
)
{
	int LRU_counter = 0;

	//Check if valid == 1, Tags Match then Read Hit
	for(int i = 0; i < tot_ways; i++)
	{
		//Cache Hit
		if((s_cache[index].valid[i] == 1) && 
		   (s_cache[index].tag[i] == tag))
		{
			s_cache[index].LRU[i] = 1;
			++cache_hits;
			return 0;
		}
	}
	
	//Check if valid == 0.. Yes, then Compulsory Read Miss
	for(int i = 0; i < tot_ways; i++)
	{
		if(s_cache[index].valid[i] == 0)
		{
			s_cache[index].valid[i] = 1;
			s_cache[index].tag[i] = tag;
			s_cache[index].LRU[i] = 1;
			++cache_misses;
			return 0;
		}
	}
	//first check LRU and reset if needed
	for(int j = 0; j < tot_ways; j++)
	{
		if(s_cache[index].LRU[j] == 1)
		{
			++LRU_counter;
		}
	}
	
	//Flush LRU bits if needed
	if(LRU_counter == tot_ways)
	{
		for(int j = 0; j < tot_ways; j++)
		{
			s_cache[index].LRU[j] = 0;
		}
	}

	//Valid == 1, No Tag Match, Cast Out Victim
	for(int i = 0; i < tot_ways; i++)
	{
		//Cast Out Victim based on LRU Policy
		if(s_cache[index].LRU[i] == 0)
		{
			
			s_cache[index].tag[i] = tag;
			s_cache[index].LRU[i] = 1;
			++cache_misses;
			++cache_evictions;

			//Writeback Dirty Cache Line to Memory
			if(s_cache[index].dirty[i] == 1)
			{
				++cache_writebacks;
			}
			s_cache[index].dirty[i] = 0;
			return 0;
		}
	}

//Cache Read Failure
return -1;
}

/*
*	Store Tag / Index / ByteSelect 
*	as Unsigned Ints
*
*/
int set_tag_ind_bs
(
	unsigned int* hex_add,
	unsigned int* hex_tag,
	unsigned int* hex_index,
	unsigned int* hex_bs,
	int index_size,
	int bs_size
)
{
	unsigned int bs_mask = pow(2,bs_size)-1;
	unsigned int index_mask = pow(2,bs_size+index_size)-1;
	*hex_bs = (*hex_add & bs_mask);
	*hex_index = (*hex_add & index_mask) >> bs_size;
	*hex_tag = *hex_add >> (bs_size + index_size);
return 0;
} 
