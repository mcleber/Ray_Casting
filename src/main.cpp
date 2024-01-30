/**
 * @file    main.cpp
 *
 * @brief   Create a basic raycaster renderer in C++ using the SFML library.
 *          Based on the Raycaster from "The Hello World Guy" YouTube channel.
 *
 * @author
 * @date    2023/12/28
 * @version 1.0
 *
 * Licensed under MIT License
 *
*/

#include <SFML/Graphics.hpp>

#include "../include/map.hpp"
#include "../include/player.hpp"
#include "../include/renderer.hpp"


int main()
{
    /// Initial window settings
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Ray Casting - 1.0",
        sf::Style::Titlebar | sf::Style::Close);

    /// Adjust window position when running
    window.setPosition(sf::Vector2i(0, 0));

    /// Speed control (in fps)
    window.setFramerateLimit(60);

    /// Creates the Map object and loads texture
    Map map(48.f, "./image/map.png");

    /// Creates the Player object
    Player player;
    player.position = sf::Vector2f(50, 50);

    Renderer renderer;
    renderer.init();

    sf::Clock gameGlock;

    // LOOP WHILE
    while (window.isOpen())
    {
        float deltaTime = gameGlock.restart().asSeconds();

        sf:: Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }


        player.update(deltaTime);

        window.clear();

        renderer.draw3DView(window, player, map);

        window.display();

    } // FIM LOOP WHILE

    return 0;
}
