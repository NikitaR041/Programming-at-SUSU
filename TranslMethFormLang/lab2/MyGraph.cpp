#include "MyGraph.hpp"
void MyGraph::signal(int _s){
  _loop: switch(_state){
case 2:
break;
case 3:
break;
case 5:
if(true){
;
goto _loop;}
break;
case 6:
break;
case 8:
break;
case 13:
break;
case 15:
break;
case 16:
if(true){
;
goto _loop;}
break;
case 18:
if(true){
;
goto _loop;}
break;
case 25:
break;
case 28:
break;
case 29:
break;
case 30:
break;
case 37:
break;
case 42:
break;
}
}
const char* MyGraph::state()const {
  static const char *_statenames[44]={"", "", "", "state0", "", "state1", "state2", "", "state3", "", "", "", "", "state4", "", "state5", "state6", "", "state7", "", "", "", "", "", "", "state8", "", "", "state9", "state10", "state11", "", "", "", "", "", "", "error", "", "", "", "", "state12", ""};
  return _statenames[_state];
}
