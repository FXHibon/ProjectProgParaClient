#ifndef SERVER_CHOICE_STATE_H
#define SERVER_CHOICE_STATE_H

/**
* Represents ... state
*/
class ServerChoiceState : public AbstractState {
public:
    virtual void handle(Interface *) = 0;
};

#endif