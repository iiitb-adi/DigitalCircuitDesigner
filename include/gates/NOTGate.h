#ifndef NOT_GATE_H
#define NOT_GATE_H

#include "core/Gate.h"
#include <memory>
#include "gates/NANDGate.h"

class NOTGate : public Gate {
public:
    NOTGate();
    void evaluate() override;
    std::unique_ptr<CircuitElement> clone() const override;

private:
    NANDGate nand;
};

#endif
