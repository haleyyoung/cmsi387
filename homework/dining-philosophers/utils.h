#ifndef __dinphil_utils__
#define __dinphil_utils__

#include "diningPhilosophers.h"

/* The test harness defines the expected interfaces. */

int randomwait(int bound);

void pickUpChopsticks(philosopher* phil);
void putDownChopsticks(philosopher* phil);

void displayTable(philosopher* philosophers, pthread_mutex_t* chopsticks);

#endif
