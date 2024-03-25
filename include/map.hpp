/**
 * @file    map.hpp
 *
 * @brief   Creates the map where the tests will be carried out.
 *          Controls cell size.
*/

#pragma once

#include <SFML/Graphics.hpp>

#include <filesystem>
#include <array>
#include <vector>
#include <cstring>
#include <unordered_map>

class Map
{
public:
    static constexpr int LAYER_WALLS { 0 };
    static constexpr int LAYER_FLOOR { 1 };
    static constexpr int LAYER_CEILING { 2 };
    static constexpr int NUM_LAYERS { 3 };

    Map(float cellSize);

    float getCellSize() const;
    int getMapCell(int x, int y, int layer) const;
    void setMapCell(int x, int y, int layer, int value);

    void draw(sf::RenderTarget &target, int layer) const;
    void load(const std::filesystem::path &path);
    void save(const std::filesystem::path &path) const;

private:
    std::vector<std::vector<std::array<int, NUM_LAYERS>>> grid;
    float cellSize;
};
