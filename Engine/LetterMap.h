#pragma once

class LetterMap {
public:

    LetterMap();
    void set(int widthIn, int heightIn, char* string);
    ~LetterMap();
    int width;
    int height;
    bool *map;
};