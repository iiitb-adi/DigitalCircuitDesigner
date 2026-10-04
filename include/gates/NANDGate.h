#ifndef NAND_GATE_H
#define NAND_GATE_H
#include "core/Gate.h"
#include <memory>
class NANDGate : public Gate {
public:
    NANDGate();
    void evaluate() override;
    std::unique_ptr<CircuitElement> clone() const override;
};
#endif
