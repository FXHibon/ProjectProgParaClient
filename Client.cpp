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

    HANDLE hProcessThread;
    struct thread_param p;

    // create the socket
    this->mSocket = socket(AF_INET, SOCK_STREAM, 0);

    // connect to the given address:port
    if (connect(this->mSocket, (SOCKADDR *) &sin, sizeof(sin)) == SOCKET_ERROR) {
        cout << "connection error" << ": " << WSAGetLastError() << endl;
    }

    this->mConnected = true;

    p.cl = this;
    p.soc = this->mSocket;

    hProcessThread = CreateThread(NULL, 0, &Client::threadLauncher, &p, 0, NULL);
    if (hProcessThread == NULL) {
        cerr << "CreateThread a échoué avec l'erreur " << GetLastError() << endl;
    }
    cout << "connection successful" << endl;
}

DWORD Client::clientThread() {
    SOCKET soc = this->getSocket();
    char buffer[50];
    int length = 1;

    cout << "Connected" << endl;

    while (true) {
        length = recv(soc, buffer, 50, 0);
        if (length == -1) {
            continue;
        }

        string message = bufferToString(buffer, length);

        cout << "Message : " << message << endl;
    }

    cout << "Disconnected" << endl;
    closesocket(soc);
    return 0;
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

std::string Client::bufferToString(char* buffer, int bufflen) {
    std::string ret(buffer, bufflen);
    return ret;
}