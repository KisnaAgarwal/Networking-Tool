#include <string>
using namespace std;

class NetworkInterface{
    public:
    string name;
    string ipv4;
    string ipv4_subnetmask;
    string ipv6;
    string ipv6_subnetmask;
    string mac_addr;
    unsigned int flag;
};

