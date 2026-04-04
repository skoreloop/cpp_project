#include <vector>
#include <iostream>
using namespace std;



class Force{
public:
    vector<vector<Vec2D>> force;
    vector<Particle> particles;
    double a_coff;  
    double b_coff;
    
    Force(vector<Particle>& particles_): particles(particles_) {
        force.resize(particles.size(), vector<Vec2D>(particles.size()));
        a_coff = 1.0;
        b_coff = 1.0;
    }
    
    Vec2D forces_calc(Particle& first, Particle& second){
        double dx = first.position[0] - second.position[0];
        double dy = first.position[1] - second.position[1];
        double r = sqrt(dx*dx + dy*dy);
        double r8 = pow(r, 8);
        double r14 = r8 * pow(r, 6);
        
        double force_amplitude = 12.0 * a_coff / r14 - 6.0 * b_coff / r8;
        
        return Vec2D(dx * force_amplitude, dy * force_amplitude);
    }
    
    void calculation_final(){
        int n = particles.size();
        for(int i = 0; i < n; i++) {  
            for(int j = i + 1; j < n; j++) {  
                Vec2D f = forces_calc(particles[i], particles[j]);
                force[i][j] = f;
                force[j][i] = Vec2D(-f[0], -f[1]);
            }
        }
    }
};