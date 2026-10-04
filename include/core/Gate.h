#ifndef GATE_H
#define GATE_H

#include "core/CircuitElement.h"
#include <cstddef>
#include <vector>

class Gate : public CircuitElement {
public:
    Gate(const std::string& name, std::size_t inputCount);
    int getInputCount() const override;
    int getOutputCount() const override;
    void setInput(std::size_t index, bool value) override;
    bool getOutput(std::size_t index) const override;

protected:
    const std::vector<bool>& getInputs() const;
    void setOutput(std::size_t index, bool value);

private:
    std::vector<bool> inputs;
    std::vector<bool> outputs;
};

#endif
