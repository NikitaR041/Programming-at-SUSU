#ifndef STATEMACHINE_H
#define STATEMACHINE_H
class BaseStateMachine {
public:
virtual void signal(int s)=0;
virtual const char *state()const=0;
};
#endif
