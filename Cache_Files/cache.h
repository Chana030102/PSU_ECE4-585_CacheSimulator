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

static int cache_ways;
static int cache_index;
static int byte_select;
static int cache_tag;
int r_w_bit;  //store read = 0, write = 1
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
int get_tag_bits_hex(unsigned int*,unsigned int*,unsigned int*,
		     unsigned int*,int,int);
int get_tag_bits(int*,int*,int*,int*,int,int,int);
int print_address(char*,int*);
int hex_to_bin(char*,int*,int);
int print_cache_set(struct cache_set*,int,int);


