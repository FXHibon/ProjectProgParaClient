#ifndef SENDER_H
#define SENDER_H

/**
* Classes implementing this interface
* are able to send a message
*/
class Sender {

public:

    Sender();

    /**
    * Send a message
    */
    virtual void sendMessage(std::string message);

};

#endif