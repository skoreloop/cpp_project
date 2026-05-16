#include "Visualizer.hpp"
#include <optional>

Visualizer::Visualizer(int width, int height, const std::string& title)
    : window(sf::VideoMode({static_cast<unsigned int>(width), static_cast<unsigned int>(height)}), title) {}

void Visualizer::handleEvents() {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        if (event->is<sf::Event::KeyPressed>()) {
            window.close();
        }
    }
}

bool Visualizer::isOpen() const {
    return window.isOpen();
}

void Visualizer::render(const std::vector<engine::Particle>& particles) {
    window.clear(sf::Color::Black);

    for (const auto& p : particles) {
        sf::CircleShape shape(p.radius);
        shape.setFillColor(sf::Color::Cyan);
        shape.setOrigin({p.radius, p.radius}); 
        shape.setPosition({static_cast<float>(p.position.x), static_cast<float>(p.position.y)});
        window.draw(shape);
    }

    window.display();
}