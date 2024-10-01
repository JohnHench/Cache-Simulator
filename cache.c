#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"

Cache *initializeCache(int size, CachePolicy policy) {
    Cache *cache = (Cache *) malloc(sizeof(Cache));
    cache->size = size;
    cache->count = 0;
    cache->time = 0;
    cache->front = NULL;
    cache->rear = NULL;
    cache->lru = NULL;
    cache->useBits = NULL;
    cache->policy = policy;

    if (policy == CLOCK) {
        cache->useBits = (int *) malloc(size * sizeof(int));
        memset(cache->useBits, 0, size * sizeof(int));
        cache->clockHand = 0;
    } else if (policy == LRU) {
        cache->lru = (int *) malloc(size * sizeof(int));
        memset(cache->lru, 0, size * sizeof(int));
    } else {
        cache->useBits = NULL;
        cache->lru = NULL;
        cache->clockHand = -1;
    }
    return cache;
}

void replaceInCache(Cache *cache, char newItem) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->data = newItem;
    newNode->next = NULL;

    // add to the front of the cache
    if (cache->count < cache->size) {
        if (cache->front == NULL) {
            cache->front = newNode;
            cache->rear = newNode;
        } else {
            cache->rear->next = newNode;
            cache->rear = newNode;
        }

        if (cache->policy == LRU)
            cache->lru[cache->count] = cache->time++;

        cache->count++;
        return;
    }
    // eviction logic based on the selected policy
    else {
        Node *temp;
        if (cache->policy == FIFO) {
            // update the data of the first item
            cache->front->data = newItem;

            // move the first item to the end of the linked list
            temp = cache->front;
            cache->front = cache->front->next;
            temp->next = NULL;

            if (cache->rear != NULL) {
                cache->rear->next = temp;
                cache->rear = temp;
            } else {
                // if the cache was empty
                cache->front = cache->rear = temp;
            }
        } else if (cache->policy == LRU) {
            // evict the least recently used item
            int minIdx = 0;
            int minCount = cache->lru[0];

            for (int i = 1; i < cache->size; ++i) {
                if (cache->lru[i] < minCount) {
                    minCount = cache->lru[i];
                    minIdx = i;
                }
            }

            temp = cache->front;
            for (int i = 0; i < minIdx; ++i) {
                temp = temp->next;
            }

            // update the data of the least recently used item
            temp->data = newItem;
            cache->lru[minIdx] = cache->time++;
        } else if (cache->policy == CLOCK) {
            // evict based on CLOCK policy
            int index = cache->clockHand;
            while (cache->useBits[index] == 1) {
                cache->useBits[index] = 0; // Reset the use bit
                index = (index + 1) % cache->size;
            }
            cache->clockHand = index;
            temp = cache->front;
            while (index != 0) {
                temp = temp->next;
                index--;
            }
            temp->data = newItem;
        }
    }

    free(newNode);
}

int findInCache(Cache *cache, char data) {
    Node *current = cache->front;
    int idx = 0;
    while (current != NULL) {
        if (current->data == data) {
            if (cache->policy == CLOCK) {
                cache->useBits[idx] = 1;
            }
            // if (cache->policy == FIFO) {
            //     cache->useBits[idx] = 1;
            // }
            else if (cache->policy == LRU) {
                cache->lru[idx] = cache->time++;
            }
            return 1;
        }
        ++idx;
        current = current->next;
    }

    return 0;
}

void printSummary(int compulsoryMisses, int capacityMisses) {
    printf("%d %d\n", compulsoryMisses, capacityMisses);
}
