#include <SFML/Graphics.hpp>
#include <configModules.h>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

Input addInput(int x, int y, int width, int height, string text)
{
    Input input;
    input.x = x;
    input.y = y;
    input.width = width;
    input.height = height;
    input.text = text;
    input.focus = false;

    return input;
}

void addInputFocus(Input& input)
{
    if (!input.focus) {
        input.focus = true;
    }
}

void deleteInputFocus(Input& input)
{
    if (input.focus) {
        input.focus = false;
    }
}

void setInputFocus(Input& input, Vector2f mouse)
{
    if (mouse.x >= input.x && mouse.x <= input.x + input.width
        && mouse.y >= input.y && mouse.y <= input.y + input.height) {
        addInputFocus(input);
    } else {
        deleteInputFocus(input);
    }
}

void drawInput(RenderWindow& window, Font font, Input& input, bool wrap)
{
    RectangleShape tmp;
    tmp.setFillColor(Color(21, 63, 124, 120));
    tmp.setPosition(input.x, input.y);
    tmp.setSize(Vector2f(input.width, input.height));

    Text text("", font, 20);

    if (input.focus) {
        text.setString(input.text + '|');
    } else {
        text.setString(input.text);
    }

    text.setPosition(input.x + 20, input.y + 20);
    string symb;

    if (text.getLocalBounds().width > input.width - 40) {
        if (wrap) {
            symb = input.text.substr(input.text.length() - 1, 1);
            input.text = input.text.substr(0, input.text.length() - 1);
            input.text += '\n';
            input.text += symb;
        } else {
            input.text = input.text.substr(0, input.text.length() - 1);
        }
    };

    window.draw(tmp);
    window.draw(text);
}

void reTextInput(Input& input, char text)
{
    input.text += text;
}
