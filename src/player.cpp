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

void Player::update(float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        angle -= TURN_SPEED * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        angle += TURN_SPEED * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        float radians = angle * PI / 180.0f;

        position.x += cos(radians) * MOVE_SPEED * deltaTime;
        position.y += sin(radians) * MOVE_SPEED * deltaTime;
    }
}
