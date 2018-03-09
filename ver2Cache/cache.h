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

static int cache_ways;  // associativity
static int cache_index; // number of index bits
static int byte_select; // number of byte select bits
static int r_w_bit;  //store read = 0, write = 1

// Keep track of transactions
static int total_accesses = 0;
static int writes       = 0;
//static int reads        = 0;
static int hits         = 0;
static int misses       = 0;
static int evictions    = 0;
static int writebacks   = 0;

/* cache.c function declarations */
//void init_sys_cache(struct cache_set* setup);
int cache_compare_tag(unsigned int tag, 
                      struct cache_set* req_set); // Determine cache hit/miss
int cache_compare_valid(struct cache_set* req_set);
int cache_evict(struct cache_set* req_set);
int cache_write(unsigned int tag, struct cache_set* req_set); 
int cache_read(unsigned int tag, struct cache_set* req_set);
