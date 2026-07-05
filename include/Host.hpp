#include <ifaddrs.h>
#include <unordered_map>
#include <NetworkInterface.hpp>
#include <iostream>
#include <vector>
using namespace std;



class Host{
    public: 
    string Hostname; 
    unordered_map <string ,NetworkInterface> HostInterface;
    vector <string> DefaultDnsServers;
    void getName();
    void getInterface();
    void getInterfaceType(NetworkInterface & obj);
    void getDns();
    void getCurrentDns(NetworkInterface & obj);
    void showNetworkInterface();
    void showGeneralDns();

};