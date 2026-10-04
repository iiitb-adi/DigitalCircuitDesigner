#ifndef HALF_ADDER_H
#define HALF_ADDER_H
#include "core/Circuit.h"
#include <memory>
#include "gates/XORGate.h"
#include "gates/ANDGate.h"
class HalfAdder : public Circuit {
public:
    HalfAdder();
    std::unique_ptr<CircuitElement> clone() const override;
};
#endif
