#ifndef __dinphil__
#define __dinphil__

#include <pthread.h>

typedef struct{
    int name;
    int rightHand;
    int leftHand;
    pthread_t thread;
    int status;
} philosopher;

philosopher philosophers[5];
pthread_mutex_t chopsticks[5];
int chopstickStatus[5];

void *philRunner(void *arg);

#endif
