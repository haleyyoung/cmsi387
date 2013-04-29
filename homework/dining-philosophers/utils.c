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
    displayTable();

    // Let go of left-hand chopstick
    pthread_mutex_unlock(&chopsticks[(phil->name + 1) % 5]);
    phil->leftHand = 0;
    chopstickStatus[(phil->name + 1) % 5] = 1;

    printf("Philosopher %d puts down left chopstick\n", phil->name);
    displayTable();
}

void pickUpChopsticks(philosopher* phil) {
    randomwait(phil->name + 2);

    // picking up right chopstick
    // JD: Nice that you found trylock---however, because this was not
    //     addressed in class, you should include a little explanation
    //     here stating what it does and why you chose to use this
    //     instead of just plain "lock."
    int lockingRight = pthread_mutex_trylock(&chopsticks[phil->name]);
    while (lockingRight) {
        lockingRight = pthread_mutex_trylock(&chopsticks[phil->name]);
    }
    // JD: ^^^Also, your code would be more readable (and better separated)
    //     if you factor out "getRightChopstickIndex" (or any other name
    //     that conveys the same meaning) as a function.  Ditto with the
    //     code for the left chopstick (below), which actually does involve
    //     more logic and thus really calls for a separate function.
    phil->rightHand = 1;
    chopstickStatus[phil->name] = 0;

    printf("Philosopher %d picks up right chopstick.\n", phil->name);
    displayTable();

    if (philosophers[(phil->name + 4) % 5].leftHand && philosophers[phil->name].rightHand) {
        fprintf(stderr, "***** Pick up right failed!\n");
        pthread_mutex_unlock(&chopsticks[phil->name]);
        phil->rightHand = 0;
        chopstickStatus[phil->name] = 1;
        return;
    }

    // picking up left chopstick
    // JD: As mentioned above, the expression "(index + 1) % 5" is repeated
    //     a good number of times here, and justifiably belongs in its own
    //     function, say getLeftChopstickIndex.
    int lockingLeft = pthread_mutex_trylock(&chopsticks[(phil->name + 1) % 5]);
    while (lockingLeft) {
        lockingLeft = pthread_mutex_trylock(&chopsticks[(phil->name + 1) % 5]);
    }
    phil->leftHand = 1;
    chopstickStatus[(phil->name + 1) % 5] = 0;

    printf("Philosopher %d picks up left chopstick.\n", phil->name);
    displayTable();

    if (philosophers[phil->name].leftHand && philosophers[(phil->name + 1) % 5].rightHand) {
        fprintf(stderr, "***** Pick up left failed!\n");
        pthread_mutex_unlock(&chopsticks[(phil->name + 1) % 5]);
        phil->leftHand = 0;
        chopstickStatus[(phil->name + 1) % 5] = 1;
        return;
    }
}




void displayTable() {
    // 5 philosophers * 5 characters each + 5 chopsticks + 6 * 2 possible spaces = 42
    // JD: Above gets 25 + 5 + 12 = 42, indeed, but based on your strcats below
    //     I get up to 4 per left chopstick + up to 5 per philosopher, or
    //     (4 + 5) * 5 = 45.  That, and you begin the string with TABLE:
    //     (+6) plus append a newline (+1) plus must also account for the
    //     null terminator (+1)...and you get at least 45 + 6 + 2 = 53.
//    char display[sizeof(char)*42];
    char display[53];
    // JD: ^^^Because the type of array is known (char), there is no need for
    //     a sizeof(char) in the declaration.

    sprintf(display, "TABLE:");
    // JD: ^^^sprintf has additional logic for formatting arguments etc.
    //     Although what you have above does work, for what you are doing
    //     you may as well use strcpy instead of sprintf.
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
