# Digital Circuit Designer - Project Report Notes

## 1. Objective

The project implements a digital electronics circuit designer and simulator in C++. The design uses object-oriented programming so that primitive gates, derived gates and larger circuits can be reused as components.

## 2. Main classes

### CircuitElement
Abstract base class for anything that has inputs, outputs and an `evaluate()` operation.

### Gate
Common implementation for single-output logic gates. It stores input and output signals while derived classes implement their logic.

### NANDGate and NORGate
Primitive gates. They provide the basic logic from which the other gates are composed.

### Derived gates
`NOTGate`, `ANDGate`, `ORGate`, `XORGate` and `XNORGate` are implemented by composing primitive gate objects and connections rather than replacing the circuit structure with one direct boolean expression.

### Connection
Represents a directed connection from one element's output to another element's input.

### Circuit
A reusable composite `CircuitElement`. It owns its internal elements and connections and exposes its own inputs and outputs.

### Combinational circuits
- `Decoder` is a 2-to-4 decoder with two inputs and four one-hot outputs.
- `Encoder` is a 4-to-2 one-hot encoder.
- `Comparator` is a 4-bit magnitude comparator with `A > B`, `A = B`, and `A < B` outputs.

### Adders
- `HalfAdder` uses XOR and AND.
- `FullAdder` uses two Half Adders and an OR gate.
- `RippleCarryAdder` connects multiple Full Adders so carry propagates from one bit to the next.

### SimulationResult
Stores input/output names and the rows generated during simulation. It is separate from output/display code.

### Simulator
Applies input rows to a circuit, evaluates it and records the outputs in a `SimulationResult`. Independent input rows are processed concurrently using `std::thread`. Each worker receives a cloned circuit instance because circuit evaluation mutates inputs and internal gate state. Results are written back by input-row index so the final output remains in deterministic truth-table order.

### Output classes
`ConsoleOutput` displays results on the terminal and `CSVOutput` writes them to a CSV file.

### TruthTableGenerator
Generates all binary input combinations for a circuit and uses the simulator to obtain the corresponding outputs.

## 3. OOP concepts demonstrated

- **Abstraction:** `CircuitElement` and `Output` define common interfaces.
- **Inheritance:** Gates derive from `Gate`; complete circuits derive from `Circuit`.
- **Composition:** Derived gates and adders are constructed from smaller circuit elements.
- **Encapsulation:** Internal gate state and circuit connections are hidden behind public interfaces.
- **Polymorphism:** `CircuitElement` pointers can refer to gates or complete circuits.

## 4. Simulation flow

```text
Input combinations
       ↓
TruthTableGenerator
       ↓
Simulator
       ↓
Circuit::evaluate()
       ↓
SimulationResult
       ↓
ConsoleOutput / CSVOutput
```

## 5. Testing

The test program checks all supported gates, Half Adder, Full Adder, 4-bit Ripple Carry Adder, Decoder, Encoder, 4-bit Comparator, truth-table generation, direct simulation, multithreaded simulation and CSV output.

## 6. Multithreading design

Truth-table rows are independent simulations, so they can be evaluated concurrently. The simulator creates a worker pool based on `std::thread::hardware_concurrency()` and gives each worker its own cloned `Circuit`. A shared atomic index distributes work without assigning the same row twice. Each row is stored at its original index, preserving deterministic output order.

The build uses CMake's `Threads::Threads` target to link the required threading support.

## 7. Possible future extensions

Possible future extensions include user-defined truth-table elements, multiplexers, registers and a graphical interface.
