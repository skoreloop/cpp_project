#include "window.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

namespace window
{
    void handleEvents(sf::RenderWindow& window)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
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
            sf::Style::Fullscreen  // sf::State -> sf::Style
        );

        while (window.isOpen())
        {
            handleEvents(window);

            window.clear(sf::Color(0, 0, 250));
            window.display();
        }
    }
}