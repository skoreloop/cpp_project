#include "engine/particles.hpp"
#include <vector>

namespace engine {
    Particle::Particle(double m, const Vec2D& pos, const Vec2D& vel, float r)
        : mass(m), position(pos), velocity(vel), force(0.0, 0.0), radius(r) {}

    void Particle::integrate_first_half(double dt) {
       
        velocity = velocity + force * (0.5 * dt / mass);
        
        position = position + velocity * dt;
    }

    void Particle::integrate_second_half(double dt) {
        
        velocity = velocity + force * (0.5 * dt / mass);
    }

    void Particle::check_wall_collision(double width, double height) {
        
        if (position.x - radius < 0) {
            position.x = radius;         
            velocity.x = -velocity.x;    
        } else if (position.x + radius > width) {
            position.x = width - radius;
            velocity.x = -velocity.x;
        }
        if (position.y - radius < 0) {
            position.y = radius;
            velocity.y = -velocity.y;
        } else if (position.y + radius > height) {
            position.y = height - radius;
            velocity.y = -velocity.y;
        }
    }

    void integrate_first_half(std::vector<Particle>& particles, double dt) {
        for (auto& p : particles) {
            p.integrate_first_half(dt);
        }
    }

    void integrate_second_half(std::vector<Particle>& particles, double dt) {
        for (auto& p : particles) {
            p.integrate_second_half(dt);
        }
    }

    void check_wall_collisions(std::vector<Particle>& particles, double width, double height) {
        for (auto& p : particles) {
            p.check_wall_collision(width, height);
        }
    }

} 