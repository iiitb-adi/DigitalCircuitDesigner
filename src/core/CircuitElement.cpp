#include "core/CircuitElement.h"

CircuitElement::CircuitElement(const std::string& name) : name(name) {}

const std::string& CircuitElement::getName() const { return name; }
