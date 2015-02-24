#ifndef SENDER_H
#define SENDER_H

/**
* Classes implementing this interface
* are able to send a message
*/
class Sender {

public:

    /**
    * Send a message
    */
    virtual void sendMessage(std::string message) = 0;

};

#endif