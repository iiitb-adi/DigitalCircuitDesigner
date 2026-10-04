#ifndef SIMULATION_RESULT_H
#define SIMULATION_RESULT_H

#include <cstddef>
#include <string>
#include <vector>

struct SimulationRow {
    std::vector<bool> inputs;
    std::vector<bool> outputs;
};

class SimulationResult {
public:
    void setInputNames(const std::vector<std::string>& names);
    void setOutputNames(const std::vector<std::string>& names);
    void addRow(const std::vector<bool>& inputs, const std::vector<bool>& outputs);

    const std::vector<std::string>& getInputNames() const;
    const std::vector<std::string>& getOutputNames() const;
    const std::vector<SimulationRow>& getRows() const;
    std::size_t rowCount() const;

private:
    std::vector<std::string> inputNames;
    std::vector<std::string> outputNames;
    std::vector<SimulationRow> rows;
};

#endif
