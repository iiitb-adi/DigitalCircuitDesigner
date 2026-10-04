#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "core/CircuitElement.h"
#include <memory>

class Comparator : public CircuitElement {
public:
    Comparator();
    void evaluate() override;
    int getInputCount() const override;
    int getOutputCount() const override;
    void setInput(std::size_t index, bool value) override;
    bool getOutput(std::size_t index) const override;
    std::unique_ptr<CircuitElement> clone() const override;

private:
    bool inputs[8];
    bool outputs[3];
};

#endif
