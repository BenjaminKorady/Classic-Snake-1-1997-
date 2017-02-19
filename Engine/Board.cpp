/**
Constructs a game board object
Initializes background color to light green and pixel color to dark green / black

@param gfx
Graphics processor reference
*/
#include "Board.h"
#include <assert.h>
#include "LetterMap.h"

Board::Board(Graphics & gfx)
	:
	gfx(gfx),
	pxColor(91, 92, 0),    // Black pixel color
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
	gfx.DrawRectDim(loc.x * LARGE_PIXEL_DIMENSION + unusedPixelsX/2,    //  x position + half of unused pixels to center the board horizontally
                    loc.y * LARGE_PIXEL_DIMENSION + unusedPixelsY/2,    //  similarly for y to center the board veritcally
                    LARGE_PIXEL_DIMENSION - pixelSpacing,               //  width of the draw pixel - the spacing. So there is a spacing inbetween pixels
                    LARGE_PIXEL_DIMENSION - pixelSpacing,               //  similarly for height
                    pxColor);                                           //  input pixel color
}

/**
    Draws a green / background color pixel

    @param loc
    The location on the screen where the pixel is to be drawn
    @param pixelSpacing
    The spacing (in monitor pixels) between each large pixel

*/
void Board::clearPixel(const PixelLocation & loc, int pixelSpacing)
{
    gfx.DrawRectDim(loc.x* LARGE_PIXEL_DIMENSION + unusedPixelsX / 2,   //  x position + half of unused pixels to center the board horizontally
        loc.y* LARGE_PIXEL_DIMENSION + unusedPixelsY / 2,               //  similarly for y to center the board veritcally
        LARGE_PIXEL_DIMENSION - pixelSpacing,                           //  width of the draw pixel - the spacing. So there is a spacing inbetween pixels
        LARGE_PIXEL_DIMENSION - pixelSpacing,                           //  similarly for height
        bgColor);                                                       //  input pixel color
}

/**
    Draws a rectangle of large pixels

    @param locIn The location on the screen where the pixel is to be drawn (top left corner of the rectangle)
    @param width The width of the rectangle to be drawn
    @param height The height of the rectangle to be drawn
    @pixelSpacing The spacing (in monitor pixels) between each large pixel

*/
void Board::drawPixelRectangle(const PixelLocation & locIn, const int width, const int height, int pixelSpacing)
{
    PixelLocation locCopy = locIn;                                      //  Create a local copy of the input location
    for (int j = 0; j < height; ++j) {                                  //  Loop through the rectangle width*height
        for (int i = 0; i < width; ++i) {                               
            drawPixel(locCopy, pixelSpacing);                           //  Draw a pixel at locCopy
            ++locCopy.x;                                                //  move locCopy by 1 to the right 
        }
        locCopy.x = locIn.x;                                            //  Set the location copy's x back to the original value (return back to the leftmost pixel of the rectangle
        ++locCopy.y;                                                    //  move locCopy 1 pixel lower
    }
}

/**
    Clears a rectangle of large pixels

    @param locIn The location on the screen where the pixel is to be drawn (top left corner of the rectangle)
    @param width The width of the rectangle to be drawn
    @param height The height of the rectangle to be drawn
    @pixelSpacing The spacing (in monitor pixels) between each large pixel
*/
void Board::clearPixelRectangle(const PixelLocation & locIn, const int width, const int height, int pixelSpacing)
{
    PixelLocation locCopy = locIn;                                      //  Create a local copy of the input location
    for (int j = 0; j < height; ++j) {                                  //  Loop through the rectangle width*height
        for (int i = 0; i < width; ++i) {
            clearPixel(locCopy, pixelSpacing);                          //  Clear a pixel at locCopy
            ++locCopy.x;                                                //  move locCopy by 1 to the right 
        }
        locCopy.x = locIn.x;                                            //  Set the location copy's x back to the original value (return back to the leftmost pixel of the rectangle
        ++locCopy.y;                                                    //  move locCopy 1 pixel lower
    }
}

/**
    Draws a string to the screen

    @param loc The location where the string is to be drawn
    @param input The string that is to be drawn
    @param invert invert the pixel colors
*/
void Board::drawString(PixelLocation loc, std::string input, const bool invert)
{
    const int LETTER_HEIGHT = 8;
    const int RIGHT_SIDE_OFFSET = 4;
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
    const int screenWidthLimit = GRID_WIDTH + LETTER_SPACING - RIGHT_SIDE_OFFSET;

    if (invert) {
        drawPixelRectangle({loc.x - 2*LETTER_SPACING, loc.y - LINE_SPACING}, screenWidthLimit, LETTER_HEIGHT + 2 * LINE_SPACING, PIXEL_SPACING);
    }

    for (std::string::iterator it = input.begin(); it < input.end(); ++it) {

        PixelLocation current = loc;

        letterCode.set(*it);

        if (letterCode.value == '\n') {
            loc.y = current.y + LETTER_HEIGHT + 2 * LINE_SPACING;
            loc.x = originalLoc.x;
            goto dontDraw;
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
    const int PIXEL_SPACING = 1;
    //Draws grid frame
	for (int y = 0; y < GRID_HEIGHT; ++y) {
		for (int x = 0; x < GRID_WIDTH; ++x) {
			PixelLocation loc = { x, y };
			if (x == 0 || y == 0 || x == GRID_WIDTH-1 || y == GRID_HEIGHT-1)
				drawPixel(loc, PIXEL_SPACING);
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
