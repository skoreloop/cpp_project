#include <iostream>
#include <ctime>
#include "Visualizer.hpp"

namespace engine {
    void integrate_first_half(std::vector<Particle>& particles, double dt);
    void calculate_forces(std::vector<Particle>& particles);
    void integrate_second_half(std::vector<Particle>& particles, double dt);
    void check_wall_collisions(std::vector<Particle>& particles, double width, double height);
}

int main() {
    std::srand(std::time(0));
    const unsigned int W = 800;
    const unsigned int H = 600;
    Visualizer viz(W, H, "VdW Gas & MD Simulation [MIPT]");

    std::vector<Particle> gas_particles;
    int num_particles = 30; // Не делай слишком много, чтобы всё не "взорвалось"
    
    for(int i = 0; i < num_particles; ++i) {
        Vec2D pos((double)(rand() % (W - 100) + 50), (double)(rand() % (H - 100) + 50));
        Vec2D vel((double)(rand() % 80 - 40), (double)(rand() % 80 - 40));
        gas_particles.emplace_back(1.0, pos, vel, 8.0f); // Радиус 8, sigma 18 — они будут отталкиваться раньше, чем коснутся визуально
    }

    // ВАЖНО: уменьшаем dt для точности столкновений
    double dt = 0.005; 

    while (viz.isOpen()) {
        viz.handleEvents();

        // Чтобы симуляция не замедлилась из-за маленького dt, 
        // прогоняем несколько физ. шагов за один кадр отрисовки
        for(int step = 0; step < 5; ++step) {
            engine::integrate_first_half(gas_particles, dt);
            engine::calculate_forces(gas_particles);
            engine::integrate_second_half(gas_particles, dt);
            engine::check_wall_collisions(gas_particles, W, H);
        }

        viz.render(gas_particles);
    }

    return 0;
}