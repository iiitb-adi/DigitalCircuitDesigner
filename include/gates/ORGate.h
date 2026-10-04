#ifndef OR_GATE_H
#define OR_GATE_H

#include "core/Gate.h"
#include <memory>
#include "core/Connection.h"
#include "gates/NORGate.h"

class ORGate : public Gate {
public:
    ORGate();
    void evaluate() override;
    std::unique_ptr<CircuitElement> clone() const override;

private:
    NORGate first;
    NORGate second;
    Connection outputToFirst;
    Connection outputToSecond;
};

#endif
