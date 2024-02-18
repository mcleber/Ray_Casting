/**
 * @file    editor.hpp
 *
 * @brief   Creates the map editor with Panning and Zooming.
*/

#pragma once

#include <SFML/Graphics.hpp>

class Editor
{
    public:
        void init(sf::RenderWindow &window);
        void run(sf::RenderWindow &window);

        void handleEvent(const sf::Event &event);

    private:
        bool isFirstMouse{}; // Capture the mouse.
        sf::Vector2i lastMousePos;
        sf::View view;
};
