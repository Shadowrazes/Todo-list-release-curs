#include <SFML/Graphics.hpp>
#include <configNote.h>
#include <editWindow.h>
#include <input.h>
#include <iostream>
#include <vector>

#define NOTE_WIDTH 1720
#define NOTE_HEIGTH 50
#define NOTE_X 100
#define NOTE_Y 75
#define MARGIN 100

using namespace std;
using namespace sf;

void askWindow(RenderWindow& window, Font& font, bool& confirmation)
{
    Text askText(L"Удалить выбранную задачу?", font, 20),
            yesText(L"Да", font, 20), cancelText(L"Отмена", font, 20);

    RectangleShape askWindowPlace(Vector2f(300, 100));
    RectangleShape yesPlace(Vector2f(75, 25));
    RectangleShape cancelPlace(Vector2f(75, 25));

    askText.setPosition(
            window.getSize().x / 2 - askText.getGlobalBounds().width / 2,
            window.getSize().y / 2 - 20);

    yesPlace.setPosition(
            window.getSize().x / 2 - askText.getGlobalBounds().width / 3,
            window.getSize().y / 2 + 20);
    yesPlace.setFillColor(Color(0, 0, 0, 0));
    yesPlace.setOutlineThickness(3);
    yesPlace.setOutlineColor(Color(255, 255, 255, 0));

    yesText.setPosition(
            window.getSize().x / 2 - askText.getGlobalBounds().width / 4,
            window.getSize().y / 2 + 20);

    cancelPlace.setPosition(
            window.getSize().x / 2 + askText.getGlobalBounds().width / 10,
            window.getSize().y / 2 + 20);
    cancelPlace.setFillColor(Color(0, 0, 0, 0));
    cancelPlace.setOutlineThickness(3);
    cancelPlace.setOutlineColor(Color(255, 255, 255, 0));
    cancelText.setPosition(
            window.getSize().x / 2 + askText.getGlobalBounds().width / 10,
            window.getSize().y / 2 + 20);

    window.draw(askText);
    window.draw(yesText);
    window.draw(cancelText);

    while (!confirmation) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::MouseButtonPressed
                && event.mouseButton.button == Mouse::Left) {
                if (yesPlace.getGlobalBounds().contains(
                            Vector2f(Mouse::getPosition())))
                    confirmation = true;

                if (cancelPlace.getGlobalBounds().contains(
                            Vector2f(Mouse::getPosition())))
                    return;

                if (Keyboard::isKeyPressed(Keyboard::Escape)
                    && Keyboard::isKeyPressed(Keyboard::LShift))
                    window.close();
            }
            if (event.type == Event::MouseMoved) {
                if (yesPlace.getGlobalBounds().contains(
                            Vector2f(Mouse::getPosition())))
                    yesPlace.setOutlineColor(Color(255, 255, 255, 255));
                else
                    yesPlace.setOutlineColor(Color(0, 0, 0, 255));

                if (cancelPlace.getGlobalBounds().contains(
                            Vector2f(Mouse::getPosition())))
                    cancelPlace.setOutlineColor(Color(255, 255, 255, 255));
                else
                    cancelPlace.setOutlineColor(Color(0, 0, 0, 255));
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                return;
            }
        }
        window.draw(yesPlace);
        window.draw(cancelPlace);
        window.display();
        sleep(milliseconds(1000 / 60));
    }
}

void drawAddButton(RenderWindow& window, Font font, int i)
{
    RectangleShape addButton;
    addButton.setPosition(NOTE_X, i * NOTE_Y + MARGIN);
    addButton.setSize(Vector2f(NOTE_WIDTH, NOTE_HEIGTH));
    addButton.setFillColor(Color(0, 0, 0, 0));
    window.draw(addButton);

    RectangleShape plus;
    Texture plusTexture;
    plusTexture.loadFromFile("../interface/images/plus.png");
    plus.setTexture(&plusTexture);

    plus.setPosition(NOTE_X + 5, i * NOTE_Y + MARGIN + 10);
    plus.setSize(Vector2f(30, 30));

    window.draw(plus);

    Text text(L"Добавить задачу", font, 20);
    text.setPosition(NOTE_X + 50, i * NOTE_Y + MARGIN + 10);
    window.draw(text);
}

void drawNotes(RenderWindow& window, Font font, vector<note> notes)
{
    Texture check, remove;
    check.loadFromFile("../interface/images/check.png");
    remove.loadFromFile("../interface/images/basket.png");

    Text text("", font, 20);
    RectangleShape tmp, removeRect(Vector2f(40, 30));
    removeRect.setFillColor(Color::White);
    removeRect.setTexture(&remove);

    CircleShape outline(15), outlineCompleted(15);
    outline.setFillColor(Color(0, 0, 0, 0));
    outline.setOutlineThickness(2);
    outline.setOutlineColor(Color::Red);

    outlineCompleted.setTexture(&check);

    unsigned int i;
    for (i = 0; i < notes.size(); i++) {
        tmp.setSize(Vector2f(NOTE_WIDTH, NOTE_HEIGTH));
        tmp.setFillColor(Color(0, 0, 0, 0));
        tmp.setPosition(NOTE_X, i * NOTE_Y + MARGIN);

        removeRect.setPosition(
                NOTE_X + NOTE_WIDTH * 0.85, i * NOTE_Y + MARGIN + 10);

        outline.setPosition(NOTE_X + 5, i * NOTE_Y + MARGIN + 10);

        text.setString(notes[i].article);
        text.setStyle(Text::Regular);
        text.setPosition(
                NOTE_X + outline.getGlobalBounds().width + 15,
                i * NOTE_Y + MARGIN + 10);

        if (notes[i].status) {
            outlineCompleted.setPosition(NOTE_X + 5, i * NOTE_Y + MARGIN + 10);
            window.draw(outlineCompleted);
            text.setStyle(Text::StrikeThrough);
        }

        window.draw(outline);
        window.draw(removeRect);
        window.draw(tmp);
        window.draw(text);
    }

    drawAddButton(window, font, i);
}

void noteFocus(RenderWindow& window, Vector2f notePos)
{
    RectangleShape line(Vector2f(NOTE_WIDTH, 2));
    line.setFillColor(Color::White);
    line.setPosition(notePos.x, notePos.y - 2);
    window.draw(line);
    line.setPosition(notePos.x, notePos.y + NOTE_HEIGTH);
    window.draw(line);
}

bool checkClickOnNoteElem(
        Vector2f mousePos, Vector2f elemPos, Vector2f elemSizes)
{
    if (mousePos.x > elemPos.x && mousePos.x < elemPos.x + elemSizes.x
        && mousePos.y > elemPos.y && mousePos.y < elemPos.y + elemSizes.y)
        return true;
    else
        return false;
}

bool checkMouseClick(Vector2f mousePos, int i)
{
    if (mousePos.x > NOTE_X && mousePos.x < NOTE_X + NOTE_WIDTH
        && mousePos.y > i * NOTE_Y + MARGIN
        && mousePos.y < i * NOTE_Y + MARGIN + NOTE_HEIGTH)
        return true;
    else
        return false;
}

void addNote(
        vector<note>& notes, string article, string description, bool status)
{
    note tmp;
    tmp.article = article;
    tmp.description = description;
    tmp.status = status;
    notes.push_back(tmp);
}

void notesList(RenderWindow& window, Font font)
{
    Texture backg;
    backg.loadFromFile("../interface/images/background.jpg");
    Sprite background(backg);
    vector<note> notes = readNotesFromFile("tasks.json");

    Text topTitle(L"Список задач", font, 40);
    topTitle.setFillColor(Color::White);
    topTitle.setPosition(
            (window.getSize().x - topTitle.getGlobalBounds().width) / 2, 0);

    RectangleShape topTitleBorder(Vector2f(window.getSize().x, 2));
    topTitleBorder.setFillColor(Color::Red);
    topTitleBorder.setPosition(
            0,
            topTitle.getPosition().y + topTitle.getGlobalBounds().height + 25);

    bool clickOnNote = false, confirmation = false;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed
                || (Keyboard::isKeyPressed(Keyboard::Escape)
                    && Keyboard::isKeyPressed(Keyboard::LShift))) {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    for (unsigned int i = 0; i < notes.size(); i++) {
                        if (checkClickOnNoteElem(
                                    Vector2f(Mouse::getPosition()),
                                    Vector2f(
                                            NOTE_X + 5,
                                            i * NOTE_Y + MARGIN + 10),
                                    Vector2f(30, 30))) {
                            notes[i].status = !notes[i].status;
                            clickOnNote = true;
                        }

                        if (checkClickOnNoteElem(
                                    Vector2f(Mouse::getPosition()),
                                    Vector2f(
                                            NOTE_X + NOTE_WIDTH * 0.85,
                                            i * NOTE_Y + MARGIN + 10),
                                    Vector2f(40, 30))) {
                            askWindow(window, font, confirmation);
                            if (confirmation) {
                                notes.erase(notes.begin() + i);
                                writeNotesInFile(notes);
                            }

                            confirmation = false;
                            clickOnNote = true;
                        }
                    }

                    if (!clickOnNote) {
                        unsigned int i;
                        for (i = 0; i < notes.size(); i++) {
                            if (checkMouseClick(
                                        Vector2f(Mouse::getPosition()), i)) {
                                openEditWindow(
                                        window, background, font, notes, i);
                            }
                        }
                        if (checkMouseClick(
                                    Vector2f(Mouse::getPosition()), i)) {
                            addNote(notes, "", "", false);
                            writeNotesInFile(notes);
                        }
                    }
                    clickOnNote = false;
                }
            }
        }
        window.clear();
        window.draw(background);
        drawNotes(window, font, notes);
        window.draw(topTitle);
        window.draw(topTitleBorder);

        for (unsigned int i = 0; i < notes.size() + 1; i++) {
            if (checkMouseClick(Vector2f(Mouse::getPosition()), i)) {
                noteFocus(window, Vector2f(NOTE_X, i * NOTE_Y + MARGIN));
            }
        }

        window.display();
        sleep(milliseconds(1000 / 60));
    }
}
