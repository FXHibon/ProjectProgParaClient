#ifndef CLIENT_H
#define CLIENT_H


#include <iostream>
#include <string>
#include <WinSock2.h>
#include <windef.h>

#include "state/AbstractState.hpp"

enum ClientState {
    SERVER_CHOICE,
    CONNECTION,
    CONNECTED,
    FAILED,
    GREETINGS,
    WAITING,
    AUTHENTICATED,
    BYE
};

/**
* Main Client class
*/
using namespace std;

class Client : public Interface {

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

    /**
    * Current state
    */
    AbstractState mState;

    /**
    * Last message received from the server
    */
    string mLastMsgReceived;

    /**
    * Is the socket activated?
    */
    bool mSocketActivated = true;

    /**
    * Last message received ID
    */
    int lastMessageId = -1;

    string lastInstruction = "";

    struct thread_param {
        Client *cl;
        SOCKET soc;
    };

    /**
    * Convert a buffer to a string object
    */
    std::string bufferToString(char* buffer, int bufflen);

    /**
    * Close current connection
    */
    void close();


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

    DWORD clientThread(/*SOCKET soc*/);

    /**
    * run the client thread (reading messages from server)
    * @param p Parameters for the thread
    */
    static DWORD WINAPI threadLauncher(void *p) {
        struct thread_param *Obj = reinterpret_cast<struct thread_param *>(p);
        Client *c = Obj->cl;
        return c->clientThread();
    }

    /**
    * Try to connect to the server
    */
    ClientState handleConnection();

    /**
    * Handle the server choice state
    */
    ClientState handleServerChoice();

    /**
    * Handler failed/error state
    */
    ClientState handleFailed();

    /**
    * Handler connected state
    */
    ClientState handleConnected();

    /**
    * Handle greetings
    */
    ClientState handleGreetings();

    ClientState handleAuthenticated();

    /**
    * Interpret incoming message
    * @param message Message from the server
    */
    void interpret(string message);

    void waitForMessage(string instruction);
    void waitForAnyMessage();

    /**
    * Send message to the server
    */
    virtual void sendMessage(string message);

public:
    /**
    * Main constructor
    */
    Client();

    /**
    * Start the client
    */
    void run();

    /********************************
    * getters and setters
    *********************************/

    int getPort() {
        return mPort;
    }

    string getAddress() {
        return mAddress;
    }

    ClientState getState() {
        return mState;
    }


    void setPort(int mPort) {
        Client::mPort = mPort;
    }

    void setAddress(string &mAddress) {
        Client::mAddress = mAddress;
    }

    void setCurrentState(ClientState const &mState) {
        Client::mState = mState;
    }

};

#endif