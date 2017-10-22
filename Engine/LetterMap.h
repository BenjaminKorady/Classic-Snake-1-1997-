/**
	Manages the letters drawn onto the board
	Mainly maps the letters to a binary value which is later used to draw black(true) / green(false) pixels

	@author: Benjamin Korady
	@version: 1.1   22/10/2017
*/
#pragma once

#include <string>
#include <vector>

class LetterMap {
public:
    LetterMap();

    void set(char c);
    
    static std::vector<std::string> splitStringByLimit(std::string str, const int limit, const int letterSpacing);
	static int getStringWidth(std::string str, const int letterSpacing);

public:
	static constexpr int MAX_WIDTH = 8;
    int width;
    static constexpr int height = 8;
    char value;
    __int64 map;

private:
	void set(int widthIn, __int64 bin);
};