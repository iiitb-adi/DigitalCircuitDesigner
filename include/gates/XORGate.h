#ifndef XOR_GATE_H
#define XOR_GATE_H

#include "core/Gate.h"
#include <memory>
#include "core/Connection.h"
#include "gates/NANDGate.h"

class XORGate : public Gate {
public:
    XORGate();
    void evaluate() override;
    std::unique_ptr<CircuitElement> clone() const override;

private:
    NANDGate first;
    NANDGate second;
    NANDGate third;
    NANDGate result;

    Connection firstToSecond;
    Connection firstToThird;
    Connection secondToResult;
    Connection thirdToResult;
};

#endif
