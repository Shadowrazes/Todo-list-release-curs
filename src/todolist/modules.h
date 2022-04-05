#pragma once

#include <SFML/Graphics.hpp>
#include <configModules.h>
#include <string>

Input addInput(int x, int y, int width, int height, std::string text);
void drawInput(
        sf::RenderWindow& window, sf::Font font, Input& input, bool wrap);
void reTextInput(sf::RenderWindow& window, Input& input, std::string text);
void addInputFocus(Input& input);
void deleteInputFocus(Input& input);
void reTextInput(Input& input, char text);
void setInputFocus(Input& input, sf::Vector2f mouse);
