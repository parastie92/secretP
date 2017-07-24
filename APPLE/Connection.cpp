#include "Connection.hpp"
#include <string>
void Connection::setBanana(std::string _banana)
{
    bananaIP = _banana;
}

void Connection::setOrange(std::string _orange)
{
    orangeIP = _orange;
}

Connection::Connection(char _id) : id(_id) {
  bananaSocket = 0;
  orangeSocket = 0;

};
