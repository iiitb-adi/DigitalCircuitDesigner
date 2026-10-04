#ifndef XNOR_GATE_H
#define XNOR_GATE_H

#include "core/Gate.h"
#include <memory>
#include "core/Connection.h"
#include "gates/NANDGate.h"
#include "gates/XORGate.h"

class XNORGate : public Gate {
public:
    XNORGate();
    void evaluate() override;
    std::unique_ptr<CircuitElement> clone() const override;

private:
    XORGate xorGate;
    NANDGate inverter;
    Connection xorToInverterA;
    Connection xorToInverterB;
};

#endif
