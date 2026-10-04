#include "analysis/TruthTableGenerator.h"
#include "circuits/FullAdder.h"
#include "circuits/HalfAdder.h"
#include "circuits/RippleCarryAdder.h"
#include "circuits/Decoder.h"
#include "circuits/Encoder.h"
#include "circuits/Comparator.h"
#include "gates/ANDGate.h"
#include "gates/NANDGate.h"
#include "gates/NORGate.h"
#include "gates/NOTGate.h"
#include "gates/ORGate.h"
#include "gates/XNORGate.h"
#include "gates/XORGate.h"
#include "output/CSVOutput.h"
#include "simulation/Simulator.h"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

void testTwoInputGate(CircuitElement& gate, const int expected[4]) {
    int index = 0;

    for (int a = 0; a <= 1; ++a) {
        for (int b = 0; b <= 1; ++b) {
            gate.setInput(0, a);
            gate.setInput(1, b);
            gate.evaluate();
            assert(gate.getOutput(0) == expected[index++]);
        }
    }
}

void testGates() {
    const int nandExpected[] = {1, 1, 1, 0};
    const int norExpected[] = {1, 0, 0, 0};
    const int andExpected[] = {0, 0, 0, 1};
    const int orExpected[] = {0, 1, 1, 1};
    const int xorExpected[] = {0, 1, 1, 0};
    const int xnorExpected[] = {1, 0, 0, 1};

    NANDGate nandGate;
    NORGate norGate;
    ANDGate andGate;
    ORGate orGate;
    XORGate xorGate;
    XNORGate xnorGate;

    testTwoInputGate(nandGate, nandExpected);
    testTwoInputGate(norGate, norExpected);
    testTwoInputGate(andGate, andExpected);
    testTwoInputGate(orGate, orExpected);
    testTwoInputGate(xorGate, xorExpected);
    testTwoInputGate(xnorGate, xnorExpected);

    NOTGate notGate;
    notGate.setInput(0, false);
    notGate.evaluate();
    assert(notGate.getOutput(0) == true);

    notGate.setInput(0, true);
    notGate.evaluate();
    assert(notGate.getOutput(0) == false);
}

void testAdders() {
    HalfAdder halfAdder;
    const int expected[4][2] = {
        {0, 0},
        {1, 0},
        {1, 0},
        {0, 1}
    };

    int row = 0;
    for (int a = 0; a <= 1; ++a) {
        for (int b = 0; b <= 1; ++b) {
            halfAdder.setInput(0, a);
            halfAdder.setInput(1, b);
            halfAdder.evaluate();

            assert(halfAdder.getOutput(0) == expected[row][0]);
            assert(halfAdder.getOutput(1) == expected[row][1]);
            ++row;
        }
    }

    FullAdder fullAdder;
    for (int a = 0; a <= 1; ++a) {
        for (int b = 0; b <= 1; ++b) {
            for (int carry = 0; carry <= 1; ++carry) {
                fullAdder.setInput(0, a);
                fullAdder.setInput(1, b);
                fullAdder.setInput(2, carry);
                fullAdder.evaluate();

                const int sum = a + b + carry;
                assert(fullAdder.getOutput(0) == (sum & 1));
                assert(fullAdder.getOutput(1) == (sum >= 2));
            }
        }
    }
}

void testRippleCarryAdder() {
    RippleCarryAdder adder(4);

    const int a = 8;
    const int b = 4;

    for (std::size_t i = 0; i < 4; ++i) {
        adder.setInput(i, (a >> i) & 1);
        adder.setInput(4 + i, (b >> i) & 1);
    }
    adder.setInput(8, false);
    adder.evaluate();

    assert(adder.getOutput(0) == 0);
    assert(adder.getOutput(1) == 0);
    assert(adder.getOutput(2) == 1);
    assert(adder.getOutput(3) == 1);
    assert(adder.getOutput(4) == 0);
}

void testSimulationAndTruthTable() {
    HalfAdder halfAdder;
    TruthTableGenerator generator;
    SimulationResult result = generator.generate(halfAdder);

    assert(result.rowCount() == 4);
    assert(result.getRows()[0].outputs[0] == 0);
    assert(result.getRows()[3].outputs[0] == 0);
    assert(result.getRows()[3].outputs[1] == 1);

    Simulator simulator;
    std::vector<std::vector<bool>> rows = {
        {false, false},
        {true, true}
    };
    SimulationResult simulated = simulator.simulate(halfAdder, rows);
    assert(simulated.rowCount() == 2);
    assert(simulated.getRows()[1].outputs[0] == 0);
    assert(simulated.getRows()[1].outputs[1] == 1);
}


void testMultithreadedSimulation() {
    HalfAdder halfAdder;
    Simulator simulator;

    std::vector<std::vector<bool>> rows;
    for (int i = 0; i < 32; ++i) {
        rows.push_back({(i & 1) != 0, (i & 2) != 0});
    }

    SimulationResult result = simulator.simulate(halfAdder, rows);
    assert(result.rowCount() == rows.size());

    const unsigned int hardwareThreads = std::thread::hardware_concurrency();
    const std::size_t expectedWorkers = std::min<std::size_t>(
        hardwareThreads == 0 ? 1 : hardwareThreads,
        rows.size()
    );
    assert(simulator.getLastWorkerCount() == expectedWorkers);

    for (std::size_t i = 0; i < rows.size(); ++i) {
        const bool a = rows[i][0];
        const bool b = rows[i][1];
        assert(result.getRows()[i].inputs == rows[i]);
        assert(result.getRows()[i].outputs[0] == (a != b));
        assert(result.getRows()[i].outputs[1] == (a && b));
    }
}

void testDecoderEncoderComparator() {
    Decoder decoder;
    const int decoderExpected[4][4] = {
        {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}
    };
    for (int a = 0; a < 2; ++a) {
        for (int b = 0; b < 2; ++b) {
            decoder.setInput(0, a);
            decoder.setInput(1, b);
            decoder.evaluate();
            const int row = a * 2 + b;
            for (int o = 0; o < 4; ++o) assert(decoder.getOutput(o) == decoderExpected[row][o]);
        }
    }

    Encoder encoder;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) encoder.setInput(j, j == i);
        encoder.evaluate();
        assert(encoder.getOutput(0) == ((i & 2) != 0));
        assert(encoder.getOutput(1) == ((i & 1) != 0));
    }

    Comparator comparator;
    for (int a = 0; a < 16; ++a) {
        for (int b = 0; b < 16; ++b) {
            for (int i = 0; i < 4; ++i) {
                comparator.setInput(i, (a >> i) & 1);
                comparator.setInput(4 + i, (b >> i) & 1);
            }
            comparator.evaluate();
            assert(comparator.getOutput(0) == (a > b));
            assert(comparator.getOutput(1) == (a == b));
            assert(comparator.getOutput(2) == (a < b));
        }
    }
}

void testCSVOutput() {
    HalfAdder halfAdder;
    TruthTableGenerator generator;
    SimulationResult result = generator.generate(halfAdder);

    const std::string path = "data/outputs/test.csv";
    std::filesystem::create_directories("data/outputs");

    CSVOutput output;
    output.write(result, path);

    std::ifstream file(path);
    assert(file.good());

    std::string header;
    std::getline(file, header);
    assert(header == "I0,I1,O0,O1");
}

int main() {
    testGates();
    testAdders();
    testRippleCarryAdder();
    testDecoderEncoderComparator();
    testSimulationAndTruthTable();
    testMultithreadedSimulation();
    testCSVOutput();

    std::cout << "All DigitalCircuitDesigner tests passed.\n";
    return 0;
}
