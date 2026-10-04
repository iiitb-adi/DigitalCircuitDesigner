#ifndef RIPPLE_CARRY_ADDER_H
#define RIPPLE_CARRY_ADDER_H
#include "core/Circuit.h"
#include "circuits/FullAdder.h"
#include <memory>
#include <vector>
class RippleCarryAdder : public Circuit {
public:
    explicit RippleCarryAdder(std::size_t bitWidth=4);
    std::size_t getBitWidth() const;
    std::unique_ptr<CircuitElement> clone() const override;
private:
    std::size_t bitWidth;
};
#endif
