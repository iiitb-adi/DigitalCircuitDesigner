# Testing

Build and run the test suite with:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

The automated tests cover:

1. NAND truth table
2. NOR truth table
3. NOT truth table
4. AND truth table
5. OR truth table
6. XOR truth table
7. XNOR truth table
8. Half Adder
9. Full Adder
10. 4-bit Ripple Carry Adder
11. Generic simulation
12. Truth-table generation
13. CSV output
14. Multithreaded simulation with multiple worker threads
15. Preservation of truth-table row order after parallel simulation


## Decoder, Encoder and Comparator

The added combinational circuits are tested exhaustively:

- 2-to-4 Decoder: all 4 input combinations are checked against one-hot outputs.
- 4-to-2 Encoder: each valid one-hot input is checked against its 2-bit encoded value.
- 4-bit Comparator: all 16 × 16 = 256 pairs of input values are checked for greater-than, equality and less-than outputs.

These tests are included in `tests/test_main.cpp`.
