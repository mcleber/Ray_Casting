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
#include "sprite.hpp"

class Renderer
{
public:
    void init();
    void draw3DView(sf::RenderTarget &target, const Player &player, const Map &map, const std::vector<Sprite> &sprites);

private:
    sf::Texture skyTexture;

    sf::Texture screenBuffer;
    sf::Sprite screenBufferSprite;
    float zBuffer[(size_t)SCREEN_W];
};
