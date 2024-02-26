/**
 * @file    map.cpp
 *
 * @brief   Creates the grid for the map.
*/

#include "../include/map.hpp"

#include <iostream>
#include <cstddef>

#include <SFML/Graphics.hpp>


Map::Map(float cellSize, int width, int height)
    : cellSize(cellSize), grid(height, std::vector(width, 0)) {};

Map::Map(float cellSize, const std::string &filename) : cellSize(cellSize)
{
    sf::Image image;
    if (!image.loadFromFile(filename))
    {
        std::cerr << "Failed to load map image" << std::endl;
        return;
    }

    grid = std::vector(image.getSize().y, std::vector(image.getSize().x, 0));

    for (size_t y = 0; y < image.getSize().y; y++)
    {
        for (size_t x = 0; x < image.getSize().x; x++)
        {
            grid[y][x] = image.getPixel(x, y) == sf::Color::Black ? 0 : 1;
        }
    }

}

// Create the map grid
void Map::draw(sf::RenderTarget &target)
{
    if (grid.empty())
    {
        return;
    }
    sf::RectangleShape background(sf::Vector2f((float)grid[0].size() * cellSize,
        (float)grid.size() * cellSize));

    // Grid color
    background.setFillColor(sf::Color::Black);

    target.draw(background);

    sf::RectangleShape cell(sf::Vector2f(cellSize * 0.95f, cellSize * 0.95f));

    for (size_t y = 0; y < grid.size(); y++)
    {
        for (size_t x = 0; x < grid[y].size(); x++)
        {
            // Background color
            cell.setFillColor(grid[y][x] ? sf::Color::White : sf::Color(95, 95, 95));

                // sf::Color color(255, 0, 0); // red
                // color.r = 0;                // make it black
                // color.b = 128;              // make it dark blue

            cell.setPosition(sf::Vector2f(x, y) * cellSize +
                sf::Vector2f(cellSize * 0.025f, cellSize * 0.025f));

            target.draw(cell);
        }
    }

}

void Map::setMapCell(int x, int y, int value)
{
    if (y > 0 && y < grid.size() && x > 0 && x < grid[y].size())
    {
        grid[y][x] = value;
    }
}

const MapGrid &Map::getGrid() const
{
    return grid;
}
float Map::getCellSize() const
{
    return cellSize;
}
