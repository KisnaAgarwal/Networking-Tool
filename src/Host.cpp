#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>// L2 protocols
#include <vector>
#include <iomanip>
#include <sstream>
#include <Host.hpp>
#include <net/if.h> // for IFF tags
#include <sys/ioctl.h>// for IFF tags


using namespace std;




void  Host::getName(){
    char name[256];
    if(gethostname(name , 256) ==-1){
        cout<<"error in host name";
    }else{
        Hostname = name;
    }
}


void Host::getInterface(){
    struct ifaddrs *ptr = nullptr; 
    if(getifaddrs(&ptr)==-1){
        cout<<"error in network intefaces" ;
    }
    struct ifaddrs * curr;
    curr = ptr;
    
    while(curr!=NULL){

       NetworkInterface & Curr_If = HostInterface[curr->ifa_name]; 
       Curr_If.name = curr->ifa_name;
       Curr_If.flag = curr->ifa_flags;


       //for Ip adrress :
        if(curr->ifa_addr != nullptr){
            if(curr->ifa_addr->sa_family==AF_INET) { //check if the network interface address is same as IP4
                //for IPv4 address
                 sockaddr_in * ip4adr = (sockaddr_in*)curr->ifa_addr; //typecaast into sockaddr_in 
                 char ipaddress [INET_ADDRSTRLEN];
                 if(inet_ntop(AF_INET,&ip4adr->sin_addr ,ipaddress ,INET_ADDRSTRLEN)){ //convert from binary to 
                    Curr_If.ipv4 = ipaddress;
                 }else{
                    perror("getifaddrs");
                 }
            }else if (curr->ifa_addr->sa_family ==AF_INET6){ //for IPv6 address
                sockaddr_in6 * ip6adr = (sockaddr_in6*)curr->ifa_addr;
                char ipaddress [INET6_ADDRSTRLEN];
                if(inet_ntop(AF_INET6 ,&ip6adr->sin6_addr , ipaddress ,INET6_ADDRSTRLEN )){
                    Curr_If.ipv6 = ipaddress;
                }else{
                    perror("getifaddrs");
                }
            }
        }
        //subnet mask : 
            if(curr->ifa_netmask != nullptr){
                //for ipv4
                if(curr->ifa_netmask->sa_family==AF_INET){
                    sockaddr_in * subnet_v4 = (sockaddr_in*)curr->ifa_netmask;
                    char subnet_mask [INET_ADDRSTRLEN];
                    if(inet_ntop(AF_INET,&subnet_v4->sin_addr ,subnet_mask ,INET_ADDRSTRLEN)){ //convert binary to 
                        Curr_If.ipv4_subnetmask = subnet_mask;
                    }else{
                        perror("inet_ntop");
                    }
                }
                // for ipv6
                 else if(curr->ifa_netmask->sa_family==AF_INET6){
                    sockaddr_in6 * subnet_v6 = (sockaddr_in6*)curr->ifa_netmask;
                    char subnet_mask [INET6_ADDRSTRLEN];
                    if(inet_ntop(AF_INET6,&subnet_v6->sin6_addr ,subnet_mask ,INET6_ADDRSTRLEN)){
                        Curr_If.ipv6_subnetmask = subnet_mask;
                    }else{
                        perror("inet_ntop");
                    }
                } 
            }

            //for MAC address :
            if(curr->ifa_addr != nullptr){
                if(curr->ifa_addr->sa_family == AF_PACKET){
                    sockaddr_ll  * macaddr = (sockaddr_ll*)curr->ifa_addr;
                    stringstream temp;
                    for(int i = 0 ; i < macaddr->sll_halen ; i++){
                        
                        temp<<setw(2)<<setfill('0')<<hex;
                        temp<<(int)macaddr->sll_addr[i] <<":";
                    
                    }
                    Curr_If.mac_addr = temp.str();
                }
            }

            //for flags 
            

        curr = curr->ifa_next;
    }
    freeifaddrs(ptr);
}

void Host::showNetworkInterface()
{
    for (const auto& [name, iface] : HostInterface)
    {
        cout << "========================================\n";
        cout << "Interface Name     : " << iface.name << '\n';
        cout << "  IPv4 Address     : " << iface.ipv4 << '\n';
        cout << "  IPv4 Subnet Mask : " << iface.ipv4_subnetmask << '\n';
        cout << "  IPv6 Address     : " << iface.ipv6 << '\n';
        cout << "  IPv6 Subnet Mask : " << iface.ipv6_subnetmask << '\n';
        cout << "  MAC Address      : " << iface.mac_addr << '\n';
        cout << "  Flags            : ";
        if (iface.flag & IFF_UP)           cout << "UP ";
        if (iface.flag & IFF_RUNNING)      cout << "RUNNING ";
        if (iface.flag & IFF_BROADCAST)    cout << "BROADCAST ";
        if (iface.flag & IFF_MULTICAST)    cout << "MULTICAST ";
        if (iface.flag & IFF_LOOPBACK)     cout << "LOOPBACK ";
        if (iface.flag & IFF_POINTOPOINT)  cout << "POINTOPOINT ";
        if (iface.flag & IFF_PROMISC)      cout << "PROMISC ";
        if (iface.flag & IFF_NOARP)        cout << "NOARP ";
        if (iface.flag & IFF_ALLMULTI)     cout << "ALLMULTI ";
        if (iface.flag & IFF_DEBUG)        cout << "DEBUG ";

        cout << '\n';
    }
}



