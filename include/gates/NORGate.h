#ifndef NOR_GATE_H
#define NOR_GATE_H
#include "core/Gate.h"
#include <memory>
class NORGate : public Gate {
public:
    NORGate();
    void evaluate() override;
    std::unique_ptr<CircuitElement> clone() const override;
};
#endif
