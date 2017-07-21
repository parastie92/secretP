#ifndef IPCHKD
#define IPCHKD

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>
#include <unistd.h>

void ip_check_deamon(int _port)
{
    int serv_socket;
    char dummy;
    ssize_t str_len;
    socklen_t clnt_adr_sz;

    struct sockaddr_in serv_adr, clnt_adr;

    serv_socket = socket(PF_INET,SOCK_DGRAM,0);
    if(serv_socket==-1)
    {
        printf("socket() error\n");
    }

    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(_port);

    if(bind(serv_socket,(struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
    {
        printf("bind() error\n");
    }

    std::string userIP;
    int userPort;
    std::string buffer;
    while(true)
    {
        clnt_adr_sz=sizeof(clnt_adr);
        str_len=recvfrom(serv_socket, &dummy, 1, 0, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        if(str_len>0)
        {

            userIP = inet_ntoa(clnt_adr.sin_addr);
            userPort = clnt_adr.sin_port;
            printf("%s:%d - ",userIP.c_str(),userPort);
            //            printf("%s\n",&dummy);
            buffer+=userIP;
            buffer+=':';
            buffer+=std::to_string(userPort);
            int send = (int)sendto(serv_socket, buffer.c_str(),buffer.size(), 0, (struct sockaddr*)&clnt_adr, clnt_adr_sz);
            std::cout<<buffer<<std::endl;
            buffer.clear();

        }
    }
    close(serv_socket);
}
#endif