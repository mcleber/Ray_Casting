/**
 * @file    map.hpp
 *
 * @brief   Creates the map where the tests will be carried out.
 *          Controls cell size.
*/

#pragma once

#include <filesystem>
#include <vector>
#include <cstring>

#include <SFML/Graphics.hpp>

using MapGrid = std::vector<std::vector<int>>;

class Map
{
public:
    Map(float cellSize);
    Map(float cellSize, int width, int height);
    Map(float cellSize, const std::string &filename);

    void draw(sf::RenderTarget &target);
    void setMapCell(int x, int y, int value);

    void load(const std::filesystem::path &path);
    void save(const std::filesystem::path &path);

    const MapGrid &getGrid() const;
    float getCellSize() const;

private:
    MapGrid grid;
    float cellSize;
};
