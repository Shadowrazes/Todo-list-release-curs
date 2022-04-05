#include <configNote.h>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using namespace std;

vector<note> readNotesFromFile(string fileName)
{
    string jsonTasks;

    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error, file 'tasks.json' not readed" << endl;
        std::ofstream file(fileName);

        vector<note> tmp;
        return tmp;
    }

    if (file.peek() == EOF) {
        vector<note> tmp;
        return tmp;
    }

    getline(file, jsonTasks);
    file.close();
    vector<note> notes;

    nlohmann::json j = nlohmann::json::parse(jsonTasks);

    note tmp;
    for (int i = 0; i < (int)j.size(); i++) {
        tmp.article = j[i]["article"].get<string>();
        tmp.description = j[i]["description"].get<string>();
        tmp.status = j[i]["status"].get<bool>();

        notes.push_back(tmp);
    }

    return notes;
}

void writeNotesInFile(vector<note> notes)
{
    nlohmann::json j{};

    for (int i = 0; i < (int)notes.size(); i++) {
        j[i]["article"] = notes[i].article;
        j[i]["description"] = notes[i].description;
        j[i]["status"] = notes[i].status;
    }

    string jsonString = j.dump();

    ofstream file;
    file.open("tasks.json");

    if (!file.is_open()) {
        cout << "Error, file 'tasks.json' not writen" << endl;
    }

    file << jsonString;
    file.close();
}
