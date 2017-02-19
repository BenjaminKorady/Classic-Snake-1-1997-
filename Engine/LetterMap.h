#pragma once

#include <string>

class LetterMap {
public:

    LetterMap();

    void set(char c);
    ~LetterMap();
    
    static int splitStringByLimit(std::string* out, std::string str, const int limit, const int letterSpacing);
    int width;
    static constexpr int height = 8;
    char value;
    bool *map;

private:
    void set(int widthIn, char* string);
};