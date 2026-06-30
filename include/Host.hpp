#include <ifaddrs.h>

class Host{
    public:
    char name [256]; 
    struct ifaddrs *ptr; 
    void showName();
    void showInterface();

};