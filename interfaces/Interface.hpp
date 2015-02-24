#ifndef INTERFACE_H
#define INTERFACE_H

#include "../state/AbstractState.hpp"

/**
* Link between Client and *State to avoid cyclic dependencies
*/
class Interface {
public:
    void setPort(int);

    void setAddress(std::string);

    void setCurrentState(AbstractState);

private:
};

#endif