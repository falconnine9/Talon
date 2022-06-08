#include <libc/types.h>

#include "memory.h"

mm_block_t mm_make_block(uint32_t limit, uint32_t low, mm_flags_t flags) {
    mm_block_t ret = {
        .limit = limit,
        .low   = low,
        .flags = flags
    };
    return ret;
}

mm_flags_t mm_make_flags(bool_t used, bool_t som, bool_t eom, bool_t pused, bool_t nused) {
    mm_flags_t ret = {
        .used  = used,
        .som   = som,
        .eom   = eom,
        .pused = pused,
        .nused = nused
    };
    return ret;
}