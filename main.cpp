#include <iostream>

#include <SFML/Graphics.hpp>

#include "RayCasting.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 768), "Raycasting");
    window.setFramerateLimit(60);
    sf::Font font;
    if (const std::string path = "assets/fonts/tech.ttf"; !font.loadFromFile(path))
    {
        std::cerr << "Could not load from file: " << path << "\n";
        std::exit(-1);
    }
    sf::Text text("R: Change\nEsc: Quit", font, 20);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(50, 30));

    // - pointer cursor
    sf::CircleShape point(5.0f);
    point.setFillColor(sf::Color::Red);
    point.setOrigin(5, 5);
    bool raycast = false;

    while (window.isOpen())
    {
        // Handle user input
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { window.close(); }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape) { window.close(); }
                if (event.key.code == sf::Keyboard::R) { raycast = !raycast; }
            }
        }
        // Clear window
        window.clear(sf::Color(50, 50, 150));

        auto mousePos = sf::Mouse::getPosition(window);
        point.setPosition(mousePos.x, mousePos.y);

        // Draw raycasting
        if (raycast)
            castRaysFromCenter1(point, window);
        else
            castRaysFromCenter3(point, window);

        window.draw(text);

        window.display();
    }
    return 0;
}
