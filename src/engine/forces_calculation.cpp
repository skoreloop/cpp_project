#include "Visualizer.hpp"
#include <cmath>
#include <algorithm>

namespace engine {
    void calculate_forces(std::vector<Particle>& particles) {
        // Параметры для "твердых" молекул
        const double epsilon = 5.0;  // Увеличили энергию, чтобы "отскок" был сильнее
        const double sigma = 100.0;   // Эффективный диаметр молекулы (чуть больше радиуса отрисовки)
        const double cut_off = 3.0 * sigma; // Радиус обрезания сил для оптимизации
        const double cut_off2 = cut_off * cut_off;

        for (auto& p : particles) p.force = Vec2D(0, 0);

        for (size_t i = 0; i < particles.size(); ++i) {
            for (size_t j = i + 1; j < particles.size(); ++j) {
                Vec2D diff = particles[j].position - particles[i].position;
                double r2 = diff.x * diff.x + diff.y * diff.y;

                if (r2 < cut_off2) {
                    double r = std::sqrt(r2);
                    
                    // Магическая защита: если молекулы ВНУТРИ друг друга, 
                    // ставим минимальный радиус, чтобы сила была огромной, но не бесконечной
                    double safe_r = std::max(r, sigma * 0.7); 
                    
                    double s_r = sigma / safe_r;
                    double s_r6 = std::pow(s_r, 6);
                    double s_r12 = s_r6 * s_r6;

                    // Сила Леннарда-Джонса: F = 24*eps*(2*s_r12 - s_r6) / safe_r^2
                    double force_mag = 24.0 * epsilon * (2.0 * s_r12 - s_r6) / (safe_r * safe_r);

                    Vec2D f_vec = diff * force_mag;
                    particles[i].force = particles[i].force - f_vec;
                    particles[j].force = particles[j].force + f_vec;
                }
            }
        }
    }
}