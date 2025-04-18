# 🚀 Getting Started

Follow these steps to quickly set up and run the QuantumSearch library on your local machine.

## 📦 Prerequisites

- **C++17 compiler** (GCC ≥ 7, Clang ≥ 5, MSVC ≥ Visual Studio 2017)
- **CMake** (optional, for project generation)
- **Git** (optional, for cloning the repo)

## 🔧 Installation

1. **Clone the repository**

   ```bash
   git clone https://github.com/Krasnovvvvv/QuantumSearch.git
   cd QuantumSearch
   ```

2. **Build with CMake** (recommended)

   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

   Executable will be generated in `build/`.

3. **Or compile directly**

   ```bash
   g++ -std=c++17 src/QuantumSearch.cpp examples/main.cpp -o quantum_search
   ```

## 🧪 Usage

Include the header and call the API:

```cpp
#include "QuantumSearch.h"

int main() {
    std::vector<double> data = {0.1, 2.3, 4.5, 6.7};
    double target = 4.5;

    int index = quantum::grover_search(data, target, 100);
    if (index >= 0)
        std::cout << "Found at index " << index << std::endl;
    else
        std::cout << "Not found or unreliable result." << std::endl;

    return 0;
}
```

- **Parameters**:
  - `data` — any container of numeric types (`std::vector`, `std::array`, raw array).
  - `target` — value to search.
  - `100` — number of trials for probabilistic accuracy (default 100).

## ⏱️ Benchmark

Compare classical vs. quantum simulation:

```bash
./quantum_search
```

You should see output similar to:

```
std::find: 0.0123s
grover_search: 0.4567s
```
