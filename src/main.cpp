#include <Host.hpp>



int main(){
    Host user;
    user.getName();
    cout<<"Host Name :" <<user.Hostname<<endl;
    user.getDns();
    user.showGeneralDns();
    user.getInterface();
    user.getGateway();
    user.showNetworkInterface();
    return 0;
}