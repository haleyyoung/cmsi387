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
        int cdCommandPresent = 0;
        char *context;
        printf("Enter the command to run: ");
        fgets(command, 256, stdin);

        int commandLength = strlen(command);
        // Change newline to terminating 0
        command[commandLength - 1] = 0;

        // JD: This is a better place to check for '&' as the last
        //     character---it avoids all of the post-tokenization work.
        //     Check for the character here and wipe it out with '\0'
        //     before even dealing with your arguments.

        char *argument;
        char *realCommand;

        // Found this for-loop on: http://www.gsp.com/cgi-bin/man.cgi?topic=strtok_r
        for(argument = strtok_r(command, delimiter, &context), i = 0;
            argument;
            argument = strtok_r(NULL, delimiter, &context), i++){
                // Save command and arguments, the command will be in args[0]
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
            waitCharacterPresent = 1;
            // Set i back one so we overwrite the "&" when we assign NULL
            i--;
        }
        if(strcmp(args[0], "cd") == 0) {
            cdCommandPresent = 1;
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

            // If we get the "cd" command

            // JD: This contributes to your cd problems---you are changing
            //     directories in the *child*.  The parent never sees this.
            //     And in fact you will have dueling prompts now, because
            //     upon a cd, the child will also be in an fgets loop.
            //
            //     Try this: in here, set some variable that "remembers"
            //     that you are in a child.  Then, in the prompt above,
            //     put a little conditional that displays some indication
            //     of whether you are in a child or the parent.  Then issue
            //     a cd command and observe how your prompts look.
            if (strcmp(args[0], "cd") == 0) {
                cdCommandPresent = 0;
                chdir(args[1]);
            }

            if(cdCommandPresent){
                printf("in child\n");
            }
            // Easter Egg - if we get the "secret-system-call" command
            else if(strcmp(args[0], "secret-system-call") == 0) {
                syscall(350);
            }

            else {
                execvp(args[0], args);
            }
        } else {
            /* Parent process. */
            int result;
            if(cdCommandPresent){
                printf("in parent\n");
                chdir(args[1]);
            }
            if (!waitCharacterPresent) {
                wait(&result);
            }
            printf("All done; result = %d\n", result);
        }
    }
    return 0;
}
