#include <string>
#include "Client.hpp"

using namespace std;

Client::Client(string address, int port) {
    cout << "creating client (" << address << ", " << port << ")" << endl;
    this->mPort = port;
    this->mAddress = address;
}

void Client::connect() {

}

int Client::getPort() const {
    return this->mPort;
}

string Client::getAddress() const {
    return this->mAddress;
}

SOCKET Client::getSocket() const {
    return this->mSocket;
}