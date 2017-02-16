#include "LetterMap.h"

LetterMap::LetterMap()
    :
    width(0),
    height(0)
{
}

void LetterMap::set(int widthIn, int heightIn, char* string)
{
    width = widthIn;
    height = heightIn;
    map = new bool[widthIn*heightIn];
    for (int i = 0; i < widthIn*heightIn; ++i) {
        if (string[i] == '1') {
            map[i] = true;
        }
        else if (string[i] == '0') {
            map[i] = false;
        }
    }
}

LetterMap::~LetterMap()
{
    delete[] map;
}

