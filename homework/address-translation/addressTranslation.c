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
    int addressUpperBound = PAGECOUNT*PAGECOUNT - 1;
    if (logical < 0 || logical > addressUpperBound) {
        return ERR_OUT_OF_RANGE;
    }

    int frame = logical >> PAGEBITS;

    if (ptr[frame].valid == 0) {
        return ERR_INVALID;
    }

    frame = ptr[frame].frame << PAGEBITS;

    int intermediateAddress = logical >> PAGEBITS << PAGEBITS;
    int offset = logical - intermediateAddress;
    int physicalAddress = frame + offset;

    return physicalAddress;
}
