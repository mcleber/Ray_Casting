/**
 * @file   constants.hpp
 *
 * @brief  Reune fórmulas, constantes e variáveis executadas em tempo de compilação.
 */

#pragma once

#include <cstddef>

constexpr float PI {3.141592653589793f};

constexpr float TURN_SPEED {120.0f};

constexpr float MOVE_SPEED {100.0f};

constexpr size_t MAX_RAYCASTING_STEPS {16};

constexpr size_t MAX_RAYCASTING_DEPTH {64};

constexpr float PLAYER_FOV {60.f};

constexpr float SCREEN_W {1024.0f};

constexpr float SCREEN_H {768.0f};

constexpr size_t NUM_RAYS {600}; // Se usar um número maior (ex. 1200), cria smooth nas paredes

constexpr float COLUMN_WIDTH {SCREEN_W / (float)NUM_RAYS};

