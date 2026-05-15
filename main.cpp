#include <iostream>
#include <vector>
#include <ctime>
#include "Visualizer.hpp"
#include "engine/particles.hpp"
#include "engine/forces_calculation.hpp"

int main() {
    std::srand(std::time(0));
    const unsigned int W = 800;
    const unsigned int H = 600;
    const double sigma = 18.0;   // Параметры Аргона
    const double epsilon = 5.0; 
    
    Visualizer viz(W, H, "VdW Gas Simulation [MIPT]");

    // Используем engine::Particle!
    std::vector<engine::Particle> gas_particles;
    for(int i = 0; i < 30; ++i) {
        Vec2D pos(rand() % (W-100) + 50, rand() % (H-100) + 50);
        Vec2D vel(rand() % 60 - 30, rand() % 60 - 30);
        gas_particles.emplace_back(1.0, pos, vel, 8.0f);
    }

    double dt = 0.001; 

    while (viz.isOpen()) {
        viz.handleEvents();
        for(int step = 0; step < 10; ++step) {
            engine::integrate_first_half(gas_particles, dt);
            // Передаем sigma и epsilon, как в хедере!
            engine::calculate_forces(gas_particles, sigma, epsilon); 
            engine::integrate_second_half(gas_particles, dt);
            engine::check_wall_collisions(gas_particles, W, H);
        }
        viz.render(gas_particles);
    }
    return 0;
}