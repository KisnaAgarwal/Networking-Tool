#include <Host.hpp>



int main(){
    Host user;
    user.getName();
    cout<<"Host Name :" <<user.Hostname<<endl;
    user.getInterface();
    user.showNetworkInterface();
    return 0;
}