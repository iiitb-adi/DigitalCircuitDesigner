#include "core/Connection.h"
#include <stdexcept>

Connection::Connection()
    : source(nullptr), sourceOutput(0), destination(nullptr), destinationInput(0), connected(false) {}

Connection::Connection(CircuitElement& source, std::size_t sourceOutput,
                       CircuitElement& destination, std::size_t destinationInput)
    : Connection() {
    connect(source, sourceOutput, destination, destinationInput);
}

void Connection::connect(CircuitElement& source, std::size_t sourceOutput,
                         CircuitElement& destination, std::size_t destinationInput) {
    if (sourceOutput >= static_cast<std::size_t>(source.getOutputCount()))
        throw std::out_of_range("Source output index out of range: "+source.getName()+"["+std::to_string(sourceOutput)+"] count="+std::to_string(source.getOutputCount()));
    if (destinationInput >= static_cast<std::size_t>(destination.getInputCount()))
        throw std::out_of_range("Destination input index out of range");
    this->source = &source;
    this->sourceOutput = sourceOutput;
    this->destination = &destination;
    this->destinationInput = destinationInput;
    connected = true;
}

void Connection::propagate() const {
    if (!connected) throw std::runtime_error("Connection is not initialized");
    destination->setInput(destinationInput, source->getOutput(sourceOutput));
}

bool Connection::isConnected() const { return connected; }
const CircuitElement* Connection::getSource() const { return source; }
const CircuitElement* Connection::getDestination() const { return destination; }
std::size_t Connection::getSourceOutput() const { return sourceOutput; }
std::size_t Connection::getDestinationInput() const { return destinationInput; }
