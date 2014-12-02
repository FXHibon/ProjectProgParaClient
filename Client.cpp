#include "Client.hpp"

using namespace std;

Client::Client(string address, int port) {
    cout << "creating client (" << address << ", " << port << ")" << endl;
    this->mPort = port;
    this->mAddress = address;
}

void Client::connect() {
    // init some socket's related data
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2, 0), &WSAData);
    SOCKADDR_IN sin;
    sin.sin_addr.s_addr = inet_addr(this->mAddress.c_str());
    sin.sin_family = AF_INET;
    sin.sin_port = htons(this->mPort);

    // create the socket
    this->mSocket = socket(AF_INET, SOCK_STREAM, 0);
    // bind to the port to be used
    bind(this->mSocket, (SOCKADDR *) &sin, sizeof(sin));

    // connect the socket to the server
    // connect(...)
    this->mConnected = true;
    cout << "connection successful";
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

void Client::close() {
    if (this->mConnected) {
        closesocket(this->mSocket);
        WSACleanup();
    }
}