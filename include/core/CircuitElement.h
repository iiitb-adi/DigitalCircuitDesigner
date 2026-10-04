#ifndef CIRCUIT_ELEMENT_H
#define CIRCUIT_ELEMENT_H

#include <cstddef>
#include <memory>
#include <string>

class CircuitElement {
public:
    explicit CircuitElement(const std::string& name);
    virtual ~CircuitElement() = default;

    const std::string& getName() const;
    virtual std::unique_ptr<CircuitElement> clone() const = 0;

    virtual void evaluate() = 0;
    virtual int getInputCount() const = 0;
    virtual int getOutputCount() const = 0;
    virtual void setInput(std::size_t index, bool value) = 0;
    virtual bool getOutput(std::size_t index) const = 0;

private:
    std::string name;
};

#endif
