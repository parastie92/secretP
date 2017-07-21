#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFF_SIZE 10

int main(int argc, char **argv) {
	int sock;
    int server_addr_size;

    struct sockaddr_in server_addr;

    char message_send[BUFF_SIZE];
    char buff_rcv[BUFF_SIZE];

    sock = socket(PF_INET, SOCK_DGRAM, 0);

    if(-1 == sock) {
        perror("sock error");
        exit( 1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
//  server_addr.sin_port        = htons(4000);
    server_addr.sin_addr.s_addr = inet_addr("52.78.214.70");

    sprintf(message_send, "%d%c", 0x01, 'O');
//  printf("message : %s  size : %ld\n", message_send, strlen(message_send));

    sendto(sock, message_send, strlen(message_send), 0,
            (struct sockaddr*)&server_addr, sizeof(server_addr));

//  server_addr_size  = sizeof(server_addr);
//  recvfrom( sock, buff_rcv, BUFF_SIZE, 0 ,
//            ( struct sockaddr*)&server_addr, &server_addr_size);
//  printf("receive: %s \n", buff_rcv);

    close(sock);

    return 0;
}
