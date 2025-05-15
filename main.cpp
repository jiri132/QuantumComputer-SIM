#include "QuantumRegister.h"

int main() {
    QuantumRegister q(20);  // 3 qubits = 8 states

    // Set a basic superposition manually (e.g., equally 0 and 7)
    // q.SetAmplitude(0, {1.0, 0.0});
    // q.SetAmplitude(7, {1.0, 0.0});
    // q.Normalize();

    // std::cout << "Initial state vector:\n";
    // const auto& state = q.getState();
    // for (size_t i = 0; i < state.size(); ++i) {
    //     std::cout << "  |" << i << ">: " << state[i] << "\n";
    // }

    size_t result = q.Measure();
    std::cout << "Measured state: |" << result << ">\n";
    result = q.Measure();
    std::cout << "Measured state: |" << result << ">\n";

    return 0;
}
