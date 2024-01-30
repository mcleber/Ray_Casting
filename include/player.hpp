/**
 * @file    player.hpp
 *
 * @brief   Cria o player e os controles via teclado.
 *          Adiciona os métodos draw e update.
*/

#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
    void draw(sf::RenderTarget &target);

    void update(float deltaTime);

    sf::Vector2f position;
    float angle;

private:

};
