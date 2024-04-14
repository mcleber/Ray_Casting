/**
 * @file    player.cpp
 *
 * @brief   Creates control for the player.
 *          Implements the Draw and Update classes.
*/

#include <cmath>

#include "../include/constants.hpp"
#include "../include/player.hpp"

void Player::draw(sf::RenderTarget &target)
{
    sf::CircleShape circle(8.0f);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(position);
    circle.setFillColor(sf::Color::Yellow);

    sf::RectangleShape line(sf::Vector2f(24.0f, 2.0f));
    line.setPosition(position);
    line.setRotation(angle);
    line.setFillColor(sf::Color::Yellow);

    target.draw(line);
    target.draw(circle);
}

void Player::update(float deltaTime, const Map &map)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        angle -= TURN_SPEED * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        angle += TURN_SPEED * deltaTime;
    }

    float radians = angle * PI / 180.0f;
    sf::Vector2f move {};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        move.x += cos(radians);
        move.y += sin(radians);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        move.x -= cos(radians);
        move.y -= sin(radians);
    }

    // Collision
    float xOffset = move.x > 0.0f ? PLAYER_SIZE : -PLAYER_SIZE;
    float yOffset = move.y > 0.0f ? PLAYER_SIZE : -PLAYER_SIZE;
    move *= MOVE_SPEED * deltaTime;
    if (map.getMapCell(position.x + move.x + xOffset, position.y, Map::LAYER_WALLS) == 0)
    {
        position.x += move.x;
    }

    if (map.getMapCell(position.x, position.y + move.y + yOffset, Map::LAYER_WALLS) == 0)
    {
        position.y += move.y;
    }
}
