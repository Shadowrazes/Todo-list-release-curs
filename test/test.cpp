#define CATCH_CONFIG_MAIN
#include <SFML/Graphics.hpp>
#include <catch.hpp>
#include <editWindow.h>
#include <input.h>
#include <iostream>
#include <modules.h>
#include <notesList.h>
#include <vector>

TEST_CASE("Work with files", "")
{
    SECTION("Read/Write file")
    {
        note a;
        a.article = "Math";
        a.description = "Homework";
        a.status = false;

        note b;
        b.article = "Meet with Gena";
        b.description = "06:00 PM";
        b.status = true;

        note c;
        c.article = "Course Work Deadline";
        c.description = "1st June";
        c.status = false;

        std::vector<note> notes;
        notes.push_back(a);
        notes.push_back(b);
        notes.push_back(c);

        writeNotesInFile(notes);

        std::vector<note> notes1;
        notes1 = readNotesFromFile("tasks.json");

        CHECK(notes1[0].article == "Math");
        CHECK(notes1[0].description == "Homework");
        CHECK(notes1[0].status == false);
        CHECK(notes1[1].article == "Meet with Gena");
        CHECK(notes1[1].description == "06:00 PM");
        CHECK(notes1[1].status == true);
        CHECK(notes1[2].article == "Course Work Deadline");
        CHECK(notes1[2].description == "1st June");
        CHECK(notes1[2].status == false);
        system("pause");
    }
}

TEST_CASE("Work with Input", "")
{
    SECTION("Add Input")
    {
        Input a = addInput(100, 100, 500, 500, "article");

        CHECK(a.x == 100);
        CHECK(a.y == 100);
        CHECK(a.width == 500);
        CHECK(a.height == 500);
        CHECK(a.text == "article");
        system("pause");
    }

    SECTION("Add focus on Input")
    {
        Input a;
        a.focus = false;
        addInputFocus(a);

        CHECK(a.focus == true);
        system("pause");
    }

    SECTION("Delete focus on Input")
    {
        Input a;
        a.focus = true;
        deleteInputFocus(a);

        CHECK(a.focus == false);
        system("pause");
    }

    SECTION("Check interscapes with Input")
    {
        Input a;

        a.x = 50;
        a.y = 50;
        a.width = 100;
        a.height = 100;
        a.focus = false;
        setInputFocus(a, sf::Vector2f(100, 100));
        CHECK(a.focus == true);

        a.x = 50;
        a.y = 50;
        a.width = 100;
        a.height = 100;
        a.focus = false;
        setInputFocus(a, sf::Vector2f(200, 100));
        CHECK(a.focus == false);

        a.x = 50;
        a.y = 50;
        a.width = 100;
        a.height = 100;
        a.focus = false;
        setInputFocus(a, sf::Vector2f(0, 100));
        CHECK(a.focus == false);

        a.x = 50;
        a.y = 50;
        a.width = 100;
        a.height = 100;
        a.focus = false;
        setInputFocus(a, sf::Vector2f(50, 50));
        CHECK(a.focus == true);

        a.x = 50;
        a.y = 50;
        a.width = 100;
        a.height = 100;
        a.focus = false;
        setInputFocus(a, sf::Vector2f(151, 51));
        CHECK(a.focus == false);

        system("pause");
    }

    SECTION("Change text in Input")
    {
        Input a;
        a.text = "123";
        reTextInput(a, '4');
        CHECK(a.text == "1234");
        system("pause");
    }
}

TEST_CASE("check mouse click", "")
{
    SECTION("check click on the note element")
    {
        sf::Vector2f mousePos1(289, 279);
        sf::Vector2f elemPos1(250, 250);
        sf::Vector2f elemSizes1(40, 30);
        CHECK(checkClickOnNoteElem(mousePos1, elemPos1, elemSizes1) == 1);

        sf::Vector2f mousePos2(290, 280);
        sf::Vector2f elemPos2(250, 250);
        sf::Vector2f elemSizes2(40, 30);
        CHECK(checkClickOnNoteElem(mousePos2, elemPos2, elemSizes2) == 0);

        sf::Vector2f mousePos3(251, 251);
        sf::Vector2f elemPos3(250, 250);
        sf::Vector2f elemSizes3(40, 30);
        CHECK(checkClickOnNoteElem(mousePos3, elemPos3, elemSizes3) == 1);

        sf::Vector2f mousePos4(250, 250);
        sf::Vector2f elemPos4(250, 250);
        sf::Vector2f elemSizes4(40, 30);
        CHECK(checkClickOnNoteElem(mousePos4, elemPos4, elemSizes4) == 0);
        system("pause");
    }
    SECTION("check click on the note")
    {
        sf::Vector2f mousePos1(100, 100);
        int i = 0;
        CHECK(checkMouseClick(mousePos1, i) == 0);

        sf::Vector2f mousePos2(500, 149);
        i = 0;
        CHECK(checkMouseClick(mousePos2, i) == 1);

        sf::Vector2f mousePos3(99, 170);
        i = 1;
        CHECK(checkMouseClick(mousePos3, i) == 0);

        sf::Vector2f mousePos4(1700, 224);
        i = 1;
        CHECK(checkMouseClick(mousePos4, i) == 1);
        system("pause");
    }
}
