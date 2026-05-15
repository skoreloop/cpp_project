#include "Visualizer.hpp"

// Сигнатура должна СОВПАДАТЬ с .hpp
void Visualizer::render(const std::vector<engine::Particle>& particles) {
    window.clear();
    for (const auto& p : particles) {
        sf::CircleShape shape(p.radius);
        shape.setOrigin({p.radius, p.radius}); // Центрируем шарик
        shape.setPosition({(float)p.position.x, (float)p.position.y});
        window.draw(shape);
    }
    window.display();
}