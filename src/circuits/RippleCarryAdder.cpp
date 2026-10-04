#include "circuits/RippleCarryAdder.h"
#include <stdexcept>
#include <vector>

RippleCarryAdder::RippleCarryAdder(std::size_t width)
    : Circuit("RippleCarryAdder", 2 * width + 1, width + 1), bitWidth(width) {
    if (width == 0) throw std::invalid_argument("RippleCarryAdder width must be positive");

    std::vector<FullAdder*> adders;
    adders.reserve(width);
    for (std::size_t i = 0; i < width; ++i) adders.push_back(&addElement<FullAdder>());

    for (std::size_t i = 0; i < width; ++i) {
        connectInput(i, *adders[i], 0);
        connectInput(width + i, *adders[i], 1);
        connectOutput(*adders[i], 0, i);
        if (i == 0) connectInput(2 * width, *adders[i], 2);
        else connect(*adders[i - 1], 1, *adders[i], 2);
    }
    connectOutput(*adders.back(), 1, width);
    setLogicDepth(width * 3);
}

std::size_t RippleCarryAdder::getBitWidth() const { return bitWidth; }

std::unique_ptr<CircuitElement> RippleCarryAdder::clone() const { return std::make_unique<RippleCarryAdder>(bitWidth); }
