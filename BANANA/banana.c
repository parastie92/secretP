#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define BUFF_SIZE 40
#define APPLE_D_PORT 1500
#define APPLE_M_PORT 1509
#define SERVER_IP "127.0.0.1"

void string_to_ip_port(char *ip_port, char *ptr_ip, int *port);

int main(int argc, char **argv) {

    if(argc != 2) {
        printf("plz input : ./banana \"session_id(1~9)\"\n");
        exit(1);
    }

    int sock, sock_main;
    int server_addr_size;
    socklen_t orange_addr_size;

    struct sockaddr_in server_addr, server_main_addr, orange_addr;

    char my_ip[BUFF_SIZE];
    char orange_ip[BUFF_SIZE];

    char s_buffer[BUFF_SIZE];
    char r_buffer[BUFF_SIZE];

    sock = socket(PF_INET, SOCK_DGRAM, 0);

    if(-1 == sock) {
        perror("sock error");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(APPLE_D_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if(sendto(sock, s_buffer, sizeof(char), 0,
                (struct sockaddr*)&server_addr,
                sizeof(server_addr)) < 0) {
        perror("sendto error!");
        exit(2);
    }

    server_addr_size  = sizeof(server_addr);
    if(recvfrom(sock, my_ip, BUFF_SIZE, 0,
                NULL,
                NULL) < 0) {
        perror("recvfrom error!");
        exit(3);
    }

    printf("receive_ip by demon: %s \n", my_ip);
    sprintf(s_buffer, "%d%c%s" , atoi(argv[1]), 'b', my_ip);
    printf("message to main_server: %s\n", s_buffer);

    sock_main = socket(PF_INET, SOCK_STREAM, 0);

    if(-1 == sock_main) {
        perror("sock_main error");
        exit(1);
    }

    memset(&server_main_addr, 0, sizeof(server_main_addr));
    server_main_addr.sin_family      = AF_INET;
    server_main_addr.sin_port        = htons(APPLE_M_PORT);
    server_main_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if(connect(sock_main, (struct sockaddr *)&server_main_addr,
                sizeof(server_main_addr)) < 0) {
        perror("bind error");
        exit(4);
    }

    //initial message
    if(send(sock_main, s_buffer, strlen(s_buffer), 0) < 0) {
        perror("send error");
        exit(2);
    }

    if(recv(sock_main, r_buffer
                , sizeof(r_buffer), 0) < 0) {
        perror("recv error");
        exit(3);
    }

    printf("check ack : %c\n", r_buffer[0]);

    if(recv(sock_main, orange_ip, sizeof(orange_ip), 0) < 0) {
        perror("recv error");
        exit(3);
    }

    printf("orange_ip and port : %s\n", orange_ip);

    //    close(sock_main);

    char ip[20];
    int port = -1;

    string_to_ip_port(orange_ip, ip, &port);

    printf("ip : %s\n", ip);
    printf("port : %d\n", port);

    //  send to orange

    memset(&orange_addr, 0, sizeof(orange_addr));
    orange_addr.sin_family      = AF_INET;
    orange_addr.sin_port        = htons(port);
    orange_addr.sin_addr.s_addr = inet_addr(ip);

    int data_size;
    orange_addr_size = sizeof(orange_addr);

    for(;;) {

        if((data_size = sendto(sock, s_buffer, sizeof(char), 0,
                    (struct sockaddr*)&orange_addr,
                    sizeof(orange_addr))) < 0) {
            perror("sendto error!");
            exit(2);
        }
        printf("%dbytes send to orange\n",data_size);

        if((data_size = recvfrom(sock, s_buffer, sizeof(s_buffer), 0,
                        NULL,
                        NULL)) < 0) {
            perror("recvfrom error!");
            exit(3);
        }

        printf("received %dbytes \n", data_size);

    }

    return 0;
}

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
