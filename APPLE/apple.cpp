#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include <iostream>
#include <string>
#include <thread>
#include <map>
#include <vector>
#include <functional>

#include "Connection.hpp"

#define IPCHKD_PORT 1500
#define APPLE_PORT  1509

extern void ip_check_deamon(int port);
extern void session(int socket, Connection* con, char type);

std::vector<std::thread> sessions;
std::map<char,Connection> connected;

int main()
{
char r_buffer[1024];
char s_buffer[1024];
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

        if(listen(server_socket,5) < 0)
        {
            std::cerr << "listen() error" << std::endl;
        }

        while(true)
        {
            int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &adr_sz );
	    std::cout<<"accepted!"<<std::endl;
            if(client_socket < 0)
            {
                std::cerr<<"invalid socket !"<<std::endl;
            }
            recv(client_socket,(void *)r_buffer,2,MSG_WAITALL);
            Connection *con;
            if(connected.find(r_buffer[0]) == connected.end())
            {
                //not found
                std::cout<<"create connection "<<r_buffer[0]<<std::endl;
                connected.insert(std::make_pair(r_buffer[0],Connection(r_buffer[0])));
            }
            else
            {
                //found
                std::cout<<"open connection "<<r_buffer[0]<<std::endl;
            }
            con = &(connected.at(r_buffer[0]));
            //create thread(start session)
            std::cout<<"create thread("<<r_buffer[1]<<") ID: "<<r_buffer[0]<<std::endl;
            sessions.push_back(std::thread(session,client_socket,con,r_buffer[1]));
            
        }

    }

    return 0;
}
