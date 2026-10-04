#include "circuits/HalfAdder.h"
HalfAdder::HalfAdder():Circuit("HalfAdder",2,2){
 auto& x=addElement<XORGate>(); auto& a=addElement<ANDGate>();
 connectInput(0,x,0); connectInput(1,x,1); connectInput(0,a,0); connectInput(1,a,1);
 connectOutput(x,0,0); connectOutput(a,0,1); setLogicDepth(1);
}

std::unique_ptr<CircuitElement> HalfAdder::clone() const { return std::make_unique<HalfAdder>(); }
