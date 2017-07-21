#include <iostream>

extern void ip_check_deamon(int port);

int main()
{

    // launch ipchkd
    ip_check_deamon(1234);
    return 0;
}
