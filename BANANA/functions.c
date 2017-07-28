#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "banana.h"

void string_to_ip_port(char *ip_port, char *ptr_ip,
        int *ptr_port) {
    char _ip[20];
    int index = 0;

    while(ip_port[index] != ':') {
        _ip[index] = ip_port[index];
        index++;
    }
    _ip[index] = '\0';
    memcpy(ptr_ip, _ip, 20);

    char *temp = &ip_port[index+1];
    *ptr_port = atoi(temp);
}

void parse_command(char *input_command, struct args *args) {
    int index = -1;

    char *token = strtok(input_command, " ");
    if(token == NULL) {
        perror("Invalid input command");
        exit(1);
    }

    strcpy(args->command, token);
    strcpy(args->argv[++index], token);
    printf("command : %s\n", args->command);
    printf("argv[%d] : %s\n", index, args->argv[index]);

    while((token = strtok(NULL, " "))) {
        strcpy(args->argv[++index], token);
        printf("argv[%d] : %s\n", index, args->argv[index]);
    }

    args->argc = index + 1;
}

