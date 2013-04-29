#ifndef __dinphil_utils__
#define __dinphil_utils__

#include "diningPhilosophers.h"

int randomwait(int bound);

// JD: The functions below strike me as belonging more in
//     diningPhilosophers.h rather than utils.h.
void pickUpChopsticks(philosopher* phil);
void putDownChopsticks(philosopher* phil);

void displayTable();

#endif
