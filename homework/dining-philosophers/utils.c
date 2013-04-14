#include "utils.h"

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>

int randomwait(int bound) {
    int wait = rand() % bound;
    sleep(wait);
    return wait;
}

void putDownChopsticks(philosopher* phil) {
    randomwait(phil->name + 2);

    // Let go of right-hand chopstick
    printf("Philosopher %d puts down right chopstick\n", phil->name);

    pthread_mutex_unlock(&chopsticks[phil->name]);
    phil->rightHand = 0;

    if (phil) {
        fprintf(stderr, "***** Put down right failed!\n");
        pthread_mutex_lock(&chopsticks[phil->name]);
        phil->rightHand = 1;
        return;
    }


    // Let go of left-hand chopstick
    printf("Philosopher %d puts down left chopstick\n", phil->name);

    pthread_mutex_unlock(&chopsticks[(phil->name + 1) % 5]);
    phil->leftHand = 0;

    if (phil) {
        fprintf(stderr, "***** Put down left failed!\n");
        pthread_mutex_lock(&chopsticks[(phil->name + 1) % 5]);
        phil->leftHand = 1;
        return;
    }

    printf("Philosopher %d thinking\n", phil->name);
}

void pickUpChopsticks(philosopher* phil) {
    randomwait(phil->name + 2);

    // picking up right chopstick
    printf("Philosopher %d picks up right chopstick.\n", phil->name);

    int lockingRight = pthread_mutex_trylock(&chopsticks[phil->name]);
    while (lockingRight) {
        lockingRight = pthread_mutex_trylock(&chopsticks[phil->name]);
        (*phil).rightHand = 1;
    }
    printf("????????????? phil %d right hand %d\n", phil->name, phil->rightHand);
    printf("\n\nphilosopher %d left hand %d philosopher %d right hand %d\n\n",
        philosophers[(phil->name + 4) % 5].name, philosophers[(phil->name + 4) % 5].leftHand,
        philosophers[phil->name].name, philosophers[phil->name].rightHand);
    if (philosophers[(phil->name + 4) % 5].leftHand && philosophers[phil->name].rightHand) {
        fprintf(stderr, "***** Pick up right failed!\n");
        pthread_mutex_unlock(&chopsticks[phil->name]);
        phil->rightHand = 0;
        return;
    }

    // picking up left chopstick
    printf("Philosopher %d picks up left chopstick.\n", phil->name);

    int lockingLeft = pthread_mutex_trylock(&chopsticks[(phil->name + 1) % 5]);
    while (lockingLeft) {
        lockingLeft = pthread_mutex_trylock(&chopsticks[(phil->name + 1) % 5]);
        phil->leftHand = 1;
    }
    printf("????????????? phil %d left hand %d\n", phil->name, phil->leftHand);
    printf("\n\nphilosopher %d left hand %d philosopher %d right hand %d\n\n",
        philosophers[phil->name].name, philosophers[phil->name].leftHand,
        philosophers[(phil->name + 1) % 5].name, philosophers[(phil->name + 1) % 5].rightHand);
    if (philosophers[phil->name].leftHand && philosophers[(phil->name + 1) % 5].rightHand) {
        fprintf(stderr, "***** Pick up left failed!\n");
        pthread_mutex_unlock(&chopsticks[(phil->name + 1) % 5]);
        phil->leftHand = 0;
        return;
    }

    printf("Philosopher %d eating\n", phil->name);
}




void displayTable(philosopher* philosophers, pthread_mutex_t* chopsticks) {
   /* char display[BUFFER_SIZE * (ITEM_WIDTH + 1) + 64];
    char buffer_content[ITEM_WIDTH + 1];
    sprintf(display, "(%s) in: %d out: %d [ ", preface, in, out);
    int i;
    for (i = 0; i < BUFFER_SIZE; i++) {
        sprintf(buffer_content, "%d", buffer[i]);

        if (i == in) {
            strcat(display, "+>");
        }
        strcat(display, buffer_content);

        if (i == out) {
            strcat(display, "->");
        }
        strcat(display, " ");
    }
    strcat(display, "]\n");
    printf("%s", display); */
}