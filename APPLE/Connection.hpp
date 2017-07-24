/*
#ifndef CONNEC_HPP
#define CONNEC_HPP
*/
#include <string>

class Connection {
public:
    std::string  bananaIP;
    std::string  orangeIP;
    char         id;
    int          bananaSocket;  //default : 0
    int          orangeSocket;
// public:
    void    setBanana(std::string _banana);
    void    setOrange(std::string _orange);
    Connection(char _id);
};

//#endif
