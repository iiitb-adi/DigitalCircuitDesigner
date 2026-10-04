#include "core/Circuit.h"

#include <algorithm>
#include <stdexcept>
#include <unordered_map>

Circuit::Circuit(
    const std::string& name,
    std::size_t inputCount,
    std::size_t outputCount
)
    : CircuitElement(name),
      inputs(inputCount, false),
      outputs(outputCount, false),
      logicDepth(0) {
}

int Circuit::getInputCount() const {
    return static_cast<int>(inputs.size());
}

int Circuit::getOutputCount() const {
    return static_cast<int>(outputs.size());
}

void Circuit::setInput(std::size_t index, bool value) {
    if (index >= inputs.size()) {
        throw std::out_of_range("Circuit input index out of range");
    }
    inputs[index] = value;
}

bool Circuit::getOutput(std::size_t index) const {
    if (index >= outputs.size()) {
        throw std::out_of_range("Circuit output index out of range");
    }
    return outputs[index];
}

void Circuit::connect(
    CircuitElement& source,
    std::size_t sourceOutput,
    CircuitElement& destination,
    std::size_t destinationInput
) {
    internalConnections.emplace_back(
        source,
        sourceOutput,
        destination,
        destinationInput
    );
}

void Circuit::connectInput(
    std::size_t circuitInput,
    CircuitElement& destination,
    std::size_t destinationInput
) {
    if (circuitInput >= inputs.size()) {
        throw std::out_of_range("Circuit input index out of range");
    }

    if (destinationInput >= static_cast<std::size_t>(destination.getInputCount())) {
        throw std::out_of_range("Destination input index out of range");
    }

    inputBindings.push_back({
        circuitInput,
        &destination,
        destinationInput
    });
}

void Circuit::connectOutput(
    CircuitElement& source,
    std::size_t sourceOutput,
    std::size_t circuitOutput
) {
    if (sourceOutput >= static_cast<std::size_t>(source.getOutputCount())) {
        throw std::out_of_range("Source output index out of range");
    }

    if (circuitOutput >= outputs.size()) {
        throw std::out_of_range("Circuit output index out of range");
    }

    outputBindings.push_back({
        &source,
        sourceOutput,
        circuitOutput
    });
}

void Circuit::evaluate() {
    for (const auto& binding : inputBindings) {
        binding.destination->setInput(
            binding.destinationInput,
            inputs[binding.circuitInput]
        );
    }

    const std::size_t passes = std::max<std::size_t>(1, logicDepth + 1);

    for (std::size_t pass = 0; pass < passes; ++pass) {
        for (const auto& element : elements) {
            element->evaluate();

            for (const auto& connection : internalConnections) {
                if (connection.getSource() == element.get()) {
                    connection.propagate();
                }
            }
        }
    }

    for (const auto& binding : outputBindings) {
        outputs[binding.circuitOutput] =
            binding.source->getOutput(binding.sourceOutput);
    }
}

void Circuit::setLogicDepth(std::size_t depth) {
    logicDepth = depth;
}

std::unique_ptr<CircuitElement> Circuit::clone() const {
    auto copy = std::make_unique<Circuit>(getName(), inputs.size(), outputs.size());
    copy->logicDepth = logicDepth;
    copy->inputs = inputs;
    copy->outputs = outputs;

    std::unordered_map<const CircuitElement*, CircuitElement*> elementMap;
    elementMap.reserve(elements.size());

    for (const auto& element : elements) {
        auto clonedElement = element->clone();
        CircuitElement* clonedPtr = clonedElement.get();
        elementMap.emplace(element.get(), clonedPtr);
        copy->elements.push_back(std::move(clonedElement));
    }

    for (const auto& connection : internalConnections) {
        const CircuitElement* source = connection.getSource();
        const CircuitElement* destination = connection.getDestination();

        auto sourceIt = elementMap.find(source);
        auto destinationIt = elementMap.find(destination);
        if (sourceIt == elementMap.end() || destinationIt == elementMap.end()) {
            throw std::runtime_error("Failed to clone circuit connection");
        }

        copy->internalConnections.emplace_back(
            *sourceIt->second,
            connection.getSourceOutput(),
            *destinationIt->second,
            connection.getDestinationInput()
        );
    }

    for (const auto& binding : inputBindings) {
        auto destinationIt = elementMap.find(binding.destination);
        if (destinationIt == elementMap.end()) {
            throw std::runtime_error("Failed to clone circuit input binding");
        }

        copy->inputBindings.push_back({
            binding.circuitInput,
            destinationIt->second,
            binding.destinationInput
        });
    }

    for (const auto& binding : outputBindings) {
        auto sourceIt = elementMap.find(binding.source);
        if (sourceIt == elementMap.end()) {
            throw std::runtime_error("Failed to clone circuit output binding");
        }

        copy->outputBindings.push_back({
            sourceIt->second,
            binding.sourceOutput,
            binding.circuitOutput
        });
    }

    return copy;
}

