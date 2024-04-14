/**
 * @file    player.hpp
 *
 * @brief   Creates the player and controls via keyboard.
 *          Adds draw and update methods.
*/

#pragma once

#include "map.hpp"

#include <SFML/Graphics.hpp>

class Player
{
public:
    void draw(sf::RenderTarget &target);

    void update(float deltaTime, const Map &map);

    sf::Vector2f position;
    float angle;
};
