cmake_minimum_required(VERSION 3.28)
project(Quantum_Search)

set(CMAKE_CXX_STANDARD 17)

add_executable(Quantum_Search main.cpp
        QuantumSearch.h
        QuantumSearch.cpp)
