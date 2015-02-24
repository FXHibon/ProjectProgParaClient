#ifndef ABSTRACTSTATE_H
#define ABSTRACTSTATE_H

#include "../interfaces/Interface.hpp"

using namespace std;

/**
* Represents an abstract state
*/
class AbstractState {

public:

    /**
    * Core method: process the state
    * @param Reference to the client (which is the called of State.handle)
    */
    virtual void handle(Interface);
};

#endif