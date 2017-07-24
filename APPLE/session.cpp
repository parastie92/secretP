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

    //session INIT
    if(type == 'b')
    {
      con->bananaSocket = socket;
    }
    else if(type == 'o')
    {
      con->orangeSocket = socket;
    }
    else {
      std::cout<<"fail to init!"<<std::endl;
      std::cout<<"close session"<<std::endl;
      return ;
    }

    //get ip
    recv(socket, r_buffer, sizeof(r_buffer),0);

    if(type == 'b')
    {
      con->setBanana(std::string(r_buffer));
    }
    else if(type == 'o')
    {
      con->setOrange(std::string(r_buffer));
    }
    else
    {
      std::cerr<<"type error!"<<std::endl;
    }
	
	send(socket, r_buffer[0], sizeof(char),0);

        send(con->orangeSocket, con->bananaIP.c_str(), con->bananaIP.size(), 0);
        send(con->bananaSocket, con->orangeIP.c_str(), con->orangeIP.size(), 0);

    while(true)
    {
      recv(socket, r_buffer, sizeof(char),0);
      if(r_buffer[0] == 0x01)
      {
      }
      else
      {
        std::cout<<"unknown command "<<r_buffer[0]<<std::endl;
      }
    }

}
