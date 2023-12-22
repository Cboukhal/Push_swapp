#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_COMMAND_LENGTH 1024

void execute_command(char *command) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        char *args[MAX_COMMAND_LENGTH];
        char *token = strtok(command, " ");
        int i = 0;

        while (token != NULL && i < MAX_COMMAND_LENGTH - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        waitpid(pid, NULL, 0);
    }
}

int main() {
    char *input;
    int running = 1;

    // Readline configuration
    rl_bind_key('\t', rl_complete);
    using_history();

    while (running) {
        input = readline("$ ");
        if (!input) {
            break;
        }

        if (strlen(input) > 0) {
            add_history(input);
            if (strcmp(input, "exit") == 0) {
                running = 0;
            } else {
                execute_command(input);
            }
        }
        free(input);
    }

    return 0;
}