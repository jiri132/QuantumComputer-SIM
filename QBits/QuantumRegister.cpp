#include "QuantumRegister.h"
#include <random>
#include <numeric>


QuantumRegister::QuantumRegister(size_t n) : nqbits(n), state(1ULL << n, std::complex<double>(0.0, 0.0)) {
    size_t dim = 1ULL << n;  // 2^n
    state.resize(dim, {0.0, 0.0});
    for (size_t i = 0; i < state.size(); ++i) {
        SetAmplitude(i, {1.0, 0.0});
    }
    Normalize();
}

void QuantumRegister::SetAmplitude(size_t index, std::complex<double> value) {
    if (index >= state.size()) {
        throw std::out_of_range("Index is out of range in SetAmplitude()");
    }
    state[index] = value;
    collapsed = false;
}

void QuantumRegister::Normalize() {
    double norm = std::sqrt(
        std::accumulate(state.begin(), state.end(), 0.0,
            [](double sum, const std::complex<double>& c) {
                return sum + std::norm(c);
            })
    );

    if (norm == 0.0) {
        throw std::runtime_error("Cannot normalize a zero vector");
    }

    for (auto& amplitude : state) {
        amplitude /= norm;
    }
}

size_t QuantumRegister::Measure() {
    if (collapsed) return lastMeasuredState;

    // Compute probability distribution
    std::vector<double> probabilities(state.size());
    for (size_t i = 0; i < state.size(); ++i) {
        probabilities[i] = std::norm(state[i]);
    }

    // Use random number generation to simulate measurement
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<size_t> dist(probabilities.begin(), probabilities.end());

    size_t result = dist(gen);
    lastMeasuredState = result;
    collapsed = true;

    // Collapse state to the measured basis state
    for (size_t i = 0; i < state.size(); ++i) {
        state[i] = (i == result) ? std::complex<double>{1.0, 0.0} : std::complex<double>{0.0, 0.0};
    }

    return result;
}

