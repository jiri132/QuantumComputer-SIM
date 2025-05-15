#ifndef QUANTUMREGISTER_H
#define QUANTUMREGISTER_H

#include <complex.h>
#include <vector>
#include <complex>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>


class QuantumRegister {
private:
    size_t nqbits;
    std::vector<std::complex<double>> state;
    bool collapsed = false;
    size_t lastMeasuredState = 0;

public: 
    QuantumRegister(size_t n);
    void SetAmplitude(size_t index, std::complex<double> value);
    void Normalize();
    size_t Measure();

    size_t size() const { return state.size(); }
    const std::vector<std::complex<double>>& getState() const { return state; }
};



#endif  