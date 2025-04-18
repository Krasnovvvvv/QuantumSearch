# QuantumSearch: Grover’s Algorithm in C++
![Grover Circuit](assets/grover_circuit.png)

A header-only C++ library simulating **Grover’s quantum search** algorithm. It offers an intuitive interface to perform quantum-like search on classical hardware for educational and benchmarking purposes.

---

## 📖 Algorithm Overview

**Grover’s algorithm** finds a marked item in an unstructured database of size \(N=2^n\) in \(O(\sqrt{N})\) steps, offering a quadratic speedup over classical \(O(N)\) search.

1. **Initialization**: Prepare an equal superposition of all \(N\) basis states.

   ![Superposition](assets/superposition.png)

2. **Oracle Query**: Flip the phase of the target state \(|t\rangle\):
   \[
      U_f: |x\rangle \mapsto (-1)^{f(x)}|x\rangle,
   \]
   where \(f(x)=1\) if \(x=t\), else 0.  

3. **Diffusion (Inversion about the Mean)**: Amplify the target amplitude by reflecting all amplitudes about their mean.

   ![Diffusion](assets/diffusion.png)

4. **Iteration**: Repeat Oracle + Diffusion ~\(\lfloor\frac{\pi}{4}\sqrt{N}\rfloor\) times.

5. **Measurement**: Observe the state to retrieve the target index with high probability.

---

## 🛠️ Implementation Details

The `QuantumSearch` class (in **QuantumSearch.h / QuantumSearch.cpp**) encapsulates the simulation:

- **Complex state vector**: stores \(2^n\) complex amplitudes.
- `initialize()`: sets uniform superposition.
- `applyOracle()`: flips phase of the target index.
- `applyDiffusion()`: performs inversion about the mean.
- `run()`: executes the optimal number of iterations.
- `measure()`: samples the final distribution to return an index.

```cpp
#include "QuantumSearch.h"

// Simulate 3 qubits, target index 5
auto qs = quantum::QuantumSearch(3, 5);
qs.run();
auto result = qs.measure();
```

### Template Helper `grover_search`

A function template that accepts any container (`std::vector`, `std::array`, raw arrays) of numeric types:

```cpp
int idx = quantum::grover_search(my_vector, key_value, 100);
```

- Returns index (≥0) if found, -1 if absent, -2 if probabilistic result is unreliable.

---

## ⏱️ Performance Comparison

```cpp
// Classical
auto start = now();
std::find(data.begin(), data.end(), target);
print(duration(start, now()));

// Grover Simulation
start = now();
quantum::grover_search(data, target, 50);
print(duration(start, now()));
```

| Method            | Time Complexity (Theoretical) | Simulation Cost (C++)      |
|-------------------|-------------------------------|----------------------------|
| `std::find`       | \(O(N)\)                      | \(O(N)\)                    |
| Grover’s (ideal)  | \(O(\sqrt{N})\)             | \(O(\sqrt{N} \times 2^n)\) |

> **Note:** In C++ simulation, Grover’s algorithm is slower due to the overhead of managing a \(2^n\)-sized state vector.

---

## 🌐 Quantum vs Classical Architectures

- **Classical CPU**: Executes sequential/parallel instructions on bits; memory and computation scale linearly with \(N\).
- **Quantum Processor**: Manipulates qubits allowing superposition and entanglement; state-size is physical and parallel, enabling real \(\sqrt{N}\) search.

| Feature            | Classical                        | Quantum                         |
|--------------------|----------------------------------|---------------------------------|
| Data Representation| Bits                             | Qubits                          |
| Parallelism        | SIMD / multi-core                | Intrinsic superposition         |
| Memory Cost        | \(O(N)\)                        | Physical qubits for \(n\)      |
| Query Complexity   | \(O(N)\)                       | \(O(\sqrt{N})\)                |

---

**License**: MIT © Fyodor Krasnov
