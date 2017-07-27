#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define BUFF_SIZE 10000
#define APPLE_D_PORT 1500
#define APPLE_M_PORT 1509
#define SERVER_IP "13.124.180.16"

#define LOG(...) printf("orange > " __VA_ARGS__)

#ifdef DEBUG
#define DLOG(...) printf("orange(debug) > " __VA_ARGS__)
#else
#define DLOG(...) /* empty */
#endif

#define SHELL(...) printf("ssh$" __VA_ARGS__)

void string_to_ip_port(char *ip_port, char *ptr_ip, int *port);

int main(int argc, char **argv) {

    if(argc != 2) {
        printf("plz input : ./orange \"session_id(1~9)\"\n");
        exit(1);
    }

    int sock, sock_main;
    int server_addr_size;
    socklen_t banana_addr_size;

    struct sockaddr_in server_addr, server_main_addr, banana_addr;

    char my_ip[40];
    char banana_ip[40];

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
    sprintf(s_buffer, "%d%c%s" , atoi(argv[1]), 'o', my_ip);
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

    s_buffer[0] = 'Z';
    send(sock_main, s_buffer, sizeof(char), 0);

    if(recv(sock_main, banana_ip, sizeof(banana_ip), 0) < 0) {
        perror("recv error");
        exit(3);
    }

    printf("banana_ip and port : %s\n", banana_ip);

    //    close(sock_main);

    char ip[20];
    int port = -1;

    string_to_ip_port(banana_ip, ip, &port);

    printf("ip : %s\n", ip);
    printf("port : %d\n", port);

    //  send to banana

    memset(&banana_addr, 0, sizeof(banana_addr));
    banana_addr.sin_family      = AF_INET;
    banana_addr.sin_port        = htons(port);
    banana_addr.sin_addr.s_addr = inet_addr(ip);

    int data_size;
    banana_addr_size = sizeof(banana_addr);

    int count = 0;
    //HOLE PUNCHING !!!
    for(;;)
    {
        for(int i=0;i<3;i++){
            if((data_size = sendto(sock, s_buffer, sizeof(char), 0,
                            (struct sockaddr*)&banana_addr,
                            sizeof(banana_addr))) < 0) {
                perror("sendto error!");
                exit(2);
            }
            printf("%dbytes send to banana\n",data_size);
        }

        if((data_size = recvfrom(sock, s_buffer, sizeof(s_buffer), 0,
                        NULL,
                        NULL)) < 0) {
            perror("recvfrom error!");
            exit(3);
        }
        s_buffer[data_size] = '\0';

        printf("received %dbytes \n", data_size);
        printf("%s\n",s_buffer);
        if(strcmp("READY?",s_buffer) == 0)
        {
            break;
        }

    }
    //ready for connection

    sprintf(s_buffer,"OKAY");
    printf("conncted\n");

    sendto(sock, s_buffer, strlen(s_buffer), 0,
            (struct sockaddr*)&banana_addr, sizeof(banana_addr));

    size_t buf_size = sizeof(s_buffer);
    char *shell_buf = 0;
    while(1)
    {
        SHELL("");
        getline(&shell_buf,&buf_size,stdin);
        sendto(sock, shell_buf, strlen(shell_buf), 0,
                (struct sockaddr *)&banana_addr, sizeof(banana_addr));
        data_size = recvfrom(sock, r_buffer, sizeof(r_buffer), 0, NULL, NULL);
        r_buffer[data_size] = '\0';
        printf("%s\n",r_buffer);
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
