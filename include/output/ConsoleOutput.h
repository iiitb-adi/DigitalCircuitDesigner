#ifndef CONSOLE_OUTPUT_H
#define CONSOLE_OUTPUT_H

#include "output/Output.h"

class ConsoleOutput : public Output {
public:
    void write(
        const SimulationResult& result,
        const std::string& destination = ""
    ) override;
};

#endif
