# Digital Circuit Designer

A C++17 digital logic circuit simulator built using object-oriented design.

## Scope

The project focuses on the core requirements of the digital electronics circuit designer:

- NAND and NOR as primitive gates
- NOT, AND, OR, XOR and XNOR built using gate composition
- Explicit connections between circuit elements
- Reusable `Circuit` abstraction
- Half Adder, Full Adder and configurable Ripple Carry Adder
- Circuit simulation
- `SimulationResult` abstraction
- Console and CSV output
- Automatic truth-table generation
- Multithreaded simulation using `std::thread`
- 2-to-4 Decoder
- 4-to-2 Encoder
- 4-bit Comparator
- Automated tests

## Build

```bash
cmake -S . -B build
cmake --build build
```

Run the application:

```bash
./build/digital_circuit_designer
```

Run tests:

```bash
ctest --test-dir build --output-on-failure
```

## Project structure

```text
DigitalCircuitDesigner/
├── include/
│   ├── core/          # CircuitElement, Gate, Connection, Circuit
│   ├── gates/         # NAND, NOR and derived gates
│   ├── circuits/      # Adders, decoder, encoder and comparator
│   ├── simulation/    # Simulator and SimulationResult
│   ├── output/        # Console and CSV output
│   └── analysis/      # Truth-table generation
├── src/               # Implementations
├── tests/              # Automated tests
├── data/outputs/       # Generated CSV files
├── PROJECT_REPORT.md   # Project documentation
├── TESTING.md          # Testing documentation
├── class_diagram.puml  # UML source
├── main.cpp            # Command-line demonstration
└── CMakeLists.txt      # Build configuration
```

## Multithreaded simulation

The simulator evaluates independent input rows in parallel using `std::thread`. Because evaluating a circuit changes its input/output state, each worker receives its own cloned circuit instance. An atomic work index distributes input rows among workers, while results are stored using their original row indices so truth-table order is preserved.

The project links C++ threading support through CMake's `Threads::Threads` target.

## Design idea

`CircuitElement` is the common abstraction for gates and complete circuits. A `Circuit` owns smaller circuit elements and connects them using `Connection` objects. This allows a circuit to be built from smaller circuits, for example:

```text
NAND/NOR
   ↓
Derived gates
   ↓
Half Adder
   ↓
Full Adder
   ↓
Ripple Carry Adder
```

The simulator operates on any `CircuitElement` and produces a `SimulationResult`. This allows gates, adders, decoder, encoder and comparator to use the same simulation infrastructure. Output classes consume that result, so simulation is independent of presentation or file format.


## Team Contributions

### Vaishvik — Part 1: Core Architecture and Gate Implementation
- `CircuitElement` and `Gate` abstraction
- `Connection` and signal propagation
- NAND and NOR primitive gates
- NOT, AND, OR, XOR and XNOR gate construction
- Core gate-level architecture and inheritance/composition design

### Aditya — Part 2: Circuit Construction
- Half Adder
- Full Adder
- 4-bit Ripple Carry Adder
- 2-to-4 Decoder
- 4-to-2 Encoder
- 4-bit Comparator
- Composition of digital circuit elements and circuit-level logic

### Suhas — Simulation, Testing and Output
- `Simulator` and `SimulationResult`
- Truth-table generation and simulation workflow
- Automated testing
- Console output and CSV export
- Multithreaded simulation integration and validation
