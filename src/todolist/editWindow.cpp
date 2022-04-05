#include <configNote.h>
#include <input.h>
#include <iostream>
#include <modules.h>

using namespace std;
using namespace sf;

void openEditWindow(
        RenderWindow& window,
        Sprite& background,
        Font font,
        vector<note>& notes,
        int currentNote)
{
    Input articleInput
            = addInput(100, 100, 1720, 60, notes[currentNote].article);
    Input descriptionInput
            = addInput(100, 260, 1720, 500, notes[currentNote].description);

    RectangleShape closeButton;
    closeButton.setFillColor(Color(255, 255, 255, 255));
    closeButton.setPosition(10, 10);
    closeButton.setSize(Vector2f(30, 30));

    Texture closeTexture;
    closeTexture.loadFromFile("../interface/images/back.png");
    closeButton.setTexture(&closeTexture);

    bool editingNote = true;
    while (editingNote) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    setInputFocus(
                            articleInput,
                            Vector2f(event.mouseButton.x, event.mouseButton.y));
                    setInputFocus(
                            descriptionInput,
                            Vector2f(event.mouseButton.x, event.mouseButton.y));
                    if (event.mouseButton.x > closeButton.getPosition().x
                        && event.mouseButton.x < closeButton.getPosition().x
                                        + closeButton.getSize().x
                        && event.mouseButton.y > closeButton.getPosition().y
                        && event.mouseButton.y < closeButton.getPosition().y
                                        + closeButton.getSize().y) {
                        editingNote = false;
                    }
                }
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (articleInput.focus) {
                        if (event.text.unicode == 8) {
                            articleInput.text = articleInput.text.substr(
                                    0, articleInput.text.length() - 1);
                        } else {
                            reTextInput(
                                    articleInput,
                                    static_cast<char>(event.text.unicode));
                        }

                        notes[currentNote].article = articleInput.text;
                        writeNotesInFile(notes);
                    }
                    if (descriptionInput.focus) {
                        if (event.text.unicode == 8) {
                            descriptionInput.text
                                    = descriptionInput.text.substr(
                                            0,
                                            descriptionInput.text.length() - 1);
                        } else {
                            reTextInput(
                                    descriptionInput,
                                    static_cast<char>(event.text.unicode));
                        }
                        notes[currentNote].description = descriptionInput.text;
                        writeNotesInFile(notes);
                    }
                }
            }

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.draw(background);
        drawInput(window, font, articleInput, false);
        drawInput(window, font, descriptionInput, true);
        window.draw(closeButton);
        window.display();
        sleep(milliseconds(1000 / 60));
        window.clear();
    }
}
