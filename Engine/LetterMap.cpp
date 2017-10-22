#include "LetterMap.h"
#include <algorithm>
#include <assert.h>

/**
	Constructs a LetterMap object
*/
LetterMap::LetterMap()
{
}

/**
	Initializes the object's width and map values to the input values

	@param widthIn
	@param mapIn
*/
void LetterMap::set(int widthIn, unsigned __int64 mapIn)
{
    width = widthIn;
	map = mapIn;
}

/**
	Initializes the LetterMap based on input char 

	@param c The character which the LetterMap should represent
*/
void LetterMap::set(char c)
{
    switch (c) {
    case 'A':
        set(5, 0b0111011011110111101111111110111101100000); break;		
    case 'B':
        set(5, 0b1111011011111101101111011110111111000000); break;
    case 'C':
        set(5, 0b0111111000110001100011000110000111100000); break;
    case 'D':
        set(5, 0b1111011011110111101111011110111111000000); break;
    case 'E':
        set(5, 0b1111111000111101100011000110001111100000); break;
    case 'F':
        set(5, 0b1111111000111101100011000110001100000000); break;
    case 'G':
        set(5, 0b0111011000110001101111011110110111100000); break;
    case 'H':
        set(5, 0b1101111011111111101111011110111101100000); break;
    case 'I':
        set(2, 0b1111111111111100); break;
    case 'J':
        set(4, 0b00110011001100110011001111100000); break;
    case 'K':
        set(6, 0b110011110110111100111000111100110110110011000000); break;
    case 'L':
        set(4, 0b11001100110011001100110011110000); break;
    case 'M':
        set(7, 0b10000011100011111011111111111101011110001111000110000000); break;
    case 'N':
        set(6, 0b100011110011111011111111110111110011110001000000); break;
    case 'O':
        set(6, 0b011110110011110011110011110011110011011110000000); break;
    case 'P':
        set(5, 0b1111011011110111101111110110001100000000); break;
    case 'Q':
        set(6, 0b011110110011110011110011110011110111011110000011000000); break;
    case 'R':
        set(5, 0b1111011011110111101111110110101101100000); break;
    case 'S':
        set(4, 0b01111100110001100011001111100000); break;
    case 'T':
        set(6, 0b111111001100001100001100001100001100001100000000); break;
    case 'U':
        set(5, 0b1101111011110111101111011110110111000000); break;
    case 'V':
        set(6, 0b110011110011110011011110011110001100001100000000); break;
    case 'W':
        set(7, 0b11000111100011110101111111110111110011111001101100000000); break;
    case 'X':
        set(6, 0b110011110011011110001100011110110011110011000000); break;
    case 'Y':
        set(6, 0b110011110011011110001100001100001100001100000000); break;
    case 'Z':
        set(5, 0b1111100011001110111011100110001111100000); break;
    case 'a':
        set(5, 0b0000000000011100001101111110110111100000); break;
    case 'b':
        set(5, 0b1100011000111101101111011110111111000000); break;
    case 'c':
        set(4, 0b00000000011111001100110001110000); break;
    case 'd':
        set(5, 0b0001100011011111101111011110110111100000); break;
    case 'e':
        set(5, 0b0000000000011101101111111110000111100000); break;
    case 'f':
        set(3, 0b011110111110110110110000); break;
    case 'g':
        set(5, 0b000000000001111110111101101111000110111000000); break;
    case 'h':
        set(5, 0b1100011000111101101111011110111101100000); break;
    case 'i':
        set(2, 0b1100111111111100); break;
    case 'j':
        set(3, 0b011000011011011011011110000); break;
    case 'k':
        set(5, 0b1100011000110111111011100111101101100000); break;
    case 'l':
        set(2, 0b1111111111111100); break;
    case 'm':
        set(8, 0b0000000000000000111111101101101111011011110110111101101100000000); break;
    case 'n':
        set(5, 0b0000000000111101101111011110111101100000); break;
    case 'o':
        set(5, 0b0000000000011101101111011110110111000000); break;
    case 'p':
        set(5, 0b0000000000111101101111011111101100011000); break;
    case 'q':
        set(5, 0b0000000000011111101111011011110001100011); break;
    case 'r':
        set(4, 0b00000000110111111100110011000000); break;
    case 's':
        set(4, 0b00000000011111001111001111100000); break;
    case 't':
        set(3, 0b110110111110110110011000); break;
    case 'u':
        set(5, 0b0000000000110111101111011110110111100000); break;
    case 'v':
        set(5, 0b0000000000110111101101110011100010000000); break;
    case 'w':
        set(7, 0b00000000000000110001111010111101011011111001101100000000); break;
    case 'x':
        set(5, 0b0000000000110111101101110110111101100000); break;
    case 'y':
        set(5, 0b0000000000110111101111011011110001101110); break;
    case 'z':
        set(5, 0b0000000000111110011001100110001111100000); break;
    case '0':
        set(5, 0b0111011011110111101111011110110111000000); break;
    case '1':
        set(3, 0b011111011011011011011000); break;
    case '2':
        set(5, 0b1111000011000110111011000110001111100000); break;
    case '3':
        set(5, 0b1111000011000110111000011000111111000000); break;
    case '4':
        set(5, 0b0001100111010111001111111000110001100000); break;
    case '5':
        set(5, 0b1111010000111100001100011000111111000000); break;
    case '6':
        set(5, 0b0111011000111101101111011110110111000000); break;
    case '7':
        set(5, 0b1111100011001100011001100011000110000000); break;
    case '8':
        set(5, 0b0111011011110110111011011110110111000000); break;
    case '9':
        set(5, 0b0111011011110111101101111000110111000000); break;
    case ' ':
        set(2, 0b0000000000000000); break;
    case ':':
        set(2, 0b0000111100111100); break;
    case '!':
        set(2, 0b1111111111001100); break;
    case '.':
        set(2, 0b0000000000111100); break;
    case ',':
        set(2, 0b0000000000011110); break;
    default:
        set(0, 0b0); break;
    }      
    value = c;
	assert(width <= MAX_WIDTH);
}

/**
	Splits the string into shorter strings so that each smaller string fits inside the given limit.
	(Fits within the screen width for example)

	@param str String which is to be split
	@param limit The limit which bounds the maximum string length
	@param letterSpacing The spacing between each letters to take into consideration when calculating the limit
	@return strings vector of strings where each string is a portion of the input string, which fits inside the given limit
*/
std::vector<std::string> LetterMap::splitStringByLimit(std::string str, const int limit, const int letterSpacing) {
	std::vector<std::string> lines;
    LetterMap letter;
    int lineLength = 0;		
    int wordLength = 0;	 
    std::string word = "";
	std::string line = "";

    for (std::string::iterator it = str.begin(); it < str.end(); ++it) {
        letter.set(*it);									// Set so that we can get the letter's width
        lineLength += letter.width + letterSpacing;		// Add that + spacing to our current counter of how many pixels we're already using
        wordLength += letter.width + letterSpacing;
        if (lineLength <= limit - letterSpacing) {		// Current loaded string still fits inside the limit
            if (letter.value == ' ' || letter.value == '\n') {	// End of the word or line
				line += word + ' ';							// Only store whole words into the line
                word = "";									// (We don't want words split onto two separate lines like th
                wordLength = 0;								// is
            }
            else {
                word += letter.value;		// Load the current char into the word
            }
        }
        else {											// Line no longer fits within the limit
			lines.push_back(line);	
			line = "";
            lineLength = wordLength;		// Start the next line with the current word's length already loaded
            --it;
        }
    }
	lines.push_back(line);
    return lines;
}


/**
	Returns the width of the input string (in Large Pixels)

	@param str
	@param letterSpacing the spacing between each letter of the string (in Large Pixels)
	@return width

*/
int LetterMap::getStringWidth(std::string str, const int letterSpacing)
{
	LetterMap letter;
	int width = 0;
	int maxWidth = 0;

	for (std::string::iterator it = str.begin(); it < str.end(); ++it) {
		letter.set(*it);
		width += letter.width + letterSpacing;
		if (letter.value == '\n') {
			maxWidth = std::max(maxWidth, width);	// Going onto next line, always remember the highest width among the checked lines
			width = 0;
		}
	}

	maxWidth = std::max(maxWidth, width);	
	return maxWidth;
}

