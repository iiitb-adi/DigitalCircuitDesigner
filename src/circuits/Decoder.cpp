#include "circuits/Decoder.h"
#include <stdexcept>

Decoder::Decoder() : CircuitElement("2-to-4 Decoder"), inputs{false, false}, outputs{false, false, false, false} {}

void Decoder::evaluate() {
    for (bool& output : outputs) output = false;
    const std::size_t selected = (static_cast<std::size_t>(inputs[0]) << 1) | static_cast<std::size_t>(inputs[1]);
    outputs[selected] = true;
}

int Decoder::getInputCount() const { return 2; }
int Decoder::getOutputCount() const { return 4; }

void Decoder::setInput(std::size_t index, bool value) {
    if (index >= 2) throw std::out_of_range("Decoder input index out of range");
    inputs[index] = value;
}

bool Decoder::getOutput(std::size_t index) const {
    if (index >= 4) throw std::out_of_range("Decoder output index out of range");
    return outputs[index];
}

std::unique_ptr<CircuitElement> Decoder::clone() const { return std::make_unique<Decoder>(*this); }
