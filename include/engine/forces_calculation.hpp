#ifndef FORCES_CALCULATION_HPP
#define FORCES_CALCULATION_HPP

#include <vector>
#include "Visualizer.hpp"

namespace engine {
    // Теперь сигнатура совпадает с вызовом в main.cpp
    void calculate_forces(std::vector<Particle>& particles, double sigma, double epsilon);
}

#endif