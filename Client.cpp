#include "Client.hpp"
#include <windows.h>

using namespace std;

Client::Client() {
    cout << "creating client ()" << endl;
    this->mState = ClientState::SERVER_CHOICE;
}

void Client::run() {

    while(true) {
        switch (this->mState) {
            case ClientState::SERVER_CHOICE:
                this->mState = this->handleServerChoice();
                break;

            case ClientState::CONNECTION:
                this->mState = this->handleConnection();
                break;

            case ClientState::FAILED:
                this->mState = this->handleFailed();
                break;

            case ClientState::CONNECTED:
                this->mState = this->handleConnected();
                break;

            case ClientState::WAITING:
                /*
                * Should be waiting (Thread.sleep() ?)
                * */
                break;

            case ClientState::GREETINGS:
                this->handleGreetings();
                break;
        }
    }
}

ClientState Client::handleServerChoice() {
    string serverIp;
    int serverPort;

    cout << endl << "Server IP (127.0.0.1 default):";
    cin >> serverIp;

    cout << endl << "Server port (3000 default):";
    cin >> serverPort;
    cout << endl;
    this->mAddress = serverIp;
    this->mPort = serverPort;

    return ClientState::CONNECTION;
}

ClientState Client::handleConnection() {
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
    this->mConnected = false;

    // connect to the given address:port
    if (connect(this->mSocket, (SOCKADDR *) &sin, sizeof(sin)) == SOCKET_ERROR) {
        cout << "connection error: " << ": " << WSAGetLastError() << endl;
        return ClientState::FAILED;
    }

    p.cl = this;
    p.soc = this->mSocket;

    hProcessThread = CreateThread(NULL, 0, &Client::threadLauncher, &p, 0, NULL);
    if (hProcessThread == NULL) {
        cerr << "connection error: " << GetLastError() << endl;
        return ClientState::FAILED;
    }

    this->mConnected = true;

    cout << "connection successful" << endl;
    return ClientState::CONNECTED;
}

ClientState Client::handleFailed() {
    cout << "An unexpected error has occured. Sorry fo the unconvenience" << endl;
    return ClientState::SERVER_CHOICE;
}

ClientState Client::handleConnected() {
    cout << "Currently connected to " << this->mAddress << ":" << this->mPort << endl;
    return ClientState::WAITING;
}

ClientState Client::handleGreetings() {
    /**
    * Should received HELLO and authenticate ASAP
    */
}

DWORD Client::clientThread() {
    SOCKET soc = this->getSocket();
    char buffer[50];
    int length = 1;
    this->mSocketActivated = true;

    /**
    * Listen and read server messages
    */
    while (this->mSocketActivated) {
        length = recv(soc, buffer, 50, 0);
        if (length == -1) {
            continue;
        }

        string message = bufferToString(buffer, length);
        this->interpret(message);
        this->mLastMsgReceived = message;
    }

    cout << "closing socket" << endl;
    closesocket(soc);
    return 0;
}

void Client::interpret(string message) {
    if (message == "hello") {
        this->mState = ClientState::GREETINGS;
        /*
        * Should unlock main thread ! (Thread.notify() ?)
        * So the run method would go in handleGreeting
        */
    }
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