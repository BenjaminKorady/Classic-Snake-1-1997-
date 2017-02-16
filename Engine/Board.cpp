#include "Board.h"
#include <assert.h>
#include "LetterMap.h"
/**
    Constructs a game board object
    Initializes background color to light green and pixel color to dark green / black

    @param gfx
    Graphics processor reference
*/

Board::Board(Graphics & gfx)
	:
	gfx(gfx),
	pxColor(91, 92, 0),    // Black pixel 
    bgColor(172, 193, 0)   // Green background color
{
}

/**
    Draws a large pixel to the screen (9 pc monitor pixels = 1 phone screen pixel)
    http://i.imgur.com/RkFVcAk.png

    @param loc
    The location on the screen where the pixel is to be drawn
*/
void Board::drawPixel(const PixelLocation & loc, int pixelSpacing)
{
    
	gfx.DrawRectDim(loc.x * LARGE_PIXEL_DIMENSION + unusedPixelsX/2,     //x position + half of unused pixels to center the board horizontally
                    loc.y * LARGE_PIXEL_DIMENSION + unusedPixelsY/2,     //similarly for y to center the board veritcally
                    LARGE_PIXEL_DIMENSION - pixelSpacing,              //width of the draw pixel - the spacing. So there is a spacing inbetween pixels
                    LARGE_PIXEL_DIMENSION - pixelSpacing,              //similarly for height
                    pxColor);                                           //input pixel color
}

void Board::clearPixel(const PixelLocation & loc, int pixelSpacing)
{
    gfx.DrawRectDim(loc.x* LARGE_PIXEL_DIMENSION + unusedPixelsX / 2,  
        loc.y* LARGE_PIXEL_DIMENSION + unusedPixelsY / 2,              
        LARGE_PIXEL_DIMENSION - pixelSpacing,                          
        LARGE_PIXEL_DIMENSION - pixelSpacing,                          
        bgColor);                                                      
}

void Board::drawPixelRectangle(const PixelLocation & locIn, const int width, const int height, int pixelSpacing)
{
    PixelLocation locCopy = locIn;
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            drawPixel({ locCopy.x, locCopy.y }, pixelSpacing);
            ++locCopy.x;
        }
        locCopy.x = locIn.x;
        ++locCopy.y;
    }
}

void Board::clearPixelRectangle(const PixelLocation & locIn, const int width, const int height, int pixelSpacing)
{
    PixelLocation locCopy = locIn;
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            clearPixel({ locCopy.x, locCopy.y }, pixelSpacing);
            ++locCopy.x;
        }
        locCopy.x = locIn.x;
        ++locCopy.y;
    }
}

void Board::drawString(PixelLocation loc, std::string input, const bool invert)
{
    const int LETTER_HEIGHT = 8;
    const int RIGHT_SIDE_OFFSET = 7;
    const int PIXEL_SPACING = 1;
    const int LETTER_SPACING = 1;
    const int LINE_SPACING = 1;

    /*
        LetterMap:
                1 = drawPixel
                0 = don't drawPixel

        if invert == true
                1 = don't drawPixel
                0 = drawPixel
    */



    const PixelLocation originalLoc = loc;
    LetterMap letterCode;


    if (invert) {
        drawPixelRectangle({loc.x - 2*LETTER_SPACING, loc.y - LINE_SPACING}, GRID_WIDTH + LETTER_SPACING - RIGHT_SIDE_OFFSET, LETTER_HEIGHT + 2 * LINE_SPACING, PIXEL_SPACING);
    }

    for (std::string::iterator it = input.begin(); it < input.end(); ++it) {

        PixelLocation current = loc;
        switch (*it) {
        case 'A':
            letterCode.set(5, 8, "0111011011110111101111111110111101100000"); break;
        case 'B':
            letterCode.set(5, 8, "1111011011111101101111011110111111000000"); break;
        case 'C':
            letterCode.set(5, 8, "0111111000110001100011000110000111100000"); break;
        case 'D':
            letterCode.set(5, 8, "1111011011110111101111011110111111000000"); break;
        case 'E':
            letterCode.set(5, 8, "1111111000111101100011000110001111100000"); break;
        case 'F':
            letterCode.set(5, 8, "1111111000111101100011000110001100000000"); break;
        case 'G':
            letterCode.set(5, 8, "0111011000110001101111011110110111100000"); break;
        case 'H':
            letterCode.set(5, 8, "1101111011111111101111011110111101100000"); break;
        case 'I':
            letterCode.set(2, 8, "1111111111111100"); break;
        case 'J':
            letterCode.set(4, 8, "00110011001100110011001111100000"); break;
        case 'K':
            letterCode.set(6, 8, "110011110110111100111000111100110110110011000000"); break;
        case 'L':
            letterCode.set(4, 8, "11001100110011001100110011110000"); break;
        case 'M':
            letterCode.set(7, 8, "10000011100011111011111111111101011110001111000110000000"); break;
        case 'N':
            letterCode.set(6, 8, "100011110011111011111111110111110011110001000000"); break;
        case 'O':
            letterCode.set(6, 8, "011110110011110011110011110011110011011110000000"); break;
        case 'P':
            letterCode.set(5, 8, "1111011011110111101111110110001100000000"); break;
        case 'Q':
            letterCode.set(6, 8, "011110110011110011110011110011110111011110000011000000"); break;
        case 'R':
            letterCode.set(5, 8, "1111011011110111101111110110101101100000"); break;
        case 'S':
            letterCode.set(4, 8, "01111100110001100011001111100000"); break;
        case 'T':
            letterCode.set(6, 8, "111111001100001100001100001100001100001100000000"); break;
        case 'U':
            letterCode.set(5, 8, "1101111011110111101111011110110111000000"); break;
        case 'V':
            letterCode.set(6, 8, "110011110011110011011110011110001100001100000000"); break;
        case 'W':
            letterCode.set(7, 8, "11000111100011110101111111110111110011111001101100000000"); break;
        case 'X':
            letterCode.set(6, 8, "110011110011011110001100011110110011110011000000"); break;
        case 'Y':
            letterCode.set(6, 8, "110011110011011110001100001100001100001100000000"); break;
        case 'Z':
            letterCode.set(5, 8, "1111100011001110111011100110001111100000"); break;
        case 'a':
            letterCode.set(5, 8, "0000000000011100001101111110110111100000"); break;
        case 'b':
            letterCode.set(5, 8, "1100011000111101101111011110111111000000"); break;
        case 'c':
            letterCode.set(4, 8, "00000000011111001100110001110000"); break;
        case 'd':
            letterCode.set(5, 8, "0001100011011111101111011110110111100000"); break;
        case 'e':
            letterCode.set(5, 8, "0000000000011101101111111110000111100000"); break;
        case 'f':
            letterCode.set(3, 8, "011110111110110110110000"); break;
        case 'g':
            letterCode.set(5, 8, "000000000001111110111101101111000110111000000"); break;
        case 'h':
            letterCode.set(5, 8, "1100011000111101101111011110111101100000"); break;
        case 'i':
            letterCode.set(2, 8, "1100111111111100"); break;
        case 'j':
            letterCode.set(3, 8, "011000011011011011011110000"); break;
        case 'k':
            letterCode.set(5, 8, "1100011000110111111011100111101101100000"); break;
        case 'l':
            letterCode.set(2, 8, "1111111111111100"); break;
        case 'm':
            letterCode.set(8, 8, "0000000000000000111111101101101111011011110110111101101100000000"); break;
        case 'n':
            letterCode.set(5, 8, "0000000000111101101111011110111101100000"); break;
        case 'o':
            letterCode.set(5, 8, "0000000000011101101111011110110111000000"); break;
        case 'p':
            letterCode.set(5, 8, "0000000000111101101111011111101100011000"); break;
        case 'q':
            letterCode.set(5, 8, "0000000000011111101111011011110001100011"); break;
        case 'r':
            letterCode.set(4, 8, "00000000110111111100110011000000"); break;
        case 's':
            letterCode.set(4, 8, "00000000011111001111001111100000"); break;
        case 't':
            letterCode.set(3, 8, "110110111110110110011000"); break;
        case 'u':
            letterCode.set(5, 8, "0000000000110111101111011110110111100000"); break;
        case 'v':
            letterCode.set(5, 8, "0000000000110111101101110011100010000000"); break;
        case 'w':
            letterCode.set(7, 8, "00000000000000110001111010111101011011111001101100000000"); break;
        case 'x':
            letterCode.set(5, 8, "0000000000110111101101110110111101100000"); break;
        case 'y':
            letterCode.set(5, 8, "0000000000110111101111011011110001101110"); break;
        case 'z':
            letterCode.set(5, 8, "0000000000111110011001100110001111100000"); break;
        case '0':
            letterCode.set(5, 8, "0111011011110111101111011110110111000000"); break;
        case '1':
            letterCode.set(3, 8, "011111011011011011011000"); break;
        case '2':
            letterCode.set(5, 8, "1111000011000110111011000110001111100000"); break;
        case '3':
            letterCode.set(5, 8, "1111000011000110111000011000111111000000"); break;
        case '4':
            letterCode.set(5, 8, "0001100111010111001111111000110001100000"); break;
        case '5':
            letterCode.set(5, 8, "1111010000111100001100011000111111000000"); break;
        case '6':
            letterCode.set(5, 8, "0111011000111101101111011110110111000000"); break;
        case '7':
            letterCode.set(5, 8, "1111100011001100011001100011000110000000"); break;
        case '8':
            letterCode.set(5, 8, "0111011011110110111011011110110111000000"); break;
        case '9':
            letterCode.set(5, 8, "0111011011110111101101111000110111000000"); break;
        case ' ':
            loc.x = loc.x + 4;
            goto dontDraw;
        case '\n':
            loc.y = current.y + LETTER_HEIGHT + 2*LINE_SPACING;
            loc.x = originalLoc.x;
            goto dontDraw;
        case ':':
            letterCode.set(1, 8, "00010010"); break;
        case '!':
            letterCode.set(2, 8, "1111111111001100"); break;
        }
        
        int i = 0;



        for (int y = 0; y < LETTER_HEIGHT; ++y) {
            for (int x = 0; x < letterCode.width; ++x) {
                if (letterCode.map[i++]) {
                    invert ? clearPixel(current, PIXEL_SPACING) : drawPixel(current, PIXEL_SPACING);
                }
                current.x++;
            }
            current.x = loc.x;
            current.y++;
        }
        
        loc.x += letterCode.width + LETTER_SPACING;

        dontDraw:;

        current.y = loc.y;
    
    }

}

/**
    Draws the game board and background fill

*/
void Board::drawBoard()
{

    //Draws grid frame
	for (int y = 0; y < GRID_HEIGHT; ++y) {
		for (int x = 0; x < GRID_WIDTH; ++x) {
			PixelLocation loc = { x, y };
			if (x == 0 || y == 0 || x == GRID_WIDTH-1 || y == GRID_HEIGHT-1)
				drawPixel(loc, 0);
		}
	}
}

/**
    Checks if input location is inside the game board

    @param loc
    The input location to check against the game board
    @return bool 
*/

bool Board::isInsideBoard(const PixelLocation loc) const
{
	return
		loc.x >= 0 &&
		loc.x < GRID_WIDTH - 1 &&
		loc.y >= 0 &&
		loc.y < GRID_HEIGHT - 1;
	
}
