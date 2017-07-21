#include "Connection.hpp"
#include <string>
void Connection::setBanana(std::string _banana)
{
    banana = _banana;
}

void Connection::setOrange(std::string _orange)
{
    orange = _orange;
}

Connection::Connection(char _id) : id(_id) {};
