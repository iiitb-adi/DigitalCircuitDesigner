#include "circuits/FullAdder.h"
FullAdder::FullAdder():Circuit("FullAdder",3,2){
 auto& h1=addElement<HalfAdder>(); auto& h2=addElement<HalfAdder>(); auto& o=addElement<ORGate>();
 connectInput(0,h1,0); connectInput(1,h1,1); connectInput(2,h2,1);
 connect(h1,0,h2,0); connect(h1,1,o,0); connect(h2,1,o,1);
 connectOutput(h2,0,0); connectOutput(o,0,1); setLogicDepth(3);
}

std::unique_ptr<CircuitElement> FullAdder::clone() const { return std::make_unique<FullAdder>(); }
