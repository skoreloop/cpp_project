#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include "engine/particles.hpp" // Подключаем общие частицы

class Visualizer {
public:
    Visualizer(int w, int h, const std::string& title);
    bool isOpen() const;
    void handleEvents();
    // ВАЖНО: используем engine::Particle
    void render(const std::vector<engine::Particle>& particles);

private:
    sf::RenderWindow window;
};

#endif