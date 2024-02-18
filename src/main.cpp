/**
 * @file    main.cpp
 *
 * @brief   Create a basic raycaster renderer in C++ using the SFML library.
 *          Raycaster tutorial from YouTube channel "The Hello World Guy".
 *
 * @author
 * @date    2023/12/28
 * @version 1.0
 *
 * Licensed under MIT License
*/

#include <SFML/Graphics.hpp>

#include "../include/map.hpp"
#include "../include/player.hpp"
#include "../include/renderer.hpp"


int main()
{
    // Initial window settings
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Ray Casting - 1.0",
                            sf::Style::Titlebar | sf::Style::Close);

    //window.setVerticalSyncEnabled(true); // limits the frame rate to 60 fps.

    // Adjust window position when running
    window.setPosition(sf::Vector2i(0, 0));

    // Speed control (in fps)
    window.setFramerateLimit(60);

    // Creates the Map object and loads texture
    Map map(48.f, "./image/map.png");

    // Creates the Player object
    Player player;
    player.position = sf::Vector2f(50, 50);

    Renderer renderer;
    renderer.init();

    // Game Editor
    enum class State { Editor, Game} state = State::Game;

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
            // Press ESC to exit the Raycaster and enter the Editor, and ESC again to return.
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                state = state == State::Game ? State::Editor : State::Game;
            }
        }

        window.clear();
        if (state == State::Game)
        {
            player.update(deltaTime);
            renderer.draw3DView(window, player, map);
        }
        else
        {
            // Draw 2D map
            map.draw(window);
        }

        window.display();

        // Frame rate (this line overwrites the Title in the Initial window settings)
        window.setTitle("Raycaster - v.1.0 | FrameRate: " + std::to_string(1.0f / deltaTime));

    } // END LOOP WHILE

    return 0;
}
