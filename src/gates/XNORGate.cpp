#include "gates/XNORGate.h"

XNORGate::XNORGate()
    : Gate("XNOR", 2),
      xorGate(),
      inverter(),
      xorToInverterA(),
      xorToInverterB() {
    xorToInverterA.connect(xorGate, 0, inverter, 0);
    xorToInverterB.connect(xorGate, 0, inverter, 1);
}

void XNORGate::evaluate() {
    xorGate.setInput(0, getInputs()[0]);
    xorGate.setInput(1, getInputs()[1]);
    xorGate.evaluate();

    xorToInverterA.propagate();
    xorToInverterB.propagate();
    inverter.evaluate();

    setOutput(0, inverter.getOutput(0));
}

std::unique_ptr<CircuitElement> XNORGate::clone() const { return std::make_unique<XNORGate>(); }
