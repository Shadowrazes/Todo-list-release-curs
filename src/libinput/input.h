#pragma once

#include <configNote.h>
#include <vector>

std::vector<note> readNotesFromFile(std::string fileName);
void writeNotesInFile(std::vector<note> notes);
