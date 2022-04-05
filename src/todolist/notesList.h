#pragma once

#include <SFML/Graphics.hpp>
#include <configNote.h>

void drawNotes(sf::RenderWindow& window, note);
void notesList(sf::RenderWindow& window, sf::Font font);
bool checkClickOnNoteElem(
        sf::Vector2f mousePos, sf::Vector2f elemPos, sf::Vector2f elemSizes);
bool checkMouseClick(sf::Vector2f mousePos, int i);
