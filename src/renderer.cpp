/**
 * @file    renderer.cpp
 *
 * @brief   Creates the "3D" version of the map.
 *          DDA (Digital Differential Analyzer) algorithm seamlessly
 *          work with textured and shaded walls.
 */

#include "../include/renderer.hpp"
#include "../include/resources.hpp"


#include <iostream>
#include <cmath>
#include <cstddef>
#include <algorithm>

struct Ray
{
    sf::Vector2f hitPosition;
    sf::Vector2u mapPosition;
    float distance;
    bool isHitVertical;
};

void Renderer::init()
{
    // Floor texture
    floorBuffer.create(SCREEN_W, SCREEN_H);
    floorBufferSprite.setTexture(floorBuffer);

    if (!skyTexture.loadFromFile("./image/sky_texture.png"))
    {
        std::cerr << "Failed to load sky_texture,png" << std::endl;
    }
    skyTexture.setRepeated(true);

    if (!floorImage.loadFromFile("./image/floor_texture.png"))
    {
        std::cerr << "Failed to load floor_texture.png" << std::endl;
    }

    if (floorImage.getSize().x != floorImage.getSize().y)
    {
        std::cerr << "ERROR: Texture is not square" << std::endl;
    }

}

void Renderer::draw3DView(sf::RenderTarget &target, const Player &player, const Map &map)
{
    float radians = player.angle * PI / 180.0f;
    sf::Vector2f directions{std::cos(radians), std::sin(radians)};
    sf::Vector2f plane{-directions.y, directions.x * 0.66f}; // plane camera
    sf::Vector2f position = player.position / map.getCellSize();

    // Sky
    int xOffset = SCREEN_W / PLAYER_TURN_SPEED * player.angle;
    while (xOffset < 0)
    {
        xOffset += skyTexture.getSize().x;
    }
    sf::Vertex sky[] =
    {
        // 4 Vertex
        sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(xOffset, 0.0f)),
        sf::Vertex(sf::Vector2f(0.0f, SCREEN_H),
                   sf::Vector2f(xOffset, skyTexture.getSize().y)),
        sf::Vertex(sf::Vector2f(SCREEN_W, SCREEN_H),
                   sf::Vector2f(xOffset + skyTexture.getSize().x,
                                skyTexture.getSize().y)),
        sf::Vertex(sf::Vector2f(SCREEN_W, 0.0f),
                   sf::Vector2f(xOffset + skyTexture.getSize().x, 0.0f)),
    };
    target.draw(sky, 4, sf::Quads, sf::RenderStates(&skyTexture));

    // Floor
    uint8_t floorPixels[(size_t)SCREEN_W * (size_t)SCREEN_H * 4]{}; // *4 -> 4 bytes (RGBA)
    for (size_t y = SCREEN_H / 2; y < SCREEN_H; y++)
    {
        sf::Vector2f rayDirLeft{directions - plane}, rayDirRight{directions + plane};

        float rowDistance = CAMERA_Z / ((float)y - SCREEN_H / 2);

        // Linear interpolation
        sf::Vector2f floorStep = rowDistance *  (rayDirRight - rayDirLeft) / SCREEN_W;
        sf::Vector2f floor = position + rowDistance * rayDirLeft;

        for (size_t x = 0; x < SCREEN_W; x++)
        {
            sf::Vector2i cell{floor};

            float textureSize = floorImage.getSize().x;
            sf::Vector2i texCoords{textureSize * (floor - (sf::Vector2f)cell)};
            texCoords.x &= (int)textureSize - 1;
            texCoords.y &= (int)textureSize - 1;

            // Remove artifacts
            sf::Color color = floorImage.getPixel(texCoords.x, texCoords.y);
            floorPixels[(x + y * (size_t)SCREEN_W) * 4 + 0] = color.r;
            floorPixels[(x + y * (size_t)SCREEN_W) * 4 + 1] = color.g;
            floorPixels[(x + y * (size_t)SCREEN_W) * 4 + 2] = color.b;
            floorPixels[(x + y * (size_t)SCREEN_W) * 4 + 3] = color.a;

            floor += floorStep;
        }
    }

    floorBuffer.update(floorPixels);
    target.draw(floorBufferSprite);

    // Wall
    sf::VertexArray walls{sf::Lines};
    for (size_t i = 0; i < SCREEN_W; i++)
    {
        float cameraX = i * 2.0f / SCREEN_W - 1.0f; // -1.0f -> 0.0f -> 1.0f

        sf::Vector2f rayPos = position;
        sf::Vector2f rayDir = directions + plane * cameraX;

        sf::Vector2f deltaDist{std::abs(1.0f / rayDir.x), std::abs(1.0f / rayDir.y)};

        sf::Vector2i mapPos{rayPos};
        sf::Vector2i step;
        sf::Vector2f sideDist;

        if (rayDir.x < 0.0f)
        {
            step.x = -1;
            sideDist.x = (-mapPos.x + rayPos.x) * deltaDist.x;
        }
        else
        {
            step.x = 1;
            sideDist.x = (mapPos.x - rayPos.x + 1.0f) * deltaDist.x;
        }

        if (rayDir.y < 0.0f)
        {
            step.y = -1;
            sideDist.y = (-mapPos.y + rayPos.y) * deltaDist.y;
        }
        else
        {
            step.y = 1;
            sideDist.y = (mapPos.y - rayPos.y + 1.0f) * deltaDist.y;
        }

        int hit{}, isHitVertical{};
        size_t depth = 0;
        while (hit == 0 && depth < MAX_RAYCASTING_DEPTH)
        {
            if (sideDist.x < sideDist.y)
            {
                sideDist.x += deltaDist.x;
                mapPos.x += step.x;
                isHitVertical = false;
            }
            else
            {
                sideDist.y += deltaDist.y;
                mapPos.y += step.y;
                isHitVertical = true;
            }

            hit = map.getMapCell(mapPos.x, mapPos.y, Map::LAYER_WALLS);
            depth++;
        }

        if (hit > 0)
        {
            float perpWallDist = isHitVertical ? sideDist.y - deltaDist.y : sideDist.x - deltaDist.x;
            float wallHeight = SCREEN_H / perpWallDist;

            float wallStart = (-wallHeight + SCREEN_H) / 2.0f;
            float wallEnd = (wallHeight + SCREEN_H) / 2.0f;

            // Wall textures
            float textureSize = Resources::wallTexture.getSize().y;

            float wallX = isHitVertical ? rayPos.x + perpWallDist * rayDir.x
                                        : rayPos.y + perpWallDist * rayDir.y;

            wallX -= std::floor(wallX);
            float textureX = wallX * textureSize;

            float brightness = 1.0f - (perpWallDist / (float)MAX_RAYCASTING_DEPTH);
            if (isHitVertical)
            {
                brightness *= 0.7f;
            }

            sf::Color color = sf::Color(255 * brightness, 255 * brightness, 255 * brightness);

            walls.append(sf::Vertex(sf::Vector2f((float)i, wallStart), color,
                            sf::Vector2f(textureX + (hit - 1) * textureSize, 0.0f)));
            walls.append(sf::Vertex(sf::Vector2f((float)i, wallEnd), color,
                            sf::Vector2f(textureX + (hit - 1) * textureSize, textureSize)));
        }
    }

    sf::RenderStates states{&Resources::wallTexture};
    target.draw(walls, states);

}
