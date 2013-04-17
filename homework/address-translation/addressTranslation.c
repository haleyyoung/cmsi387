/**
 * Implementation of the software paging unit.
 */
#include "addressTranslation.h"

#include <stdio.h>
#include <stdlib.h>

static pagetable *ptr = NULL; // ptr = "page table register"

void setPageTable(pagetable *pt) {
    ptr = pt;
}

int getPhysical(int logical) {
    if (logical < 0 || logical > 255) {
        return ERR_OUT_OF_RANGE;
    }

    int frame = logical >> 4;

    if (ptr[frame].valid == 0) {
        return ERR_INVALID;
    }
}
