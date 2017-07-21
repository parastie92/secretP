/*
#ifndef CONNEC_HPP
#define CONNEC_HPP
*/
#include <string>

class Connection {
private:
    std::string  banana;
    std::string  orange;
    char    id;
public:
    void    setBanana(std::string _banana);
    void    setOrange(std::string _orange);
    Connection(char _id);
};

//#endif
