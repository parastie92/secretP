#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_command(char *command, char argv[][20]);

int main() {
    int i;
    char *str = "ls -l";
    char argv[20][20];

//    argv = (char**)malloc(sizeof(char*) * 20);
 //   argv[0] = (char*)malloc(sizeof(char) * 20*20);
 //   for(i=1; i<20; i++) {
 //       argv[i] = argv[i-1] + 20;
 //   }

    printf("str : %s\n", str);

    parse_command(str, argv);

    return 0;
}

void parse_command(char *command, char argv[][20]) {
    printf("command : %s\n", command);
    int index = -1;
    char *rest = command;
    char *token;

    printf("rest : %s\n", rest);
    printf("11111\n");

    while(token = strtok_r(rest, " ", &rest)) {
        printf("token : %s\n", token);
        memcpy(argv[++index], token, strlen(token));

        printf("22222\n");
    }
}

