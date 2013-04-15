#include "utils.h"

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int randomwait(int bound) {
    int wait = rand() % bound;
    sleep(wait);
    return wait;
}

void putDownChopsticks(philosopher* phil) {
    randomwait(phil->name + 2);

    // Let go of right-hand chopstick
    pthread_mutex_unlock(&chopsticks[phil->name]);
    phil->rightHand = 0;
    chopstickStatus[phil->name] = 1;

    printf("Philosopher %d puts down right chopstick\n", phil->name);
    printf("chopsticks %d %d %d %d %d\n", chopstickStatus[0], chopstickStatus[1],
        chopstickStatus[2], chopstickStatus[3], chopstickStatus[4]);
    displayTable();

    // Let go of left-hand chopstick
    pthread_mutex_unlock(&chopsticks[(phil->name + 1) % 5]);
    phil->leftHand = 0;
    chopstickStatus[(phil->name + 1) % 5] = 1;

    printf("Philosopher %d puts down left chopstick\n", phil->name);
    printf("chopsticks %d %d %d %d %d\n", chopstickStatus[0], chopstickStatus[1],
        chopstickStatus[2], chopstickStatus[3], chopstickStatus[4]);
    displayTable();
    printf("Philosopher %d thinking\n", phil->name);
}

void pickUpChopsticks(philosopher* phil) {
    randomwait(phil->name + 2);

    // picking up right chopstick

    int lockingRight = pthread_mutex_trylock(&chopsticks[phil->name]);
    while (lockingRight) {
        lockingRight = pthread_mutex_trylock(&chopsticks[phil->name]);
    }
    phil->rightHand = 1;
    chopstickStatus[phil->name] = 0;

    printf("Philosopher %d picks up right chopstick.\n", phil->name);
    printf("chopsticks %d %d %d %d %d\n", chopstickStatus[0], chopstickStatus[1],
        chopstickStatus[2], chopstickStatus[3], chopstickStatus[4]);
    displayTable();

    if (philosophers[(phil->name + 4) % 5].leftHand && philosophers[phil->name].rightHand) {
        fprintf(stderr, "***** Pick up right failed!\n");
        pthread_mutex_unlock(&chopsticks[phil->name]);
        phil->rightHand = 0;
        chopstickStatus[phil->name] = 1;
        return;
    }

    // picking up left chopstick

    int lockingLeft = pthread_mutex_trylock(&chopsticks[(phil->name + 1) % 5]);
    while (lockingLeft) {
        lockingLeft = pthread_mutex_trylock(&chopsticks[(phil->name + 1) % 5]);
    }
    phil->leftHand = 1;
    chopstickStatus[(phil->name + 1) % 5] = 0;

    printf("Philosopher %d picks up left chopstick.\n", phil->name);
    printf("chopsticks %d %d %d %d %d\n", chopstickStatus[0], chopstickStatus[1],
        chopstickStatus[2], chopstickStatus[3], chopstickStatus[4]);
    displayTable();

    if (philosophers[phil->name].leftHand && philosophers[(phil->name + 1) % 5].rightHand) {
        fprintf(stderr, "***** Pick up left failed!\n");
        pthread_mutex_unlock(&chopsticks[(phil->name + 1) % 5]);
        phil->leftHand = 0;
        chopstickStatus[(phil->name + 1) % 5] = 1;
        return;
    }

    printf("Philosopher %d eating\n", phil->name);
}




void displayTable() {
    // 5 philosophers made of 5 characters each + 5 chopsticks = 30
    char display[sizeof(char)*50];
    sprintf(display, "TABLE:");
    int i;
    for (i = 0; i < 5; i++) {
        //place left chopstick
        if (chopstickStatus[i] == 1) {
            strcat(display, " | *");
        }
        else if (philosophers[i].rightHand == 1) {
            strcat(display, " *|");
        }
        else {
            strcat(display, " *");
        }

        if (philosophers[i].rightHand == 1 && philosophers[i].leftHand == 1) {
            strcat(display, "0_0|*");
        }
        else {
            strcat(display, "-_-*");
        }
    }
    strcat(display, "\n");
    printf("%s", display);
}