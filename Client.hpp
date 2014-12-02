#include <iostream>
#include <string>
#include <WinSock2.h>

/**
* Main Client class
*/
using namespace std;

class Client {

private:
    /**
    * Server connection port
    */
    int mPort;
    /**
    * Server address
    */
    string mAddress;
    /**
    * Client socket
    */
    SOCKET mSocket;

public:
    /**
    * Main constructor
    */
    Client(string address, int port);

    /**
    * Try to connect to the server
    */
    void connect();

    /**
    * get the server's port
    */
    int getPort() const;

    /**
    * get the server's address
    */
    string getAddress() const;

    /**
    * get the client's socket
    */
    SOCKET getSocket() const;
};