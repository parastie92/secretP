#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "banana.h"

int main(void) {
    char input_command[64];
    struct args *args = (struct args*)malloc(sizeof(struct args));

    strcpy(input_command, "ls -l");
    parse_command(input_command, args);

    char *argv[64];
    char *current_arg;
    int i;

    for(i=0; i<args->argc; i++) {
        argv[i] = args->argv[i];
    }
    argv[i] = '\0';

    if(fork() == 0) {
        execvp("ls", argv);
        printf("what? you funxing");
    }

    return 0;
}
