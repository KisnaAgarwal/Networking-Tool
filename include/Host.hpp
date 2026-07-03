#include <ifaddrs.h>
#include <unordered_map>
#include <NetworkInterface.hpp>
#include <iostream>
using namespace std;



class Host{
    public: 
    string Hostname; 
    unordered_map <string ,NetworkInterface> HostInterface;
    void getName();
    void getInterface();
    void showNetworkInterface();
    void showFlags();
};