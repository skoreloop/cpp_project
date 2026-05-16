#ifndef PARTICLES_HPP
#define PARTICLES_HPP

#include "engine/Vec2D.hpp"
#include <vector>

namespace engine {
    struct Particle {
        double mass;
        Vec2D position;
        Vec2D velocity;
        Vec2D force;
        float radius;

        Particle(double m, const Vec2D& pos, const Vec2D& vel, float r);
        
        void integrate_first_half(double dt);
        void integrate_second_half(double dt);
        void check_wall_collision(double width, double height);
    };

    // Обертки для вектора
    void integrate_first_half(std::vector<Particle>& particles, double dt);
    void integrate_second_half(std::vector<Particle>& particles, double dt);
    void calculate_forces(std::vector<Particle>& particles, double sigma, double epsilon);
    void check_wall_collisions(std::vector<Particle>& particles, double width, double height);
}

#endif