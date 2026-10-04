#ifndef TRUTH_TABLE_GENERATOR_H
#define TRUTH_TABLE_GENERATOR_H

#include "core/CircuitElement.h"
#include "simulation/SimulationResult.h"

class TruthTableGenerator {
public:
    SimulationResult generate(CircuitElement& circuit) const;
};

#endif
