#include "gates/NANDGate.h"
NANDGate::NANDGate() : Gate("NAND", 2) {}
void NANDGate::evaluate() { bool a=getInputs()[0], b=getInputs()[1]; setOutput(0, !(a && b)); }

std::unique_ptr<CircuitElement> NANDGate::clone() const { return std::make_unique<NANDGate>(); }
