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
    ImGui::Text("Layer");
    if (ImGui::BeginCombo("##layer", Map::LAYER_NAMES[currentLayer]))
    {
        for (size_t i = 0; i < Map::NUM_LAYERS; i++)
        {
            if (ImGui::Selectable(Map::LAYER_NAMES[i], currentLayer == i))
            {
                currentLayer = i;
            }
        }

        ImGui::EndCombo();
    }

    ImGui::Text("Texture No.: "); // Texture Number
    ImGui::InputInt("##tex_no", &textureNumber);

    int textureSize = Resources::textures.getSize().y;
    ImGui::Text("Preview: ");
    ImGui::Image(
        sf::Sprite
        {
            Resources::textures,
            sf::IntRect(textureNumber * textureSize, 0, textureSize, textureSize),
        },
        sf::Vector2f(100.0f, 100.0f));

    if (ImGui::Button("Fill"))
    {
        map.fill(currentLayer, textureNumber + 1);
    }

    ImGui::SameLine();
    if (ImGui::Button("Clear"))
    {
        map.fill(currentLayer, 0);
    }

    static int newSize[2];
    if (ImGui::Button("Resize"))
    {
        newSize[0] = map.getWidth();
        newSize[1] = map.getHeight();
        ImGui::OpenPopup("Resize");
    }

    if (ImGui::BeginPopupModal("Resize"))
    {
        ImGui::Text("New Size:");
        ImGui::InputInt2("##newSize", newSize);
        newSize[0] = std::max(0, newSize[0]);
        newSize[1] = std::max(0, newSize[1]);

        if (ImGui::Button("OK"))
        {
                        //width     height
            map.resize(newSize[0], newSize[1]);
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    ImGui::End();

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
        sf::Vector2i mapPos = (sf::Vector2i)(worldPos / CELL_SIZE);
        cell.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        cell.setPosition((sf::Vector2f)mapPos * CELL_SIZE);
        window.draw(cell);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            map.setMapCell(mapPos.x, mapPos.y, currentLayer,
                        sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 0 : textureNumber + 1);
        }
    }

    map.draw(window, CELL_SIZE, currentLayer);
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
