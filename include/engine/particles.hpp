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

    Particle(double m = 1.0, const Vec2D& pos = Vec2D(), const Vec2D& vel = Vec2D());
    void WallCollision(double boxSize_x, double boxSize_y);
    void VelocityStep(double dt, const std::vector<Particle>& particles, double boxSize_x, double boxSize_y);
};

#endif