#include "circuits/Comparator.h"
#include "gates/ANDGate.h"
#include "gates/NOTGate.h"
#include "gates/ORGate.h"
#include "gates/XNORGate.h"

Comparator::Comparator()
    : CircuitElement("4-bit Comparator"),
      circuit("4-bit Comparator Internal", 8, 3) {

    // Inputs 0..3 = A0..A3
    // Inputs 4..7 = B0..B3
    //
    // Outputs:
    // 0 = A > B
    // 1 = A = B
    // 2 = A < B

    XNORGate* eq[4];
    NOTGate* notA[4];
    NOTGate* notB[4];

    for (int i = 0; i < 4; ++i) {

        eq[i] = &circuit.addElement<XNORGate>();
        notA[i] = &circuit.addElement<NOTGate>();
        notB[i] = &circuit.addElement<NOTGate>();

        circuit.connectInput(i, *eq[i], 0);
        circuit.connectInput(4 + i, *eq[i], 1);

        circuit.connectInput(i, *notA[i], 0);
        circuit.connectInput(4 + i, *notB[i], 0);
    }

    // Equality:
    // A = B when all four bits are equal.

    auto& eq32 = circuit.addElement<ANDGate>();
    circuit.connect(*eq[3], 0, eq32, 0);
    circuit.connect(*eq[2], 0, eq32, 1);

    auto& eq321 = circuit.addElement<ANDGate>();
    circuit.connect(eq32, 0, eq321, 0);
    circuit.connect(*eq[1], 0, eq321, 1);

    auto& equal = circuit.addElement<ANDGate>();
    circuit.connect(eq321, 0, equal, 0);
    circuit.connect(*eq[0], 0, equal, 1);

    // A > B

    auto& gt3 = circuit.addElement<ANDGate>();
    circuit.connectInput(3, gt3, 0);
    circuit.connect(*notB[3], 0, gt3, 1);

    auto& gt2a = circuit.addElement<ANDGate>();
    circuit.connect(*eq[3], 0, gt2a, 0);
    circuit.connectInput(2, gt2a, 1);

    auto& gt2 = circuit.addElement<ANDGate>();
    circuit.connect(gt2a, 0, gt2, 0);
    circuit.connect(*notB[2], 0, gt2, 1);

    auto& gt1b = circuit.addElement<ANDGate>();
    circuit.connect(eq32, 0, gt1b, 0);
    circuit.connectInput(1, gt1b, 1);

    auto& gt1 = circuit.addElement<ANDGate>();
    circuit.connect(gt1b, 0, gt1, 0);
    circuit.connect(*notB[1], 0, gt1, 1);

    auto& gt0b = circuit.addElement<ANDGate>();
    circuit.connect(eq321, 0, gt0b, 0);
    circuit.connectInput(0, gt0b, 1);

    auto& gt0 = circuit.addElement<ANDGate>();
    circuit.connect(gt0b, 0, gt0, 0);
    circuit.connect(*notB[0], 0, gt0, 1);

    auto& gtLeft = circuit.addElement<ORGate>();
    circuit.connect(gt3, 0, gtLeft, 0);
    circuit.connect(gt2, 0, gtLeft, 1);

    auto& gtRight = circuit.addElement<ORGate>();
    circuit.connect(gt1, 0, gtRight, 0);
    circuit.connect(gt0, 0, gtRight, 1);

    auto& greater = circuit.addElement<ORGate>();
    circuit.connect(gtLeft, 0, greater, 0);
    circuit.connect(gtRight, 0, greater, 1);

    // A < B

    auto& lt3 = circuit.addElement<ANDGate>();
    circuit.connect(*notA[3], 0, lt3, 0);
    circuit.connectInput(7, lt3, 1);

    auto& lt2a = circuit.addElement<ANDGate>();
    circuit.connect(*eq[3], 0, lt2a, 0);
    circuit.connect(*notA[2], 0, lt2a, 1);

    auto& lt2 = circuit.addElement<ANDGate>();
    circuit.connect(lt2a, 0, lt2, 0);
    circuit.connectInput(6, lt2, 1);

    auto& lt1b = circuit.addElement<ANDGate>();
    circuit.connect(eq32, 0, lt1b, 0);
    circuit.connect(*notA[1], 0, lt1b, 1);

    auto& lt1 = circuit.addElement<ANDGate>();
    circuit.connect(lt1b, 0, lt1, 0);
    circuit.connectInput(5, lt1, 1);

    auto& lt0b = circuit.addElement<ANDGate>();
    circuit.connect(eq321, 0, lt0b, 0);
    circuit.connect(*notA[0], 0, lt0b, 1);

    auto& lt0 = circuit.addElement<ANDGate>();
    circuit.connect(lt0b, 0, lt0, 0);
    circuit.connectInput(4, lt0, 1);

    auto& ltLeft = circuit.addElement<ORGate>();
    circuit.connect(lt3, 0, ltLeft, 0);
    circuit.connect(lt2, 0, ltLeft, 1);

    auto& ltRight = circuit.addElement<ORGate>();
    circuit.connect(lt1, 0, ltRight, 0);
    circuit.connect(lt0, 0, ltRight, 1);

    auto& less = circuit.addElement<ORGate>();
    circuit.connect(ltLeft, 0, less, 0);
    circuit.connect(ltRight, 0, less, 1);

    circuit.connectOutput(greater, 0, 0);
    circuit.connectOutput(equal, 0, 1);
    circuit.connectOutput(less, 0, 2);

    circuit.setLogicDepth(20);
}

void Comparator::evaluate() {
    circuit.evaluate();
}

int Comparator::getInputCount() const {
    return circuit.getInputCount();
}

int Comparator::getOutputCount() const {
    return circuit.getOutputCount();
}

void Comparator::setInput(std::size_t index, bool value) {
    circuit.setInput(index, value);
}

bool Comparator::getOutput(std::size_t index) const {
    return circuit.getOutput(index);
}

std::unique_ptr<CircuitElement> Comparator::clone() const {
    return std::make_unique<Comparator>();
}
