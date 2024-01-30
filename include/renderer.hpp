/**
 * @file   renderer.hpp
 *
 * @brief  Cria a classe Renderer.
 *         Método para desenhar as linhas de raios e visualização "3D".
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

    void drawRays(sf::RenderTarget &target, const Player &player, const Map &map);

private:
    sf::Texture  wallTexture;
    sf::Sprite wallSprite;
};
