#include "output/CSVOutput.h"

#include <fstream>
#include <stdexcept>

void CSVOutput::write(
    const SimulationResult& result,
    const std::string& destination
) {
    std::ofstream file(destination);
    if (!file) {
        throw std::runtime_error("Cannot open CSV output: " + destination);
    }

    bool first = true;

    for (const auto& name : result.getInputNames()) {
        if (!first) file << ',';
        file << name;
        first = false;
    }

    for (const auto& name : result.getOutputNames()) {
        if (!first) file << ',';
        file << name;
        first = false;
    }

    file << '\n';

    for (const auto& row : result.getRows()) {
        first = true;

        for (bool value : row.inputs) {
            if (!first) file << ',';
            file << value;
            first = false;
        }

        for (bool value : row.outputs) {
            if (!first) file << ',';
            file << value;
            first = false;
        }

        file << '\n';
    }
}
