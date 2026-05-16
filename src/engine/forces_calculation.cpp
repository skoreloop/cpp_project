#include "engine/forces_calculation.hpp"
#include <cmath>
#include <algorithm>

namespace engine {

void calculate_forces(std::vector<Particle>& particles, double sigma, double epsilon) {
    
    const double cut_off = 3.0 * sigma;
    const double cut_off2 = cut_off * cut_off;

    for (auto& p : particles) {
        p.force = Vec2D(0, 0);
    }

    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            Vec2D diff = particles[j].position - particles[i].position;
            double r2 = diff.x * diff.x + diff.y * diff.y;

            if (r2 < cut_off2) {
                
                double min_r = 0.5 * sigma; 
                double min_r2 = min_r * min_r;
                double safe_r2 = std::max(r2, min_r2);
                
                double s2_r2 = (sigma * sigma) / safe_r2; // (sigma/r)^2
                double s6_r6 = s2_r2 * s2_r2 * s2_r2;     // (sigma/r)^6
                double s12_r12 = s6_r6 * s6_r6;           // (sigma/r)^12

                double force_mag = 24.0 * epsilon * (2.0 * s12_r12 - s6_r6) / safe_r2;

                Vec2D f_vec = diff * force_mag;

                particles[i].force = particles[i].force - f_vec;
                particles[j].force = particles[j].force + f_vec;
            }
        }
    }
}

} 