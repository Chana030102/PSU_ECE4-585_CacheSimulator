#include <string.h>
#include <stdio.h>
#include <math.h>

#define MEM_SIZE 32

/* global variables */
static int ways = 1;
static int line_size = 64; // in bytes
static int bs_size = 8;  // # of bits
static int num_set = 256; 


struct cache_set
{
	int valid;
	int dirty;
	int LRU;
    unsigned int tag;
};
