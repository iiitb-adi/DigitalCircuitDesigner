#include "analysis/TruthTableGenerator.h"
#include "simulation/Simulator.h"

#include <cstddef>
#include <stdexcept>
#include <vector>

SimulationResult TruthTableGenerator::generate(CircuitElement& circuit) const {
    const std::size_t inputCount = static_cast<std::size_t>(circuit.getInputCount());

    if (inputCount >= 20) {
        throw std::runtime_error("Truth table is too large to generate");
    }

    const std::size_t rowCount = static_cast<std::size_t>(1) << inputCount;
    std::vector<std::vector<bool>> rows;
    rows.reserve(rowCount);

    for (std::size_t value = 0; value < rowCount; ++value) {
        std::vector<bool> row(inputCount, false);

        for (std::size_t i = 0; i < inputCount; ++i) {
            row[i] = ((value >> (inputCount - 1 - i)) & 1U) != 0;
        }

        rows.push_back(row);
    }

    Simulator simulator;
    return simulator.simulate(circuit, rows);
}
