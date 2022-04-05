#include <SFML/Graphics.hpp>
#include <configNote.h>
#include <input.h>
#include <iostream>
#include <notesList.h>
#include <vector>

using namespace sf;

int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(
            VideoMode(1920, 1080), "TodoList", Style::Fullscreen, settings);

    Font font;
    font.loadFromFile("../interface/font/times-new-roman.ttf");

    notesList(window, font);

    return 0;
}
