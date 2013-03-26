#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/**
 * This program demonstrates the use of the fork() and exec()
 * functions.
 */
int main() {
    /* String to hold the command to run. */
    char command[256];
    char *args[256];
    int i;
    while (!feof(stdin)) {
        const char *delimiter = " ";
        const char *waitCharacter = "&";
        int cdCommandPresent = 0;
        int waitCharacterPresent = 0;
        char *argument;
        char *context;
        printf("Enter the command to run: ");
        fgets(command, 256, stdin);

        int commandLength = strlen(command);

        // Change newline to terminating 0
        command[commandLength - 1] = 0;

        // Remove any trailing spaces
        while(strcmp(&command[commandLength - 2], delimiter) == 0){
            command[commandLength - 2] = 0;
            commandLength--;
        }

        // Check if we need to strip off the "&" from the command or last argument
        if(strcmp(&command[commandLength - 2], waitCharacter) == 0){
            command[commandLength - 2] = 0;
            waitCharacterPresent = 1;
        }

        // Found this for-loop on: http://www.gsp.com/cgi-bin/man.cgi?topic=strtok_r
        for(argument = strtok_r(command, delimiter, &context), i = 0;
            argument;
            argument = strtok_r(NULL, delimiter, &context), i++){
                // Save command and arguments, the command will be in args[0]
                args[i] = argument;
        }

        // "cd" command
        if(strcmp(args[0], "cd") == 0) {
            chdir(args[1]);
        }

        // Easter Egg - if we get the "secret-system-call" command
        else if(strcmp(args[0], "secret-system-call") == 0) {
            syscall(350);
        }

        else{

            args[i] = NULL;

            /* Variable that will store the fork result. */
            pid_t pid;

            /* Perform the actual fork. */
            pid = fork();
            if (pid < 0) {
                /* Error condition. */
                fprintf(stderr, "Fork failed\n");
                return -1;

            } else if (pid == 0) {
                /* Child process. */
                printf("Running...\n");
                execvp(args[0], args);

            } else {
                /* Parent process. */
                int result;
                if (!waitCharacterPresent) {
                    wait(&result);
                }
                printf("All done; result = %d\n", result);
            }
        }
    }
    return 0;
}