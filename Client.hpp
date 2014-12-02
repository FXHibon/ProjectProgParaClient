#include <iostream>
#include <string>
#include <WinSock2.h>
#include <windef.h>

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

    /**
    * client connected or not
    */
    boolean mConnected;

    struct thread_param {
        Client *cl;
        SOCKET soc;
    };

public:
    /**
    * Main constructor
    */
    Client(string address, int port);

    /**
    * Try to connect to the server
    */
    void connectClient();

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

    /**
    * Close current connection
    */
    void close();

    /**
    * Send a single message to the server
    */
    void sendMessage(string message);

    DWORD clientThread(/*SOCKET soc*/);

    static DWORD WINAPI threadLauncher(void *p) {
        struct thread_param *Obj = reinterpret_cast<struct thread_param *>(p);
        Client *c = Obj->cl;
        return c->clientThread(/*Obj->soc*/);
    }
};