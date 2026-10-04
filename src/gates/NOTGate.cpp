#include "gates/NOTGate.h"

NOTGate::NOTGate()
    : Gate("NOT", 1),
      nand() {
}

void NOTGate::evaluate() {
    nand.setInput(0, getInputs()[0]);
    nand.setInput(1, getInputs()[0]);
    nand.evaluate();

    setOutput(0, nand.getOutput(0));
}

std::unique_ptr<CircuitElement> NOTGate::clone() const { return std::make_unique<NOTGate>(); }
