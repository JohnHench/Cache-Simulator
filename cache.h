#ifndef CACHE_H
#define CACHE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { FIFO, LRU, CLOCK } CachePolicy;

typedef struct Node {
    char data;
    struct Node *next;
} Node;

typedef struct {
    int size, count;
    Node *front;
    Node *rear;

    // used for clock
    int *useBits;
    int clockHand;

    // used for lru
    int time;
    int *lru;

    // selected policy
    CachePolicy policy;
} Cache;

//function calls?
//planning how I want to utilized the cache?

// initialize a cache of a given size and policy
Cache *initializeCache(int size, CachePolicy policy);

// replace the target selected item according to the policy with the new item
void replaceInCache(Cache *cache, char newItem);

// finds a specific item in cache
int findInCache(Cache *cache, char data);

// auxilary function
void printSummary(int compulsoryMisses, int capacityMisses);

#endif // CACHE_H
