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
    const int RIGHT_SIDE_OFFSET = 2;
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
    const int screenWidthLimit = GRID_WIDTH + LETTER_SPACING - RIGHT_SIDE_OFFSET - loc.x;

    if (invert) {
        drawPixelRectangle({loc.x - 2*LETTER_SPACING, loc.y - LINE_SPACING}, screenWidthLimit, LETTER_HEIGHT + 2 * LINE_SPACING, PIXEL_SPACING);
    }

    for (std::string::iterator it = input.begin(); it < input.end(); ++it) {

        PixelLocation current = loc;
        switch (*it) {            
            case '\n':
                loc.y = current.y + LETTER_HEIGHT + 2 * LINE_SPACING;
                loc.x = originalLoc.x;
                goto dontDraw;
            default:
                letterCode.set(*it);
            
        }
        
        if (letterCode.width + loc.x <= screenWidthLimit) {
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
        }

    dontDraw: {

        };

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
