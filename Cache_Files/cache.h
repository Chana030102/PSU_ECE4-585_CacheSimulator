#include <string.h>
#include <stdio.h>
#include <math.h>

/* macros */

#define HEX 8
#define BIN 32
#define MAX 8

/* structs */

struct cache_set
{
	int valid[MAX];
	int dirty[MAX];
	int LRU[MAX];
	unsigned int tag[MAX];
};

/* global variables */

int r_w_bit; 
int cache_accesses;
int cache_reads;
int cache_writes;
int cache_hits;
int cache_misses;
float cache_hit_ratio;
float cache_miss_ratio;
int cache_evictions;
int cache_writebacks;

/* cache.c function declarations */

int cache_startup(struct cache_set*, int, int);
int cache_write(struct cache_set*, unsigned int, int, int);
int cache_read(struct cache_set*, unsigned int, int, int);
int set_tag_ind_bs(unsigned int*,unsigned int*,unsigned int*,
		     unsigned int*,int,int);

