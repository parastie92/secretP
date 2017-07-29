#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "net_apple.h"

void send_to_daemon(int *sock, char *s_buffer, char *banana_ip) {
    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(APPLE_D_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if(sendto(*sock, s_buffer, sizeof(char), 0, (struct sockaddr*)&server_addr,
                sizeof(server_addr)) < 0) {
        perror("sendto error!");
        exit(2);
    }

    if(recvfrom(*sock, banana_ip, sizeof(banana_ip), 0, NULL, NULL) < 0) {
        perror("recvfrom error!");
        exit(3);
    }
}
