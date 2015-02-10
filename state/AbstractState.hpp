#ifndef ABSTRACTSTATE_H
#define ABSTRACTSTATE_H

#include "../interfaces/Sender.hpp"

using namespace std;

/**
* Represents an abstract state
*/
class AbstractState {

private:

    /**
    * Sender reference
    */
    Sender mSender;

public:

/**
    * Main constructor
    * @param sender Reference to a sender class
    * We need it to be able to communicate with the main thread
    */
    AbstractState(Sender sender);

    /**
    * Core method: process the state
    */
    virtual void handle();

    /**
    * getter
    */
    Sender const &getSender() const {
        return this->mSender;
    }

};

#endif