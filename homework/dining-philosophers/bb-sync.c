/**
 * Synchronization primitive implementation.
 */
#include "bb-sync.h"

#include "buffer.h"
#ifdef __APPLE_CC__
#include <fcntl.h>
#endif
#include <pthread.h>
#include <semaphore.h>

void initSync(void) {
    pthread_mutex_init(&mutex, NULL);
    int i;
    int chopsticksLength = sizeof(int)*5;
#ifndef __APPLE_CC__
    chopsticks = &statusOfChopsticks;
    for(i = 0; i < chopsticksLength; i += sizeof(sem_t)){
        sem_init(chopsticks[i], 0, 1);
    }
#else
    sem_unlink("chopsticks");
    for(i = 0; i < chopsticksLength; i += sizeof(sem_t)){
        chopsticks[i] = sem_open("chopsticks[" + i + "]", O_CREAT, S_IRWXU, 1);
    }
#endif
}
