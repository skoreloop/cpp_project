#include "Simulation.hpp"
#include "engine/forces_calculation.hpp"
#include <ctime>
#include <cmath>
#include <algorithm>

Simulation::Simulation(unsigned int width, unsigned int height, const std::string& title)
    : viz(static_cast<int>(width), static_cast<int>(height), title), 
      window_width(width), window_height(height) {
    std::srand(std::time(0));
    init_particles(30);
    initial_total_energy = compute_total_energy();
}

void Simulation::init_particles(int count) {
    for(int i = 0; i < count; ++i) {
        Vec2D pos(std::rand() % (window_width - 100) + 50, 
                  std::rand() % (window_height - 100) + 50);
        Vec2D vel(std::rand() % 100 - 50, 
                  std::rand() % 100 - 50);
        particles.emplace_back(1.0, pos, vel, 6.0f);
    }
}

double Simulation::compute_total_energy() const {
    double kinetic = 0.0;
    for (const auto& p : particles) {
        kinetic += 0.5 * p.mass * (p.velocity.x * p.velocity.x + p.velocity.y * p.velocity.y);
    }
    
    double potential = 0.0;
    double s2 = sigma * sigma;
    
    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            double dx = particles[i].position.x - particles[j].position.x;
            double dy = particles[i].position.y - particles[j].position.y;
            double r2 = dx*dx + dy*dy;

            double safe_r2 = std::max(r2, (0.6 * sigma) * (0.6 * sigma));
            
            double s2_r2 = s2 / safe_r2;        // (sigma/r)^2
            double s6_r6 = s2_r2 * s2_r2 * s2_r2; // (sigma/r)^6
            double s12_r12 = s6_r6 * s6_r6;       // (sigma/r)^12
            
            potential += 4.0 * epsilon * (s12_r12 - s6_r6);
        }
    }
    return kinetic + potential;
}

void Simulation::enforce_energy_conservation() {
    double kinetic = 0.0;
    for (const auto& p : particles) {
        kinetic += 0.5 * p.mass * (p.velocity.x * p.velocity.x + p.velocity.y * p.velocity.y);
    }

    double current_total = compute_total_energy();
    double potential = current_total - kinetic;

    double target_kinetic = initial_total_energy - potential;

    if (target_kinetic > 0 && kinetic > 0) {
        double scale = sqrt(target_kinetic / kinetic);
        scale = std::clamp(scale, 0.9, 1.1); 

        for (auto& p : particles) {
            p.velocity.x *= scale;
            p.velocity.y *= scale;
        }
    }
}

void Simulation::update_physics() {
    for(int step = 0; step < physics_substeps; ++step) {
        engine::integrate_first_half(particles, dt);
        engine::calculate_forces(particles, sigma, epsilon); 
        engine::integrate_second_half(particles, dt);
        engine::check_wall_collisions(particles, static_cast<double>(window_width), static_cast<double>(window_height));
    }
    
    if (energy_protection_enabled) {
        enforce_energy_conservation();
    }
}

void Simulation::run() {
    while (viz.isOpen()) {
        viz.handleEvents();
        update_physics();
        viz.render(particles);
    }
}