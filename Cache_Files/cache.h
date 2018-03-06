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
	const int* tag[MAX];
};

/* global variables */

static int cache_ways;
static int cache_index;
static int byte_select;
static int cache_tag;

/* cache.c function declarations */

int get_tag_bits(int*,int*,int*,int*,int,int,int);
int print_address(char*,int*);
int hex_to_bin(char*,int*,int);
int print_cache_set(struct cache_set*,int,int);


