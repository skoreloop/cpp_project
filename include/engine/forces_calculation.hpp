#ifndef FORCES_CALC_HPP
#define FORCES_CALC_HPP

#include "particles.hpp"
#include "Vec2D.hpp"
#include <vector>

class Force {
public:
    std::vector<std::vector<Vec2D>> force;
    std::vector<Particle> particles;
    double a_coff;
    double b_coff;

    Force(std::vector<Particle>& particles_);
    Vec2D forces_calc(Particle& first, Particle& second);
    void calculation_final();
};

#endif