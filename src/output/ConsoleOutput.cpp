#include "output/ConsoleOutput.h"

#include <iostream>

void ConsoleOutput::write(
    const SimulationResult& result,
    const std::string& destination
) {
    (void)destination;

    for (const auto& name : result.getInputNames()) {
        std::cout << name << '\t';
    }

    for (const auto& name : result.getOutputNames()) {
        std::cout << name << '\t';
    }

    std::cout << '\n';

    for (const auto& row : result.getRows()) {
        for (bool value : row.inputs) {
            std::cout << value << '\t';
        }
        for (bool value : row.outputs) {
            std::cout << value << '\t';
        }
        std::cout << '\n';
    }
}
