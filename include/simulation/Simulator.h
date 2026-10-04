#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "core/CircuitElement.h"
#include "simulation/SimulationResult.h"

#include <vector>

class Simulator {
public:
    SimulationResult simulate(
        CircuitElement& circuit,
        const std::vector<std::vector<bool>>& inputRows
    ) const;

    std::size_t getLastWorkerCount() const;

private:
    mutable std::size_t lastWorkerCount = 1;
};

#endif
