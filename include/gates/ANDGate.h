#ifndef AND_GATE_H
#define AND_GATE_H

#include "core/Gate.h"
#include <memory>
#include "core/Connection.h"
#include "gates/NANDGate.h"

class ANDGate : public Gate {
public:
    ANDGate();
    void evaluate() override;
    std::unique_ptr<CircuitElement> clone() const override;

private:
    NANDGate first;
    NANDGate second;
    Connection outputToFirst;
    Connection outputToSecond;
};

#endif
