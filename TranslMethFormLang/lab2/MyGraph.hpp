#ifndef MyGraph_H
#define MyGraph_H
#include "statemachine.hpp"
class MyGraph: public BaseStateMachine {
  int _state=2;
public:
void signal(int s);
const char* state()const;
};
#endif
