#include "engine/forces_calculation.hpp"
#include <cmath>
#include <algorithm>

namespace engine {

void calculate_forces(std::vector<Particle>& particles, double sigma, double epsilon) {
    // 1. Параметры обрезания (Cut-off) для оптимизации O(N^2)
    const double cut_off = 3.0 * sigma;
    const double cut_off2 = cut_off * cut_off;

    // 2. Сброс сил перед новым расчетом (критично для стабильности!)
    for (auto& p : particles) {
        p.force = Vec2D(0, 0);
    }

    // 3. Двойной цикл по парам частиц
    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            Vec2D diff = particles[j].position - particles[i].position;
            double r2 = diff.x * diff.x + diff.y * diff.y;

            // Считаем силы только в пределах радиуса обрезания
            if (r2 < cut_off2) {
                // Защита от "взрыва": ограничиваем минимальное расстояние r^2
                // (соответствует непроницаемому ядру молекулы 0.7*sigma)
                double min_r2 = (sigma) * (sigma);
                double safe_r2 = std::max(r2, min_r2);
                
                // Оптимизированный расчет Леннарда-Джонса через квадраты
                double s2_r2 = (sigma * sigma) / safe_r2; // (sigma/r)^2
                double s6_r6 = s2_r2 * s2_r2 * s2_r2;     // (sigma/r)^6
                double s12_r12 = s6_r6 * s6_r6;           // (sigma/r)^12

                // Сила (векторная форма): F_mag = 24*eps*(2*s_r12 - s_r6) / r^2
                // Делим на safe_r2, так как один r идет из производной потенциала, 
                // а второй — из нормировки вектора направления diff.
                double force_mag = 24.0 * epsilon * (2.0 * s12_r12 - s6_r6) / safe_r2;

                Vec2D f_vec = diff * force_mag;

                // Третий закон Ньютона в действии
                particles[i].force = particles[i].force - f_vec;
                particles[j].force = particles[j].force + f_vec;
            }
        }
    }
}

} // namespace engine