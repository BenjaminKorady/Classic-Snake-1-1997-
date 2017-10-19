#pragma once

#include <string>
#include <vector>
class LetterMap {
public:

    LetterMap();

    void set(char c);
    ~LetterMap();
    
    static std::vector<std::string> splitStringByLimit(std::string str, const int limit, const int letterSpacing);
	static int getStringWidth(std::string str, const int letterSpacing);

public:
    int width;
    static constexpr int height = 8;
    char value;
    bool *map;

private:
    void set(int widthIn, char* string);
};