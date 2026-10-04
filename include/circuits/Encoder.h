#ifndef ENCODER_H
#define ENCODER_H

#include "core/CircuitElement.h"
#include <memory>

class Encoder : public CircuitElement {
public:
    Encoder();
    void evaluate() override;
    int getInputCount() const override;
    int getOutputCount() const override;
    void setInput(std::size_t index, bool value) override;
    bool getOutput(std::size_t index) const override;
    std::unique_ptr<CircuitElement> clone() const override;

private:
    bool inputs[4];
    bool outputs[2];
};

#endif
