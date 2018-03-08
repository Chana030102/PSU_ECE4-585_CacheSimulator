# PSU_ECE4-585_Project
## Single Level Cache Simulator
This program will simulate a single level writeback policy cache.
Three parameters that should be variable will help define the cache structure:
* Number of sets
* Associativity
* Cache line size (limited to 32, 64, or 128 bytes)

Traces will be provided in the following format:
    Access_Type Hex_Address
Access type can be either a 0 (read) or 1 (write) to indicate the operation. 
The Hex address should consist of the following fields in this order:
    | Tag | Index | Byte Select |

Once all traces have been processed, the simulator should provide the following statistics:
* Total number of cache accesses
* Number of cache reads
* Number of cache writes
* Number of cache hits
* Number of cache misses
* Cache hit ratio
* Cache miss ratio
* Number of evictions
* Number of writebacks
=====
### Project Group
Ryan Bornhorst < bornhor2@pdx.edu >
Aaron Chan     < chanaar@pdx.edu  >

=====

