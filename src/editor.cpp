/**
 * @file    editor.cpp
 *
 * @brief   Creates the map editor with Panning and Zooming.
*/

#include "../include/editor.hpp"
#include "../include/map.hpp"
#include "../include/resources.hpp"

#include "../include/ImGuiFileDialog.h"
#include "../include/imgui-SFML.h"
#include "../include/imgui.h"

#include <SFML/Graphics.hpp>

void Editor::init(sf::RenderWindow &window)
{
    currentLayer = Map::LAYER_WALLS;
    view = window.getView();
    cell.setFillColor(sf::Color::Green);
}

// Right-click panning.
void Editor::run(sf::RenderWindow &window, Map &map)
{
    // ImGui Menu Bar
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open"))
            {
                ImGuiFileDialog::Instance()->OpenDialog("OpenDialog", "Open", ".map");
            }

            if (ImGui::MenuItem("Save"))
            {
                if (savedFileName.empty())
                {
                    ImGuiFileDialog::Instance()->OpenDialog("SaveDialog", "Save", ".map");
                }
                else
                {
                    map.save(savedFileName);
                }
            }

            if (ImGui::MenuItem("Save As"))
            {
                ImGuiFileDialog::Instance()->OpenDialog("SaveDialog", "Save As", ".map");
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    } // END ImGui MENU

    if (ImGuiFileDialog::Instance()->Display("SaveDialog"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            savedFileName = ImGuiFileDialog::Instance()->GetFilePathName();
            map.save(savedFileName);
        }
        ImGuiFileDialog::Instance()->Close();
    }

    if (ImGuiFileDialog::Instance()->Display("OpenDialog"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            savedFileName = ImGuiFileDialog::Instance()->GetFilePathName();
            map.load(savedFileName);
        }
        ImGuiFileDialog::Instance()->Close();
    }

    // ImGui Editing Options
    ImGui::Begin("Editing Options");
    ImGui::Text("Texture No.: "); // Texture Number
    ImGui::InputInt("##tex_no", &textureNumber);

    int textureSize = Resources::wallTexture.getSize().y;
    ImGui::Text("Preview: ");
    ImGui::Image(
        sf::Sprite
        {
            Resources::wallTexture,
            sf::IntRect(textureNumber * textureSize, 0, textureSize, textureSize),
        },
        sf::Vector2f(100.0f, 100.0f));

    ImGui::End(); //END ImGUI Editing Options

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        if (isFirstMouse)
        {
            lastMousePos = mousePos;
            isFirstMouse = false;
        }
        else
        {
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

    if (!ImGui::GetIO().WantCaptureMouse)
    {
        // Draw Cells
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
        sf::Vector2i mapPos = (sf::Vector2i)(worldPos / map.getCellSize());
        cell.setSize(sf::Vector2f(map.getCellSize(), map.getCellSize()));
        cell.setPosition((sf::Vector2f)mapPos * map.getCellSize());
        window.draw(cell);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            map.setMapCell(mapPos.x, mapPos.y, currentLayer,
                        sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 0 : textureNumber + 1);
        }
    }

    map.draw(window, currentLayer);
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
