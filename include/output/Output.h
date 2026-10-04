#ifndef OUTPUT_H
#define OUTPUT_H

#include "simulation/SimulationResult.h"

#include <string>

class Output {
public:
    virtual ~Output() = default;
    virtual void write(
        const SimulationResult& result,
        const std::string& destination = ""
    ) = 0;
};

#endif
