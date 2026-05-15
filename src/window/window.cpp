#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>

namespace window {
    void handle_events(sf::RenderWindow& window) {
        // В SFML 3 pollEvent() возвращает std::optional и не принимает аргументов
        while (const std::optional event = window.pollEvent()) {
            // Проверка закрытия окна
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            
            // Проверка нажатия клавиши (твое требование для выхода)
            if (event->is<sf::Event::KeyPressed>()) {
                window.close();
            }
        }
    }

    void run() {
        // В SFML 3 VideoMode принимает sf::Vector2u через фигурные скобки
        // sf::Style::Fullscreen заменен на sf::State::Fullscreen
        sf::RenderWindow window(sf::VideoMode({800, 600}), "MIPT VdW Simulation", sf::State::Fullscreen);

        while (window.isOpen()) {
            handle_events(window);

            window.clear(sf::Color::Black);
            // Здесь будет твоя логика отрисовки
            window.display();
        }
    }
}