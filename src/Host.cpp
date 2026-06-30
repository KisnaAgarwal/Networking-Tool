#include <iostream>
#include <Host.hpp>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>


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
                 sockaddr_in * ip4adr = (sockaddr_in*)curr->ifa_addr;
                 char ipaddress [16];
                 inet_ntop(AF_INET,&ip4adr->sin_addr ,ipaddress ,16);
                 cout<< "ip address :" <<ipaddress<<endl;
            }
        }
        curr = curr->ifa_next;
    }
    freeifaddrs(ptr);
}



