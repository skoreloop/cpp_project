#include "Visualizer.hpp"

Visualizer::Visualizer(unsigned int width, unsigned int height, const std::string& title) 
    : window(sf::VideoMode({width, height}), title) {
    window.setFramerateLimit(60);
}

bool Visualizer::isOpen() const {
    return window.isOpen();
}

void Visualizer::handleEvents() {
    // Новый синтаксис SFML 3 [cite: 164, 216, 231]
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>() || event->is<sf::Event::KeyPressed>()) {
            window.close();
        }
    }
}

void Visualizer::render(const std::vector<Particle>& particles) {
    window.clear(sf::Color(15, 15, 20));

    for (const auto& p : particles) {
        sf::CircleShape shape(p.radius);
        shape.setOrigin({p.radius, p.radius}); // Центрируем шарик
        shape.setPosition({(float)p.position.x, (float)p.position.y});
        shape.setFillColor(sf::Color::Cyan);
        window.draw(shape);
    }

    window.display();
}