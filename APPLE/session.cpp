#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "Connection.hpp"

void session(int socket,Connection* con,char type)
{
    char r_buffer[128];
    char s_buffer[128];

    
}
