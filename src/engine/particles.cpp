#include "Visualizer.hpp"

namespace engine {
    // Первый этап Верле: обновление координат и полшага по скорости [cite: 317, 318]
    void integrate_first_half(std::vector<Particle>& particles, double dt) {
        for (auto& p : particles) {
            p.velocity = p.velocity + p.force * (0.5 * dt / p.mass);
            p.position = p.position + p.velocity * dt;
        }
    }

    // Второй этап Верле: финальное обновление скорости [cite: 317, 318]
    void integrate_second_half(std::vector<Particle>& particles, double dt) {
        for (auto& p : particles) {
            p.velocity = p.velocity + p.force * (0.5 * dt / p.mass);
        }
    }

    // Обработка столкновений со стенками [cite: 278, 285]
    void check_wall_collisions(std::vector<Particle>& particles, double width, double height) {
        for (auto& p : particles) {
            if (p.position.x - p.radius < 0) {
                p.position.x = p.radius; p.velocity.x *= -1;
            } else if (p.position.x + p.radius > width) {
                p.position.x = width - p.radius; p.velocity.x *= -1;
            }
            if (p.position.y - p.radius < 0) {
                p.position.y = p.radius; p.velocity.y *= -1;
            } else if (p.position.y + p.radius > height) {
                p.position.y = height - p.radius; p.velocity.y *= -1;
            }
        }
    }
}