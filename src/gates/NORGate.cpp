#include "gates/NORGate.h"
NORGate::NORGate() : Gate("NOR", 2) {}
void NORGate::evaluate() { bool a=getInputs()[0], b=getInputs()[1]; setOutput(0, !(a || b)); }

std::unique_ptr<CircuitElement> NORGate::clone() const { return std::make_unique<NORGate>(); }
