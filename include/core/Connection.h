#ifndef CONNECTION_H
#define CONNECTION_H

#include "core/CircuitElement.h"
#include <cstddef>

class Connection {
public:
    Connection();
    Connection(CircuitElement& source, std::size_t sourceOutput,
               CircuitElement& destination, std::size_t destinationInput);
    void connect(CircuitElement& source, std::size_t sourceOutput,
                 CircuitElement& destination, std::size_t destinationInput);
    void propagate() const;
    bool isConnected() const;
    const CircuitElement* getSource() const;
    const CircuitElement* getDestination() const;
    std::size_t getSourceOutput() const;
    std::size_t getDestinationInput() const;

private:
    CircuitElement* source;
    std::size_t sourceOutput;
    CircuitElement* destination;
    std::size_t destinationInput;
    bool connected;
};

#endif
