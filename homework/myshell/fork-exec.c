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
        char *context;
        printf("Enter the command to run: ");
        fgets(command, 256, stdin);

        int commandLength = strlen(command);
        // Change newline to terminating 0
        command[commandLength - 1] = 0;
   //     printf("COMMAND %s\n", command);

        char *argument; //= strtok_r(command, delimiter, &context);
        char *realCommand; //= argument;

        // Found this for-loop on: http://www.gsp.com/cgi-bin/man.cgi?topic=strtok_r
        for(argument = strtok_r(command, delimiter, &context), i = 0;
            argument;
            argument = strtok_r(NULL, delimiter, &context), i++){
                // Save command and arguments
                args[i] = argument;
        }

        // Check if we need to strip off the "&" from the command or last argument
        if (strcmp(&args[0][strlen(args[0]) - 1], "&") == 0) {
            int position = args[1] ? i : 1;
            args[0][strlen(args[0]) - 1] = 0;
            args[position] = "&";
            i++;
        }
        else if ((strcmp(&args[i - 1][strlen(args[i - 1]) - 1], "&") == 0)
            && (strlen(args[i - 1]) != 1)) {
            args[i] = "&";
            args[i - 1][strlen(args[i- 1]) - 1] = 0;
            i++;
        }
        
        int waitCharacterPresent = 0;
        if (strcmp(&args[i - 1][0], "&") == 0) {
        printf("setting last character");
            waitCharacterPresent = 1;
            
            // Set i back one so we overwrite the "&" when we assign NULL
            i--;
        }
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
            int m;
            for (m = 0; m < i; m++) {
            printf("command and args %s\n", args[m]);
            }
            
            if (strcmp(args[0], "cd") == 0) {
                printf ("directory %s", args[1]);
                int check = chdir(args[1]);
                printf("check %d", check);
                char cwd[1024];
                printf("current working directory %s\n", getcwd(cwd, sizeof(cwd)));
            }
            else {
                execvp(args[0], args);
            }
        } else {
            /* Parent process. */
            int result;
            if (!waitCharacterPresent) {
                printf("here\n");
                wait(&result);
            }
            printf("All done; result = %d\n", result);
        }
    }
    return 0;
}
