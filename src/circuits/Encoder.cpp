#include "circuits/Encoder.h"
#include <stdexcept>

Encoder::Encoder() : CircuitElement("4-to-2 Encoder"), inputs{false, false, false, false}, outputs{false, false} {}

void Encoder::evaluate() {
    outputs[0] = false;
    outputs[1] = false;
    for (int i = 0; i < 4; ++i) {
        if (inputs[i]) {
            outputs[0] = (i & 2) != 0;
            outputs[1] = (i & 1) != 0;
            return;
        }
    }
}

int Encoder::getInputCount() const { return 4; }
int Encoder::getOutputCount() const { return 2; }

void Encoder::setInput(std::size_t index, bool value) {
    if (index >= 4) throw std::out_of_range("Encoder input index out of range");
    inputs[index] = value;
}

bool Encoder::getOutput(std::size_t index) const {
    if (index >= 2) throw std::out_of_range("Encoder output index out of range");
    return outputs[index];
}

std::unique_ptr<CircuitElement> Encoder::clone() const { return std::make_unique<Encoder>(*this); }
