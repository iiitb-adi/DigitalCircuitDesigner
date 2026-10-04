#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "core/CircuitElement.h"
#include "core/Connection.h"

#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include <utility>

struct InputBinding {
    std::size_t circuitInput;
    CircuitElement* destination;
    std::size_t destinationInput;
};

struct OutputBinding {
    CircuitElement* source;
    std::size_t sourceOutput;
    std::size_t circuitOutput;
};

class Circuit : public CircuitElement {
public:
    Circuit(const std::string& name, std::size_t inputCount, std::size_t outputCount);

    int getInputCount() const override;
    int getOutputCount() const override;
    void setInput(std::size_t index, bool value) override;
    bool getOutput(std::size_t index) const override;
    void evaluate() override;
    std::unique_ptr<CircuitElement> clone() const override;

    template <typename T, typename... Args>
    T& addElement(Args&&... args) {
        auto element = std::make_unique<T>(std::forward<Args>(args)...);
        T& reference = *element;
        elements.push_back(std::move(element));
        return reference;
    }

    void connect(
        CircuitElement& source,
        std::size_t sourceOutput,
        CircuitElement& destination,
        std::size_t destinationInput
    );

    void connectInput(
        std::size_t circuitInput,
        CircuitElement& destination,
        std::size_t destinationInput
    );

    void connectOutput(
        CircuitElement& source,
        std::size_t sourceOutput,
        std::size_t circuitOutput
    );

    void setLogicDepth(std::size_t depth);

private:
    std::vector<bool> inputs;
    std::vector<bool> outputs;
    std::vector<std::unique_ptr<CircuitElement>> elements;
    std::vector<Connection> internalConnections;
    std::vector<InputBinding> inputBindings;
    std::vector<OutputBinding> outputBindings;
    std::size_t logicDepth;
};

#endif
