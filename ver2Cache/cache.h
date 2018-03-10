#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define HEX 8
#define MAX 8

struct cache_set
{
	int valid[MAX];
	int dirty[MAX];
	int LRU[MAX];
	const unsigned int* tag[MAX];
};

int cache_ways;  // associativity
int cache_index; // number of index bits
int byte_select; // number of byte select bits
int r_w_bit;  //store read = 0, write = 1

// Keep track of transactions
extern int total_accesses;
extern int writes;
extern int reads;
extern int hits;   
extern int misses;
extern int evictions; 
extern int writebacks;

/* cache.c function declarations */
int cache_compare_tag(unsigned int tag, 
                      struct cache_set* req_set); // Determine cache hit/miss
int cache_compare_valid(struct cache_set* req_set);
int cache_evict(struct cache_set* req_set);
int cache_op(unsigned int tag, struct cache_set* req_set); 
void cache_stats(void);
