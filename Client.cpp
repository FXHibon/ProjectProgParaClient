#include "Client.hpp"

using namespace std;

Client::Client(string address, int port) {
    cout << "creating client (" << address << ", " << port << ")" << endl;
    this->mPort = port;
    this->mAddress = address;
}

void Client::connectClient() {
    // init some socket's related data
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2, 2), &WSAData);
    SOCKADDR_IN sin;
    sin.sin_addr.s_addr = inet_addr(this->mAddress.c_str());
    sin.sin_family = AF_INET;
    sin.sin_port = htons(this->mPort);

    // create the socket
    this->mSocket = socket(AF_INET, SOCK_STREAM, 0);

    // connect to the given address:port
    if (connect(this->mSocket, (SOCKADDR *) &sin, sizeof(sin)) == SOCKET_ERROR) {
        cout << "connection error" << ": " << WSAGetLastError() << endl;
    }

    this->mConnected = true;
    cout << "connection successful" << endl;
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
        cout << "closing connections" << endl;
        this->sendMessage("0");
        closesocket(this->mSocket);
        WSACleanup();
    }
}

void Client::sendMessage(string message) {
    send(this->mSocket, message.c_str(), (int) strlen(message.c_str()), 0);
}