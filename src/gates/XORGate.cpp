#include "gates/XORGate.h"

XORGate::XORGate()
    : Gate("XOR", 2),
      first(),
      second(),
      third(),
      result(),
      firstToSecond(),
      firstToThird(),
      secondToResult(),
      thirdToResult() {
    firstToSecond.connect(first, 0, second, 1);
    firstToThird.connect(first, 0, third, 1);
    secondToResult.connect(second, 0, result, 0);
    thirdToResult.connect(third, 0, result, 1);
}

void XORGate::evaluate() {
    first.setInput(0, getInputs()[0]);
    first.setInput(1, getInputs()[1]);
    first.evaluate();

    second.setInput(0, getInputs()[0]);
    firstToSecond.propagate();
    second.evaluate();

    third.setInput(0, getInputs()[1]);
    firstToThird.propagate();
    third.evaluate();

    secondToResult.propagate();
    thirdToResult.propagate();
    result.evaluate();

    setOutput(0, result.getOutput(0));
}

std::unique_ptr<CircuitElement> XORGate::clone() const { return std::make_unique<XORGate>(); }
