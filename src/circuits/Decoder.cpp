#include "circuits/Decoder.h"
#include "gates/ANDGate.h"
#include "gates/NOTGate.h"

Decoder::Decoder()
    : CircuitElement("2-to-4 Decoder"),
      circuit("2-to-4 Decoder Internal", 2, 4) {

    auto& notA = circuit.addElement<NOTGate>();
    auto& notB = circuit.addElement<NOTGate>();

    auto& y0 = circuit.addElement<ANDGate>();
    auto& y1 = circuit.addElement<ANDGate>();
    auto& y2 = circuit.addElement<ANDGate>();
    auto& y3 = circuit.addElement<ANDGate>();

    circuit.connectInput(0, notA, 0);
    circuit.connectInput(1, notB, 0);

    // Y0 = !A AND !B
    circuit.connect(notA, 0, y0, 0);
    circuit.connect(notB, 0, y0, 1);

    // Y1 = !A AND B
    circuit.connect(notA, 0, y1, 0);
    circuit.connectInput(1, y1, 1);

    // Y2 = A AND !B
    circuit.connectInput(0, y2, 0);
    circuit.connect(notB, 0, y2, 1);

    // Y3 = A AND B
    circuit.connectInput(0, y3, 0);
    circuit.connectInput(1, y3, 1);

    circuit.connectOutput(y0, 0, 0);
    circuit.connectOutput(y1, 0, 1);
    circuit.connectOutput(y2, 0, 2);
    circuit.connectOutput(y3, 0, 3);

    circuit.setLogicDepth(1);
}

void Decoder::evaluate() {
    circuit.evaluate();
}

int Decoder::getInputCount() const {
    return circuit.getInputCount();
}

int Decoder::getOutputCount() const {
    return circuit.getOutputCount();
}

void Decoder::setInput(std::size_t index, bool value) {
    circuit.setInput(index, value);
}

bool Decoder::getOutput(std::size_t index) const {
    return circuit.getOutput(index);
}

std::unique_ptr<CircuitElement> Decoder::clone() const {
    return std::make_unique<Decoder>();
}
