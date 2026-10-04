#include "circuits/Comparator.h"
#include <stdexcept>

Comparator::Comparator() : CircuitElement("4-bit Comparator"), inputs{false, false, false, false, false, false, false, false}, outputs{false, false, false} {}

void Comparator::evaluate() {
    unsigned int a = 0;
    unsigned int b = 0;
    for (int i = 0; i < 4; ++i) {
        if (inputs[i]) a |= (1U << i);
        if (inputs[4 + i]) b |= (1U << i);
    }
    outputs[0] = a > b;
    outputs[1] = a == b;
    outputs[2] = a < b;
}

int Comparator::getInputCount() const { return 8; }
int Comparator::getOutputCount() const { return 3; }

void Comparator::setInput(std::size_t index, bool value) {
    if (index >= 8) throw std::out_of_range("Comparator input index out of range");
    inputs[index] = value;
}

bool Comparator::getOutput(std::size_t index) const {
    if (index >= 3) throw std::out_of_range("Comparator output index out of range");
    return outputs[index];
}

std::unique_ptr<CircuitElement> Comparator::clone() const { return std::make_unique<Comparator>(*this); }
