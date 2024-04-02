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

#include <iostream>

#include <SFML/Graphics.hpp>

#include "../include/editor.hpp"

#include "../include/imgui-SFML.h"

#include "../include/map.hpp"
#include "../include/player.hpp"
#include "../include/renderer.hpp"
#include "../include/resources.hpp"


int main(int argc, const char **argv)
{
    // Initial window settings
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Ray Casting - 1.0",
                            sf::Style::Titlebar | sf::Style::Close);

    window.setVerticalSyncEnabled(true); // limits the frame rate to 60 fps

    // Adjust window position when running
    window.setPosition(sf::Vector2i(0, 0));

    // Speed control (in fps)
    //window.setFramerateLimit(60);

    // Check ImGUI- SFML
    if (!ImGui::SFML::Init(window))
    {
        std::cerr << "Failed to init ImGui" << std::endl;
        return 1;
    }

    // Load Wall Textures
    if (!Resources::texturesImage.loadFromFile("./image/textures.png"))
    {
        std::cerr << "Failed to load textures.png" << std::endl;
    }
    Resources::textures.loadFromImage(Resources::texturesImage);

    // Creates the Player object
    Player player;
    player.position = sf::Vector2f(50, 50);

    Renderer renderer;
    renderer.init();

    // Map Editor
    Editor editor{};
    editor.init(window);

    // Creates the Map object and load edited map
    Map map {48.0f};
    if (argc > 1)
    {
        editor.savedFileName = argv[1];
        map.load(editor.savedFileName);
    }

    // Game Editor
    enum class State { Editor, Game} state = State::Game;

    sf::Clock gameGlock;
    // LOOP WHILE
    while (window.isOpen())
    {
        sf::Time deltaTime = gameGlock.restart();
        ImGui::SFML::Update(window, deltaTime);

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

            // Zoom
            if (state == State::Editor)
            {
                editor.handleEvent(event);
            }

            ImGui::SFML::ProcessEvent(window, event);
        }

        window.clear();
        if (state == State::Game)
        {
            window.setView(window.getDefaultView());
            player.update(deltaTime.asSeconds());
            renderer.draw3DView(window, player, map);
        }
        else
        {

            //map.draw(window);  // Draw 2D map
            editor.run(window, map);
        }

        ImGui::SFML::Render(window);
        window.display();

        // Frame rate (this line overwrites the Title in the Initial window settings).
        window.setTitle("Raycaster - v.1.0 | FrameRate: " + std::to_string(1.0f / deltaTime.asSeconds()));

    } // END LOOP WHILE

    ImGui::SFML::Shutdown();

    return 0;
}
