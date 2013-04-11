/**
 * A test harness for running solutions to the bounded buffer problem.
 */
#include <pthread.h>
#include <stdio.h>

#include "bb-sync.h"

/* The test harness defines the expected interfaces. */
void *pickUp(int thinkBound);
void *putDown(int eatBound);

/**
 * Thread runner for the producer.
 */
void *philRunner(void *arg) {
    printf("Starting philosopher\n");
    pickUp((int)arg);
    printf("Ending philosopher\n");
    pthread_exit(NULL);
}

/**
 * Overall driver program.
 */
int main(int argc, char** argv) {
    printf("Starting bounded buffer test harness...\n");

    /* Initialize the synchronization primitives. */
    initSync();

    /* Start the threads. */
    pthread_t phil1, phil2, phil3, phil4, phil5;
    pthread_create(&phil1, NULL, philRunner, (void *)2);
    pthread_create(&phil2, NULL, philRunner, (void *)3);
    pthread_create(&phil3, NULL, philRunner, (void *)4);
    pthread_create(&phil4, NULL, philRunner, (void *)5);
    pthread_create(&phil5, NULL, philRunner, (void *)6);

    /* Not really needed, since we'll pretty much run forever... */
    pthread_join(phil1, NULL);
    pthread_join(phil2, NULL);
    pthread_join(phil3, NULL);
    pthread_join(phil4, NULL);
    pthread_join(phil5, NULL);

    /* We won't really get here, but to avoid any warnings... */
    return 0;
}
