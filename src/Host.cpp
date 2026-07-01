#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Host.hpp"

using namespace std;




void  Host::showName(){
    if(gethostname(name,256) ==-1){
        cout<<"error in host name";
    }
    cout<< "Host name :" <<name<<endl;
}

void Host::showInterface(){
    if(getifaddrs(&ptr)==-1){
        cout<<"error in network intefaces" ;
    }
    struct ifaddrs * curr;
    curr = ptr;

    while(curr!=NULL){
        cout<<"Interface :"<<curr->ifa_name<<endl;


        if(curr->ifa_addr != nullptr){
            if(curr->ifa_addr->sa_family==AF_INET) { //check if the network interface address is same as IP4
                //for IPv4 address
                 sockaddr_in * ip4adr = (sockaddr_in*)curr->ifa_addr; //typecaast into sockaddr_in 
                 char ipaddress [INET_ADDRSTRLEN];
                 if(inet_ntop(AF_INET,&ip4adr->sin_addr ,ipaddress ,INET_ADDRSTRLEN)){ //convert from binary to 
                     cout<< "IPv4 :" <<ipaddress<<endl;
                 }else{
                    perror("getifaddrs");
                 }
            }else if (curr->ifa_addr->sa_family ==AF_INET6){ //for IPv6 address
                sockaddr_in6 * ip6adr = (sockaddr_in6*)curr->ifa_addr;
                char ipaddress [INET6_ADDRSTRLEN];
                if(inet_ntop(AF_INET6 ,&ip6adr->sin6_addr , ipaddress ,INET6_ADDRSTRLEN )){
                    cout<<"IPv6 :"<<ipaddress<<endl;
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
                        cout<<"Subnet Mask :"<<subnet_mask<<endl;
                    }else{
                        perror("inet_ntop");
                    }
                }
                // for ipv6
                 else if(curr->ifa_netmask->sa_family==AF_INET6){
                    sockaddr_in6 * subnet_v6 = (sockaddr_in6*)curr->ifa_netmask;
                    char subnet_mask [INET6_ADDRSTRLEN];
                    if(inet_ntop(AF_INET6,&subnet_v6->sin6_addr ,subnet_mask ,INET6_ADDRSTRLEN)){
                        cout << "Family: " << curr->ifa_addr->sa_family << endl;
                        cout<<"Subnet Mask :"<<subnet_mask<<endl;
                    }else{
                        perror("inet_ntop");
                    }
                }
            }


        curr = curr->ifa_next;
    }
    freeifaddrs(ptr);
}



