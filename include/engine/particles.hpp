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

        Particle(double m, const Vec2D& pos, const Vec2D& vel, float r = 8.0f);

        // Методы для ОДНОЙ частицы (имена как в main)
        void check_wall_collision(double width, double height);
        void integrate_first_half(double dt);
        void integrate_second_half(double dt);
    };

    // Глобальные функции для ВЕКТОРА (то, что вызывается в main.cpp)
    void integrate_first_half(std::vector<Particle>& particles, double dt);
    void integrate_second_half(std::vector<Particle>& particles, double dt);
    void check_wall_collisions(std::vector<Particle>& particles, double width, double height);
}

#endif