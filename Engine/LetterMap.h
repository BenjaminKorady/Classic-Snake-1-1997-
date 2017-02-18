#pragma once

class LetterMap {
public:

    LetterMap();

    void set(char c);
    ~LetterMap();


    int width;
    int height;
    char value;
    bool *map;

private:
    void set(int widthIn, int heightIn, char* string);
};