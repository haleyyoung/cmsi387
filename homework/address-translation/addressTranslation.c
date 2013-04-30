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
    // JD: I see what you're trying to do here---however, in the
    //     general case, remember that the number of pages != the
    //     size of a page.  (e.g., for 32-bit Intel CPUs, the
    //     logical address is 32 bits with page sizes of up to 4M)
    int addressUpperBound = PAGECOUNT*PAGECOUNT - 1;
    if (logical < 0 || logical > addressUpperBound) {
        return ERR_OUT_OF_RANGE;
    }

    // JD: Your final computation is correct, but with respect
    //     to naming, this value isn't quite the frame yet---it
    //     is the *index* of the pagetable entry which will then
    //     contain the frame.  Not super huge, but potentially
    //     confusing to the reader (especially when you do the
    //     actual frame calculation a few lines below).
    int frame = logical >> PAGEBITS;

    if (ptr[frame].valid == 0) {
        // JD: ^^^ !ptr[page].valid works in C also :)
        return ERR_INVALID;
    }

    frame = ptr[frame].frame << PAGEBITS;

    // JD: So for this one, you are essentially removing the
    //     low-order/offset bits.  A bitwise and may be more
    //     efficient here.
    int intermediateAddress = logical >> PAGEBITS << PAGEBITS;
    int offset = logical - intermediateAddress;
    int physicalAddress = frame + offset;
    // JD: ^^^Yes, actually from an efficiency standpoint, see
    //     if you can re-express these in terms of purely
    //     bitwise operations.

    return physicalAddress;
}
