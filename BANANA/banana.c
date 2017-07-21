#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFF_SIZE 30
#define APPLE_D_PORT 1500
#define APPLE_M_PORT 1509

int main(int argc, char **argv) {
	int sock;
    int server_addr_size;

    struct sockaddr_in server_addr;

    char *dummy = "I'm dummy^^";
    char message[BUFF_SIZE];
    char apple_ip[BUFF_SIZE];

    sock = socket(PF_INET, SOCK_DGRAM, 0);

    if(-1 == sock) {
        perror("sock error");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(APPLE_D_PORT);
    server_addr.sin_addr.s_addr = inet_addr("52.78.214.70");

    size_t temp;

    if((temp = sendto(sock, dummy, strlen(dummy), 0,
            (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0) {
        perror("sendto error!");
        exit(1);
    }

    printf("size : %ld\n", temp);



    server_addr_size  = sizeof(server_addr);
    if(recvfrom(sock, apple_ip, BUFF_SIZE, 0,
            (struct sockaddr*)&server_addr, &server_addr_size) < 0) {
        perror("recvfrom error!");
        exit(1);
    }

    printf("receive_ip: %s \n", apple_ip);

//  sprintf(message_send, "%d%c", 0x01, 'B');
//  printf("message : %s  size : %ld\n", message_send, strlen(message_send));

    close(sock);

    return 0;
}
