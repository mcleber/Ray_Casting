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

    static constexpr const char *LAYER_NAMES[NUM_LAYERS] = {
        "Wall",
        "Floor",
        "Ceiling",
    };

    Map() = default;

    int getMapCell(int x, int y, int layer) const;
    void setMapCell(int x, int y, int layer, int value);
    void fill(int layer, int value);
    size_t getWidth();
    size_t getHeight();
    void resize(size_t width, int height);

    void draw(sf::RenderTarget &target, float cellSize, int layer) const;
    void load(const std::filesystem::path &path);
    void save(const std::filesystem::path &path) const;

private:
    std::vector<std::vector<std::array<int, NUM_LAYERS>>> grid;

};
