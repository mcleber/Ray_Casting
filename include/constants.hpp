/**
 * @file   constants.hpp
 *
 * @brief  Formulas, constants and variables executed at compile time.
*/

#pragma once

#include <cstddef>

constexpr float PI {3.141592653589793f};

constexpr float TURN_SPEED {120.0f};

constexpr float MOVE_SPEED {120.0f};

constexpr size_t MAX_RAYCASTING_STEPS {16};

constexpr size_t MAX_RAYCASTING_DEPTH {64};

constexpr float PLAYER_FOV {60.0f};

constexpr float SCREEN_W {1024.0f};

constexpr float SCREEN_H {768.0f};

constexpr size_t NUM_RAYS {600}; // Large numbers (e.g. 1200) create smooth walls.

constexpr float COLUMN_WIDTH {SCREEN_W / (float)NUM_RAYS};

