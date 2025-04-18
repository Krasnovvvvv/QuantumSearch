#include "QuantumSearch.h"
#include <cmath>
#include <random>
#include <numeric>

namespace quantum {

    QuantumSearch::QuantumSearch(std::size_t num_qubits, std::uint64_t target_index)
    : num_qubits_(num_qubits), dimension_(static_cast<std::size_t>(1) << num_qubits),
      target_index_(target_index), state_(dimension_){}

    void QuantumSearch::initialize() {
        double amp = 1.0/std::sqrt(static_cast<double>(dimension_));
        for(auto&a:state_) a = Complex(amp,0.0);
    }

    void QuantumSearch::applyOracle() {
        state_[target_index_]*=Complex(-1.0,0.0);
    }

    void QuantumSearch::applyDiffusion() {
        Complex mean = std::accumulate(state_.begin(),state_.end(),Complex(0.0,0.0));
        mean/=static_cast<double>(dimension_);
        for(auto&a:state_) a = Complex(2.0,0.0)*mean-a;
    }

    void QuantumSearch::iterate() {
        applyOracle();
        applyDiffusion();
    }

    void QuantumSearch::run() {
        initialize();
        std::size_t iterations = static_cast<std::size_t>(std::floor((M_PI/4.0)*std::sqrt(dimension_)));
        for(std::size_t i =0;i<iterations;++i) iterate();
    }

    std::uint64_t QuantumSearch::measure() const {
        std::vector<double> probs(dimension_);
        for(std::size_t i =0;i<dimension_;++i) probs[i]=std::norm(state_[i]);

        double sum = std::accumulate(probs.begin(),probs.end(),0.0);
        for(auto&p:probs) p/=sum;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<>dist(0.0,1.0);
        double r = dist(gen);
        double cumulative = 0.0;
        for(std::size_t i = 0;i<dimension_;++i) {
            cumulative+=probs[i];
            if(r<=cumulative){
                return static_cast<std::uint64_t>(i);
            }
        }
        return static_cast<std::uint64_t>(dimension_-1);
    }

    const QuantumSearch::StateVector& QuantumSearch::state() const {
        return state_;
    }

} //namespace quantum
