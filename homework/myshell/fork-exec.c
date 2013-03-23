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
                // Save command
                if (i == 0) {
                    realCommand = argument;
                    args[i] = argument;
             //       printf("command NOW %s\n", realCommand);                    
                }
                // Save command arguments
                else {
                    args[i] = argument;
           //         printf("ARGUMENT , %d , %s\n", (i-1), args[i - 1]);
                }
         //           printf("command NOW , %d, %s\n", i, realCommand);    
        }

       //     printf("command %s\n", command);
     //       printf("checking %c\n", args[i-2][strlen(args[i- 2]) - 1]);

        // Check if we need to strip off the "&" from the command or last argument
        if (strcmp(&command[strlen(command) - 1], "&") == 0) {
            int position = args[0] ? i : 0;
            command[strlen(command) - 1] = 0;
            args[position] = "&";
            i++;
            
   //         printf("modified command %s , args %s\n", command, args[i-2]);
        }
        else if (args[0] && (strcmp(&args[i- 1][strlen(args[i - 1]) - 1], "&") == 0)
            && (strlen(args[i - 1]) != 1)) {
            args[i] = "&";
            args[i - 1][strlen(args[i- 1]) - 1] = 0;
            i++;
            
 //           printf("modified args %s , args %s\n", args[i - 3], args[i-2]);
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
            printf("command and args %s , %s\n", command, args[m]);
            }
            
            execvp(command, args);
        } else {
            /* Parent process. */
            int result;
  //          printf("%d\n", (strcmp(args[i - 2], "&") != 0));
            if (args[0] && strcmp(args[i - 1], "&") != 0) {
                printf("here\n");
                wait(&result);
            }
            printf("All done; result = %d\n", result);
        }
    }
    return 0;
}
