#ifndef FULL_ADDER_H
#define FULL_ADDER_H
#include "core/Circuit.h"
#include "circuits/HalfAdder.h"
#include "gates/ORGate.h"
class FullAdder : public Circuit {
public: FullAdder();
    std::unique_ptr<CircuitElement> clone() const override;
};
#endif
