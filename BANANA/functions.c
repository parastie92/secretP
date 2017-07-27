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

void parse_command(char *_command, char *_args[20]) {
    printf("ddd");
    const char delim[2] = " ";
    char *token;
    int index = -1;

    token = strtok(_command, delim);
    memcpy(_args[++index], token, strlen(token));
    printf("??????\n");

    while(token != NULL) {
        token = strtok(NULL, delim);
        memcpy(_args[++index], token, strlen(token));
        printf("??????22\n");
    }
}
