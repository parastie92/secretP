#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <map>

#define IPCHKD_PORT 1500
#define APPLE_PORT  1509

extern void ip_check_deamon(int port);

int main()
{
    // launch ipchkd
    if(fork() == 0)
    {
        ip_check_deamon(IPCHKD_PORT);
    }
    else
    {
        int server_socket;
        socklen_t adr_sz;

        struct sockaddr_in server_addr, client_addr;

        server_socket = socket(PF_INET,SOCK_STREAM,0);
        if(server_socket < 0)
            std::cerr << "socket() error" << std::endl;

        memset(&server_addr,0,sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        server_addr.sin_port = htons(APPLE_PORT);

        if(bind(server_socket,(struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        {
            std::cerr << "bind() error" << std::endl;
        }

    }

    return 0;
}
