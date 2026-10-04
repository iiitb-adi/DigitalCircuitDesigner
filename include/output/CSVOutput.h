#ifndef CSV_OUTPUT_H
#define CSV_OUTPUT_H

#include "output/Output.h"

class CSVOutput : public Output {
public:
    void write(
        const SimulationResult& result,
        const std::string& destination
    ) override;
};

#endif
