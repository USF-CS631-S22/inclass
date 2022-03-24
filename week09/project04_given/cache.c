#include <stdio.h>
#include <stdlib.h>

#include "armemu.h"
    
void cache_init(struct cache_st *csp) {

    if (csp->type == CT_DIRECT_MAPPED_1) {
        csp->ways = 1;
        csp->index_mask = (csp->size) - 1;
        csp->block_size = 1;
    } else if (csp->type == CT_SET_ASSOCIATIVE_1) {
        csp->ways = 4;
        csp->index_mask = (csp->size / csp->ways) - 1;
        csp->block_size = 1;
    }

    csp->index_bits = 0;
    while (csp->index_mask & (1 << csp->index_bits)) {
              csp->index_bits++;
    }

    for (int i = 0; i < CACHE_MAX_SLOTS; i++) {
        csp->slots[i].valid = 0;
        csp->slots[i].tag = 0;
        for (int j = 0; j < CACHE_MAX_BLOCK_SIZE; j++) {
            csp->slots[i].block[j] = 0;
        }
        // timestamp only used for SA cache
        csp->slots[i].timestamp = 0;
    }

    csp->refs = 0;
    csp->hits = 0;
    csp->misses = 0;
    csp->misses_cold = 0;
    csp->misses_hot = 0;
}

void cache_print(struct cache_st *csp, char *name) {
    int num_slots_used = 0;
    int i;

    for (i = 0; i < csp->size; i++) {
        if (csp->slots[i].valid == 1) {
            num_slots_used += 1;
        }
    }

    printf("=== Cache %s\n", name);
    printf("Type          = ");
    if (csp->type == CT_DIRECT_MAPPED_1) {
        printf("direct mapped block size 1\n");
    } else if (csp->type == CT_DIRECT_MAPPED_4) {
        printf("direct mapped block size 4\n");
    } else if (csp->type == CT_SET_ASSOCIATIVE_1) {
        printf("4-way set associative block size 1\n");
    } else if (csp->type == CT_SET_ASSOCIATIVE_4) {
        printf("4-way set associative block size 4\n");
    }
    printf("Size          = %d slots\n", csp->size);
    printf("References    = %d\n", csp->refs);
    printf("Hits          = %d (%.2f%% hit ratio)\n", csp->hits, 
           ((double) csp->hits / (double) csp->refs) * 100.00);
    printf("Misses        = %d (%.2f%% miss ratio)\n", csp->misses,
           ((double) csp->misses / (double) csp->refs) * 100.00);    
    printf("Misses (cold) = %d\n", csp->misses_cold);
    printf("Misses (hot)  = %d\n", csp->misses_hot);
    printf("%% Used        = %.2f%%\n", ((double) num_slots_used / (double) csp->size) * 100.0);    
}

// Direct mapped lookup
uint32_t cache_lookup_dm(struct cache_st *csp, uint32_t addr,
                         bool write, uint32_t value) {
    uint32_t tag;
    uint32_t index;
    struct cache_slot_st *slot;
    uint32_t data;

    index = (addr >> 2) & csp->index_mask;
    tag = addr >> (csp->index_bits + 2);

    slot = &csp->slots[index];

    csp->refs += 1;
    if (slot->valid && (slot->tag == tag)) {
        // hit
        csp->hits += 1;

        if (write) {
            // update cache slot data
            slot->block[0] = value;
            // write back to memory
            *((uint32_t *) addr) = value;
        } else {
            data = slot->block[0];
        }
        verbose("  cache tag hit for index %d tag %X addr %lX\n",
                index, tag, addr);

    } else {
        // miss
        csp->misses += 1;
        if (slot->valid == 0) {
            csp->misses_cold += 1;
            verbose("  cache tag (%X) miss for index %d tag %X addr %X (cold)\n",
                    slot->tag, index, tag, addr);
        } else {
            csp->misses_hot += 1;
            verbose("  cache tag (%X) miss for index %d tag %X addr %X (hot)\n",
                    slot->tag, index, tag, addr);
            
        }
        slot->valid = 1;
        slot->tag = tag;
        if (write) {
            slot->block[0] = value;
            *((uint32_t *) addr) = value;
        } else {
            data = *((uint32_t *) addr);
            slot->block[0] = data;
        }
    }
    
    return data;
}

uint32_t cache_lookup_sa(struct cache_st *csp, uint32_t addr, bool write, uint32_t value) {
    // TODO
    return 0;
}



// Cache lookup
uint32_t cache_lookup(struct cache_st *csp, uint32_t addr, bool write, uint32_t value) {
    uint32_t data;

    if (csp->type == CT_DIRECT_MAPPED_1 || csp->type == CT_DIRECT_MAPPED_4) {
        data = cache_lookup_dm(csp, addr, write, value);
    } else if (csp->type == CT_SET_ASSOCIATIVE_1 || csp->type == CT_SET_ASSOCIATIVE_4) {
        data = cache_lookup_sa(csp, addr, write, value);
    } else {
        if (write) {
            *((uint32_t *) addr) = value;
        } else {
            data = *((uint32_t *) addr);
        }
    }
    return data;
}
