#include "circuits/Encoder.h"
#include "gates/ORGate.h"

Encoder::Encoder()
    : CircuitElement("4-to-2 Encoder"),
      circuit("4-to-2 Encoder Internal", 4, 2) {

    auto& msb = circuit.addElement<ORGate>();
    auto& lsb = circuit.addElement<ORGate>();

    // One-hot encoder:
    // Y0 Y1 Y2 Y3 -> A B

    circuit.connectInput(2, msb, 0);
    circuit.connectInput(3, msb, 1);

    circuit.connectInput(1, lsb, 0);
    circuit.connectInput(3, lsb, 1);

    circuit.connectOutput(msb, 0, 0);
    circuit.connectOutput(lsb, 0, 1);
}

void Encoder::evaluate() {
    circuit.evaluate();
}

int Encoder::getInputCount() const {
    return circuit.getInputCount();
}

int Encoder::getOutputCount() const {
    return circuit.getOutputCount();
}

void Encoder::setInput(std::size_t index, bool value) {
    circuit.setInput(index, value);
}

bool Encoder::getOutput(std::size_t index) const {
    return circuit.getOutput(index);
}

std::unique_ptr<CircuitElement> Encoder::clone() const {
    return std::make_unique<Encoder>();
}
