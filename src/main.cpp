/**
 * @file    main.cpp
 *
 * @brief   Create a basic raycaster renderer in C++ using the SFML library.
 *          Baseado no Raycaster do canal "The Hello World Guy" no Youtube.
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
    /// Configurações iniciais da janela
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Ray Casting - 1.0",
        sf::Style::Titlebar | sf::Style::Close);

    /// Ajustar a posição da janela ao executar
    window.setPosition(sf::Vector2i(0, 0));

    /// Controle de velocidade (em fps)
    window.setFramerateLimit(60);

    /// Cria o objeto Map e carrega textura
    Map map(48.f, "./image/map.png");

    /// Cria o objeto Player
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
