/**
 * @file    map.hpp
 *
 * @brief   Creates the map where the tests will be carried out.
 *          Controls cell size.
*/

#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

class Map
{
public:
    Map(float cellSize, int width, int height);
    Map(float cellSize, const std::string &filename);

    void draw(sf::RenderTarget &target);

    const std::vector<std::vector<sf::Color>> &getGrid() const;
    float getCellSize() const;

private:
    std::vector<std::vector<sf::Color>> grid;
    float cellSize;
};
