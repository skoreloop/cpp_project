#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "Vec2D.hpp"
#include <vector>

class Particle {
public:
    double mass;
    Vec2D position;
    Vec2D velocity;
    Vec2D force;

    Particle(double m, const Vec2D& pos, const Vec2D& vel);
    void WallCollision(double boxSize_x, double boxSize_y);
    void VelocityStep(double dt, const std::vector<Particle>& particles, double boxSize_x, double boxSize_y);
};

#endif