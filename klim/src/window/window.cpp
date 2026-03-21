#include "window/window.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

namespace window
{
    void handleEvents(sf::RenderWindow& window)
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::KeyPressed>())
            {
                std::cout << "Key was pressed!" << std::endl;
                window.close();
            }
        }
    }

    void run()
    {
        sf::RenderWindow window(
            sf::VideoMode::getDesktopMode(),
            "Тест",
            sf::State::Fullscreen
        );

        while (window.isOpen())
        {
            handleEvents(window);

            window.clear(sf::Color(0, 0, 250));
            window.display();
        }
    }
}