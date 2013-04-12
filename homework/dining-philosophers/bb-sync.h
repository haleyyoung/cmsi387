/**
 * Synchronization elements for a bounded buffer solution.
 */
#ifndef __BB_SYNC__
#define __BB_SYNC__

#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t mutex;
sem_t *chopsticks;
#ifndef __APPLE_CC__
sem_t statusOfChopsticks[5];
#endif

/**
 * Initializes synchronization primitives.
 */
void initSync(void);

#endif
