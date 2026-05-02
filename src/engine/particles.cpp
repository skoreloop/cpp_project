#include <vector>
#include <iostream>
#include "engine/particles.hpp"

        

 Particle::Particle(double m = 1.0, const Vec2D& pos = Vec2D(), const Vec2D& vel = Vec2D()) : mass(m), position(pos), velocity(vel), force() {}

    void Particle::WallCollision(double boxSize_x, double boxSize_y) {
        if (position.x < 0) {
            position.x = -position.x;          
            velocity.x = -velocity.x;          
        } else if (position.x > boxSize_x) {
            position.x = 2.0 * boxSize_x - position.x;
            velocity.x = -velocity.x;
        }

        if (position.y < 0) {
            position.y = -position.y;
            velocity.y = -velocity.y;
        } else if (position.y > boxSize_y) {
            position.y = 2.0 * boxSize_y - position.y;
            velocity.y = -velocity.y;
        }
    }

    void Particle::VelocityStep(double dt, const std::vector<Particle>& particles, double boxSize_x, double boxSize_y) {
        velocity = velocity + force * (dt / mass);
        position = position + velocity * dt;

        WallCollision(boxSize_x, boxSize_y);
    }
