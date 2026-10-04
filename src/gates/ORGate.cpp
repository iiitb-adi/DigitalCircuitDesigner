#include "gates/ORGate.h"

ORGate::ORGate()
    : Gate("OR", 2),
      first(),
      second(),
      outputToFirst(),
      outputToSecond() {
    outputToFirst.connect(first, 0, second, 0);
    outputToSecond.connect(first, 0, second, 1);
}

void ORGate::evaluate() {
    first.setInput(0, getInputs()[0]);
    first.setInput(1, getInputs()[1]);
    first.evaluate();

    outputToFirst.propagate();
    outputToSecond.propagate();

    second.evaluate();
    setOutput(0, second.getOutput(0));
}

std::unique_ptr<CircuitElement> ORGate::clone() const { return std::make_unique<ORGate>(); }
