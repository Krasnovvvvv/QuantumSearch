#ifndef QUANTUMSEARCH_H
#define QUANTUMSEARCH_H

#include <complex>
#include <vector>
#include <cstdint>

namespace quantum {

    class QuantumSearch
    {
    public:
        using Complex = std::complex<double>;
        using StateVector = std::vector<Complex>;

        QuantumSearch(std::size_t num_qubits, std::uint64_t target_index);

        void initialize();
        void applyOracle();
        void applyDiffusion();
        void iterate();
        void run();
        [[nodiscard]] std::uint64_t measure() const;
        [[nodiscard]] const StateVector& state() const;

    private:
        std::size_t num_qubits_;
        std::size_t dimension_;
        std::uint64_t target_index_;
        StateVector state_;

    };

    template<typename Container>
    int grover_search(const Container&data,
                      const typename Container::value_type&key,
                      int trials) {
        using T = typename Container::value_type;
        static_assert(std::is_arithmetic<T>::value,
                      "Container value_type must be arithmetic (int, double, etc.)");

        size_t n = data.size();
        if(n==0) return -1;

        size_t num_qubits = 0;
        while((size_t(1)<<num_qubits)<n) ++num_qubits;

        int idx = -1;
        size_t i = 0;
        for(auto it = std::begin(data);it!=std::end(data);++it,++i) {
            if(*it==key){idx = int(i); break;}
        }
        if(idx<0) return -1;

        int success = 0;
        for(int t = 0;t<trials;++t) {
            QuantumSearch qs(num_qubits,static_cast<uint64_t>(idx));
            qs.run();
            if(int(qs.measure())==idx) ++success;
        }
        return (success*2>=trials)?idx:-2;
    }
} //namespace quantum
#endif //QUANTUMSEARCH_H
