#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include <string>
#include "Visualizer.hpp"
#include "engine/particles.hpp"

class Simulation {
public:
    Simulation(unsigned int width, unsigned int height, const std::string& title);
    void run();

private:
    void init_particles(int count);
    void update_physics();
    
    double compute_total_energy() const;      
    void enforce_energy_conservation();       
    
    Visualizer viz;
    std::vector<engine::Particle> particles;
    
    const unsigned int window_width;
    const unsigned int window_height;
    const double sigma = 15.0;
    const double epsilon = 80.0;
    const double dt = 0.0004;
    const int physics_substeps = 15;
    
    double initial_total_energy = 0.0;
    bool energy_protection_enabled = true;
};

#endif