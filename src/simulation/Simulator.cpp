#include "simulation/Simulator.h"

#include <algorithm>
#include <atomic>
#include <exception>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>

SimulationResult Simulator::simulate(
    CircuitElement& circuit,
    const std::vector<std::vector<bool>>& inputRows
) const {
    SimulationResult result;

    std::vector<std::string> inputNames;
    std::vector<std::string> outputNames;

    for (int i = 0; i < circuit.getInputCount(); ++i) {
        inputNames.push_back("I" + std::to_string(i));
    }

    for (int i = 0; i < circuit.getOutputCount(); ++i) {
        outputNames.push_back("O" + std::to_string(i));
    }

    result.setInputNames(inputNames);
    result.setOutputNames(outputNames);

    if (inputRows.empty()) {
        lastWorkerCount = 0;
        return result;
    }

    for (const auto& row : inputRows) {
        if (row.size() != static_cast<std::size_t>(circuit.getInputCount())) {
            throw std::invalid_argument("Input row has incorrect width");
        }
    }

    const unsigned int hardwareThreads = std::thread::hardware_concurrency();
    const std::size_t availableThreads = hardwareThreads == 0 ? 1 : hardwareThreads;
    const std::size_t workerCount = std::min(availableThreads, inputRows.size());
    lastWorkerCount = workerCount;

    std::vector<SimulationRow> rows(inputRows.size());
    std::atomic<std::size_t> nextIndex{0};
    std::exception_ptr firstException;
    std::mutex exceptionMutex;

    auto worker = [&]() {
        try {
            // Every worker gets its own circuit instance. Circuit evaluation mutates
            // gate inputs/outputs, so sharing one Circuit between threads would race.
            auto workerCircuit = circuit.clone();

            while (true) {
                const std::size_t index = nextIndex.fetch_add(1, std::memory_order_relaxed);
                if (index >= inputRows.size()) {
                    break;
                }

                const auto& row = inputRows[index];

                for (std::size_t i = 0; i < row.size(); ++i) {
                    workerCircuit->setInput(i, row[i]);
                }

                workerCircuit->evaluate();

                std::vector<bool> outputs;
                outputs.reserve(static_cast<std::size_t>(workerCircuit->getOutputCount()));
                for (int i = 0; i < workerCircuit->getOutputCount(); ++i) {
                    outputs.push_back(workerCircuit->getOutput(i));
                }

                rows[index] = {row, std::move(outputs)};
            }
        } catch (...) {
            std::lock_guard<std::mutex> lock(exceptionMutex);
            if (!firstException) {
                firstException = std::current_exception();
            }
        }
    };

    std::vector<std::thread> workers;
    workers.reserve(workerCount);
    for (std::size_t i = 0; i < workerCount; ++i) {
        workers.emplace_back(worker);
    }

    for (auto& thread : workers) {
        thread.join();
    }

    if (firstException) {
        std::rethrow_exception(firstException);
    }

    for (auto& row : rows) {
        result.addRow(row.inputs, row.outputs);
    }

    return result;
}

std::size_t Simulator::getLastWorkerCount() const {
    return lastWorkerCount;
}
