#include "utils.h"
#include "diningPhilosophers.h"

#include <stdio.h>
#include <pthread.h>


/**
 * Thread runner for the producer.
 */
void *philRunner(void *phil) {
    printf("Starting philosopher\n");
    while(1){
        pickUpChopsticks((philosopher *) phil);
        putDownChopsticks((philosopher *) phil);
    }
    printf("Ending philosopher\n");
    pthread_exit(NULL);
}

/**
 * Overall driver program.
 */
int main(int argc, char** argv) {
    int i;


    // chopstickStatus[0] == 1 means chopstick 0 is available
    for (i = 0; i < 5; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
        chopstickStatus[i] = 1;
    }

    /* Create the philosopher objects. */
    // status = 0 is thinking, status = 1 is eating
    // rightHand = 0 is not holding a chopstick

    for(i = 0; i < 5; i++) {
        philosophers[i].name = i;
        philosophers[i].rightHand = 0;
        philosophers[i].leftHand = 0;
        philosophers[i].status = 0;

        /* Start the threads. */
        //pthread_t philosophers[i].thread;
        pthread_create(&philosophers[i].thread, NULL, philRunner, (void *) &philosophers[i]);
    }

    /* Not really needed, since we'll pretty much run forever... */
    for (i = 0; i < 5; i++) {
        pthread_join(philosophers[i].thread, NULL);
    }

    /* We won't really get here, but to avoid any warnings... */
    return 0;
}