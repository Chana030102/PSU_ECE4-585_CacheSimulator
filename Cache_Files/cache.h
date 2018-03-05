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
	const char* tag[MAX];
};

/* global variables */

static int cache_ways;
static int cache_index;
static int byte_select;

/* cache.c function declarations */

int get_byte_select(int*,int*,int);
int hex_to_bin(char*,int*,int);
int test_struct(struct cache_set*);
int print_struct(struct cache_set*);


