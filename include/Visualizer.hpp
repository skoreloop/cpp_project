#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <optional>
#include "engine/particles.hpp"

class Visualizer {
private:
    sf::RenderWindow window;
public:

    Visualizer(int width, int height, const std::string& title);
    
    void handleEvents();
    bool isOpen() const;
    void render(const std::vector<engine::Particle>& particles);
};

#endif 