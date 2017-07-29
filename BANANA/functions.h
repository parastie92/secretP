#ifndef _BANANA_H_
#define _BANANA_H_

struct args {
    char command[64];
    char argv[16][64];
    int argc;
};

void string_to_ip_port(char *ip_port, char *ptr_ip, int *port);
void parse_command(char *input_command, struct args *args);

#endif
