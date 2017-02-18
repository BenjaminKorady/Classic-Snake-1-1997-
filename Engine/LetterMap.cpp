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

void LetterMap::set(char c)
{
    {
        switch (c) {
        case 'A':
            set(5, 8, "0111011011110111101111111110111101100000"); break;
        case 'B':
            set(5, 8, "1111011011111101101111011110111111000000"); break;
        case 'C':
            set(5, 8, "0111111000110001100011000110000111100000"); break;
        case 'D':
            set(5, 8, "1111011011110111101111011110111111000000"); break;
        case 'E':
            set(5, 8, "1111111000111101100011000110001111100000"); break;
        case 'F':
            set(5, 8, "1111111000111101100011000110001100000000"); break;
        case 'G':
            set(5, 8, "0111011000110001101111011110110111100000"); break;
        case 'H':
            set(5, 8, "1101111011111111101111011110111101100000"); break;
        case 'I':
            set(2, 8, "1111111111111100"); break;
        case 'J':
            set(4, 8, "00110011001100110011001111100000"); break;
        case 'K':
            set(6, 8, "110011110110111100111000111100110110110011000000"); break;
        case 'L':
            set(4, 8, "11001100110011001100110011110000"); break;
        case 'M':
            set(7, 8, "10000011100011111011111111111101011110001111000110000000"); break;
        case 'N':
            set(6, 8, "100011110011111011111111110111110011110001000000"); break;
        case 'O':
            set(6, 8, "011110110011110011110011110011110011011110000000"); break;
        case 'P':
            set(5, 8, "1111011011110111101111110110001100000000"); break;
        case 'Q':
            set(6, 8, "011110110011110011110011110011110111011110000011000000"); break;
        case 'R':
            set(5, 8, "1111011011110111101111110110101101100000"); break;
        case 'S':
            set(4, 8, "01111100110001100011001111100000"); break;
        case 'T':
            set(6, 8, "111111001100001100001100001100001100001100000000"); break;
        case 'U':
            set(5, 8, "1101111011110111101111011110110111000000"); break;
        case 'V':
            set(6, 8, "110011110011110011011110011110001100001100000000"); break;
        case 'W':
            set(7, 8, "11000111100011110101111111110111110011111001101100000000"); break;
        case 'X':
            set(6, 8, "110011110011011110001100011110110011110011000000"); break;
        case 'Y':
            set(6, 8, "110011110011011110001100001100001100001100000000"); break;
        case 'Z':
            set(5, 8, "1111100011001110111011100110001111100000"); break;
        case 'a':
            set(5, 8, "0000000000011100001101111110110111100000"); break;
        case 'b':
            set(5, 8, "1100011000111101101111011110111111000000"); break;
        case 'c':
            set(4, 8, "00000000011111001100110001110000"); break;
        case 'd':
            set(5, 8, "0001100011011111101111011110110111100000"); break;
        case 'e':
            set(5, 8, "0000000000011101101111111110000111100000"); break;
        case 'f':
            set(3, 8, "011110111110110110110000"); break;
        case 'g':
            set(5, 8, "000000000001111110111101101111000110111000000"); break;
        case 'h':
            set(5, 8, "1100011000111101101111011110111101100000"); break;
        case 'i':
            set(2, 8, "1100111111111100"); break;
        case 'j':
            set(3, 8, "011000011011011011011110000"); break;
        case 'k':
            set(5, 8, "1100011000110111111011100111101101100000"); break;
        case 'l':
            set(2, 8, "1111111111111100"); break;
        case 'm':
            set(8, 8, "0000000000000000111111101101101111011011110110111101101100000000"); break;
        case 'n':
            set(5, 8, "0000000000111101101111011110111101100000"); break;
        case 'o':
            set(5, 8, "0000000000011101101111011110110111000000"); break;
        case 'p':
            set(5, 8, "0000000000111101101111011111101100011000"); break;
        case 'q':
            set(5, 8, "0000000000011111101111011011110001100011"); break;
        case 'r':
            set(4, 8, "00000000110111111100110011000000"); break;
        case 's':
            set(4, 8, "00000000011111001111001111100000"); break;
        case 't':
            set(3, 8, "110110111110110110011000"); break;
        case 'u':
            set(5, 8, "0000000000110111101111011110110111100000"); break;
        case 'v':
            set(5, 8, "0000000000110111101101110011100010000000"); break;
        case 'w':
            set(7, 8, "00000000000000110001111010111101011011111001101100000000"); break;
        case 'x':
            set(5, 8, "0000000000110111101101110110111101100000"); break;
        case 'y':
            set(5, 8, "0000000000110111101111011011110001101110"); break;
        case 'z':
            set(5, 8, "0000000000111110011001100110001111100000"); break;
        case '0':
            set(5, 8, "0111011011110111101111011110110111000000"); break;
        case '1':
            set(3, 8, "011111011011011011011000"); break;
        case '2':
            set(5, 8, "1111000011000110111011000110001111100000"); break;
        case '3':
            set(5, 8, "1111000011000110111000011000111111000000"); break;
        case '4':
            set(5, 8, "0001100111010111001111111000110001100000"); break;
        case '5':
            set(5, 8, "1111010000111100001100011000111111000000"); break;
        case '6':
            set(5, 8, "0111011000111101101111011110110111000000"); break;
        case '7':
            set(5, 8, "1111100011001100011001100011000110000000"); break;
        case '8':
            set(5, 8, "0111011011110110111011011110110111000000"); break;
        case '9':
            set(5, 8, "0111011011110111101101111000110111000000"); break;
        case ' ':
            set(2, 8, "0000000000000000"); break;
        case ':':
            set(2, 8, "0000111100111100"); break;
        case '!':
            set(2, 8, "1111111111001100"); break;
        case '.':
            set(2, 8, "0000000000111100"); break;
        case ',':
            set(2, 8, "0000000000011110"); break;
        default:
            set(0, 0, ""); break;
        }
        
        value = c;
    }
}

LetterMap::~LetterMap()
{
    delete[] map;
}

int LetterMap::splitStringByLimit(std::string* out, std::string str, const int limit, const int letterSpacing)
{
    LetterMap letter;
    int limitCounter = 0;
    int tempLimitCounter = 0;
    int i = 0;
    std::string word = "";
    for (std::string::iterator it = str.begin(); it < str.end(); ++it) {
        letter.set(*it);
        limitCounter += letter.width + letterSpacing;
        tempLimitCounter += letter.width + letterSpacing;
        if (limitCounter <= limit - letterSpacing) {
            if (letter.value == ' ' || letter.value == '\n') {
                out[i] += word + ' ';
                word = "";
                tempLimitCounter = 0;
            }
            else {
                word += letter.value;
            }
        }

        else {
            ++i;
            limitCounter = tempLimitCounter;
            --it;
        }
    }
    return i + 1;
}

