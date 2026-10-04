#include "simulation/SimulationResult.h"

void SimulationResult::setInputNames(const std::vector<std::string>& names) {
    inputNames = names;
}

void SimulationResult::setOutputNames(const std::vector<std::string>& names) {
    outputNames = names;
}

void SimulationResult::addRow(
    const std::vector<bool>& inputs,
    const std::vector<bool>& outputs
) {
    rows.push_back({inputs, outputs});
}

const std::vector<std::string>& SimulationResult::getInputNames() const {
    return inputNames;
}

const std::vector<std::string>& SimulationResult::getOutputNames() const {
    return outputNames;
}

const std::vector<SimulationRow>& SimulationResult::getRows() const {
    return rows;
}

std::size_t SimulationResult::rowCount() const {
    return rows.size();
}
