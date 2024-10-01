Cache Simulator  

The program is a cache simulator written in C, that simulates a cache system with different replacement policies: 
 - First-In First-Out (FIFO)
 - Least Recently Used (LRU)
 - Clock

Program Summary  

This cache simulator is designed to demonstrate the functionality of different cache replacement policies.\
It accepts a sequence of data accesses and simulates cache hits and misses based on the specified cache policy.

Features  

Supports three cache replacement policies: FIFO, LRU, and Clock.\
Allows a configuration of cache size and policy through command line arguments.\
Prints a summary of compulsory and capacity misses after processing the input.


Usage
- -N size: Set the size of the cache.
- -F: Use the First-In First-Out (FIFO) policy (default).
- -L: Use the Least Recently Used (LRU) policy.
- -C: Use the Clock policy.

Execution  
$ ./cacher [-N size] [policy]

