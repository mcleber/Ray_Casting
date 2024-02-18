/**
 * @file   renderer.hpp
 *
 * @brief  Creates the Renderer class.
 *         Method for drawing ray lines and "3D" visualization.
*/

#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "constants.hpp"
#include "map.hpp"
#include "player.hpp"

class Renderer
{
public:
    void init();

    void draw3DView(sf::RenderTarget &target, const Player &player, const Map &map);

private:
    sf::Texture  wallTexture, skyTexture;
    sf::Image floorImage;

    sf::Texture floorBuffer;
    sf::Sprite floorBufferSprite;
};
