#include "core/Gate.h"
#include <stdexcept>

Gate::Gate(const std::string& name, std::size_t inputCount)
    : CircuitElement(name), inputs(inputCount, false), outputs(1, false) {}

int Gate::getInputCount() const { return static_cast<int>(inputs.size()); }
int Gate::getOutputCount() const { return static_cast<int>(outputs.size()); }

void Gate::setInput(std::size_t index, bool value) {
    if (index >= inputs.size()) throw std::out_of_range("Gate input index out of range");
    inputs[index] = value;
}

bool Gate::getOutput(std::size_t index) const {
    if (index >= outputs.size()) throw std::out_of_range("Gate output index out of range");
    return outputs[index];
}

const std::vector<bool>& Gate::getInputs() const { return inputs; }

void Gate::setOutput(std::size_t index, bool value) {
    if (index >= outputs.size()) throw std::out_of_range("Gate output index out of range");
    outputs[index] = value;
}
