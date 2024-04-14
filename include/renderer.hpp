/**
 * @file   renderer.hpp
 *
 * @brief  Creates the Renderer class.
 *         Method for drawing ray lines and "3D" visualization.
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "player.hpp"
#include "map.hpp"
#include "constants.hpp"

class Renderer
{
public:
    void init();
    void draw3DView(sf::RenderTarget &target, const Player &player, const Map &map);

private:
    sf::Texture skyTexture;

    sf::Texture screenBuffer;
    sf::Sprite screenBufferSprite;
};
