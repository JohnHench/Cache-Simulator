#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Invalid args!\n");
        fprintf(stderr, "Usage: %s [-N size] <policy>\n", argv[0]);
        exit(1);
    }
    int cacheSize = 0;
    CachePolicy policy = FIFO; // Default policy is FIFO

    // parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-N") == 0 && i + 1 < argc) {
            cacheSize = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-F") == 0) {
            policy = FIFO;
        } else if (strcmp(argv[i], "-L") == 0) {
            policy = LRU;
        } else if (strcmp(argv[i], "-C") == 0) {
            policy = CLOCK;
        }
    }

    // initialize cache based on the specified size and policy
    Cache *cache = initializeCache(cacheSize, policy);

    // Process input until stdin is closed
    char buffer;
    int compulsoryMisses = 0;
    int capacityMisses = 0;

    int misses[255];
    int missCount = 0;
    memset(misses, 0, sizeof(int) * 255);
    while (scanf(" %c", &buffer) != EOF) { // Read individual characters until EOF
        // check if the item is in the cache
        int hit = findInCache(cache, buffer);
        misses[(int) buffer]++;

        // update cache based on the policy and print status
        if (hit) {
            printf("HIT\n");
        } else {
            printf("MISS\n");
            ++missCount;
            replaceInCache(cache, buffer);
        }
    }

    for (int i = 0; i < 255; ++i) {
        if (misses[i]) {
            compulsoryMisses++;
        }
    }
    capacityMisses = missCount - compulsoryMisses;

    // print summary
    printSummary(compulsoryMisses, capacityMisses);

    // free allocated memory
    Node *temp;
    while (cache->front != NULL) {
        temp = cache->front;
        cache->front = cache->front->next;
        free(temp);
    }

    //valgrind errors should be fixed herer?

    free(cache->lru);
    free(cache->useBits);
    free(cache);

    return 0;
}
