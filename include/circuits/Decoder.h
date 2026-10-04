#ifndef DECODER_H
#define DECODER_H

#include "core/CircuitElement.h"
#include <memory>

class Decoder : public CircuitElement {
public:
    Decoder();
    void evaluate() override;
    int getInputCount() const override;
    int getOutputCount() const override;
    void setInput(std::size_t index, bool value) override;
    bool getOutput(std::size_t index) const override;
    std::unique_ptr<CircuitElement> clone() const override;

private:
    bool inputs[2];
    bool outputs[4];
};

#endif
