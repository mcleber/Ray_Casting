/**
 * @file    editor.cpp
 *
 * @brief   Creates the map editor with Panning and Zooming.
*/

#include "../include/editor.hpp"

#include <SFML/Graphics.hpp>

void Editor::init(sf::RenderWindow &window)
{
    view = window.getView();
}

// Right-click panning.
void Editor::run(sf::RenderWindow &window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        if (isFirstMouse)
        {
            lastMousePos = sf::Mouse::getPosition(window);
            isFirstMouse = false;
        }
        else
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2i mouseDelta = mousePos - lastMousePos;

            view.setCenter(view.getCenter() - (sf::Vector2f)mouseDelta);

            sf::Mouse::setPosition(lastMousePos, window);
        }

        window.setMouseCursorVisible(false);
    }
    else
    {
        isFirstMouse = true;
        window.setMouseCursorVisible(true);
    }

    window.setView(view);
}

// Mouse scroll wheel for zooming.
void Editor::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseWheelScrolled)
    {
        float zoom = 1.0f - 0.1f * event.mouseWheelScroll.delta;
        view.zoom(zoom);
    }
}
