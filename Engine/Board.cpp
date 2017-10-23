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
	grid(),
	pxColor(91, 92, 0),    // Black pixel color
    bgColor(172, 193, 0)   // Green background color
{
}

/**
    Draws a large pixel to the screen (9 pc monitor pixels = 1 phone screen pixel, including offset)
    http://i.imgur.com/RkFVcAk.png

    @param loc Location in Large Pixel units
	@param pixelSpacing Optional spacing between pixels (defaults to 1)
    The location on the screen where the pixel is to be drawn
*/
void Board::drawLargePixel(const Vec2_<int> & loc, int pixelSpacing) const
{
	assert(loc.x >= 0);
	assert(loc.x < LP_WIDTH + LP_OFFSET_X);
	assert(loc.y >= 0);
	assert(loc.y < LP_HEIGHT + LP_OFFSET_Y);

	const int unusedPixelsX = Graphics::ScreenWidth - getWidth();
	const int unusedPixelsY = Graphics::ScreenHeight - getHeight();
	gfx.DrawRectDim(loc.x * LargePixel::SIZE + unusedPixelsX/2,    //  x position + half of unused pixels to center the board horizontally
                    loc.y * LargePixel::SIZE + unusedPixelsY/2,    //  similarly for y to center the board veritcally
                    LargePixel::SIZE - pixelSpacing,               //  width of the draw pixel - the spacing. So there is a spacing inbetween pixels
                    LargePixel::SIZE - pixelSpacing,               //  similarly for height
                    pxColor);                                      //  input pixel color
}

/**
    Draws a green / background color pixel

    @param loc
    The location on the screen where the pixel is to be drawn
    @param pixelSpacing
    The spacing - optional (in monitor pixels) between each large pixel (defaults to 1)

*/
void Board::clearLargePixel(const Vec2_<int> & loc, int pixelSpacing)  const
{
	const int unusedPixelsX = Graphics::ScreenWidth - getWidth();
	const int unusedPixelsY = Graphics::ScreenHeight - getHeight();
    gfx.DrawRectDim(loc.x* LargePixel::SIZE + unusedPixelsX / 2,   //  x position + half of unused pixels to center the board horizontally
        loc.y* LargePixel::SIZE + unusedPixelsY / 2,               //  similarly for y to center the board veritcally
        LargePixel::SIZE - pixelSpacing,                           //  width of the draw pixel - the spacing. So there is a spacing inbetween pixels
        LargePixel::SIZE - pixelSpacing,                           //  similarly for height
        bgColor);                                                  //  input pixel color
}

/**
    Draws a rectangle of large pixels

    @param locIn The location on the screen where the pixel is to be drawn (top left corner of the rectangle)
    @param width The width of the rectangle to be drawn
    @param height The height of the rectangle to be drawn
    @param pixelSpacing The spacing - optional (in monitor pixels) between each large pixel (defaults to 1)

*/
void Board::drawLargePixelRectangle(const Vec2_<int> & locIn, const int width, const int height, int pixelSpacing)  const
{
    Vec2_<int> locCopy = locIn;                                      //  Create a local copy of the input location
    for (int j = 0; j < height; ++j) {                                  //  Loop through the rectangle width*height
        for (int i = 0; i < width; ++i) {                               
            drawLargePixel(locCopy, pixelSpacing);                           //  Draw a pixel at locCopy
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
    @param pixelSpacing The spacing - optional (in monitor pixels) between each large pixel (defaults to 1)
*/
void Board::clearLargePixelRectangle(const Vec2_<int> & locIn, const int width, const int height, int pixelSpacing)  const
{
    Vec2_<int> locCopy = locIn;                                      //  Create a local copy of the input location
    for (int j = 0; j < height; ++j) {                                  //  Loop through the rectangle width*height
        for (int i = 0; i < width; ++i) {
            clearLargePixel(locCopy, pixelSpacing);                          //  Clear a pixel at locCopy
            ++locCopy.x;                                                //  move locCopy by 1 to the right 
        }
        locCopy.x = locIn.x;                                            //  Set the location copy's x back to the original value (return back to the leftmost pixel of the rectangle
        ++locCopy.y;                                                    //  move locCopy 1 pixel lower
    }
}

/**
	Returns width of the game board (in monitor pixels)

	@return int Width (in monitor pixels)
*/
int Board::getWidth()
{
	return LP_WIDTH * LargePixel::SIZE;
}

/**
	Returns height of the game board (in monitor pixels)

	@return int Height (in monitor pixels)
*/
int Board::getHeight()
{
	return LP_HEIGHT * LargePixel::SIZE;
}

/**
	Converts a location of a tile (of the grid) to its corresponding top-left corner Large Pixel of the grid (game board)

	@param tileLocation The location of the tile in grid-coordinates (tile coordinates)
	@return gridLocation Location in large pixels on the grid
*/
Vec2_<int> Board::convertToGridLocation(Vec2_<int> tileLocation)
{
	return Vec2_<int>( {
		tileLocation.x*(Tile::SIZE + Tile::SPACING) + LP_OFFSET_X,
		tileLocation.y*(Tile::SIZE + Tile::SPACING) + LP_OFFSET_Y
	});
}

/**
    Draws a string to the screen

    @param loc The location where the string is to be drawn
    @param input The string that is to be drawn
    @param invert invert the pixel colors
*/
void Board::drawString(Vec2_<int> loc, std::string input, const bool invert) const
{
    static constexpr int RIGHT_SIDE_OFFSET = 4;
	static constexpr int LINE_SPACING = 1;
    const Vec2_<int> originalLoc = loc;                                          //  Store the original input location for later use
    LetterMap letterCode;                                                           //  A LetterMap object to keep track of where to draw pixels (See LetterMap class for more information)
	static constexpr int screenWidthLimit = LP_WIDTH + LETTER_SPACING - RIGHT_SIDE_OFFSET;   //  Boundary of where it is possible to draw

    //  Draws a black background if the string is to be inverted
    if (invert) {
        drawLargePixelRectangle({loc.x - 2*LETTER_SPACING, loc.y - LINE_SPACING}, screenWidthLimit, LetterMap::height + 2 * LINE_SPACING);
    }

    for (std::string::iterator it = input.begin(); it < input.end(); ++it) {        //  Iterate through each character of the string
        Vec2_<int> current = loc;                                                //  Keep track of the location where pixels are drawn with "current" and "loc".
        letterCode.set(*it);                                                        //  Maps the current char as LetterMap

        //  Don't draw anything if the input char is \n. Instead shift the current location one line lower and back to the leftmost side
        if (letterCode.value == '\n') {                                               
            loc.y = current.y + LetterMap::height + 2 * LINE_SPACING;
            loc.x = originalLoc.x;
            goto dontDraw;                                                          //  Skips the drawing part and moves to the next char
        }
        
        //  Draws the letter based on its mapping stored in LetterMap letter code
        if (letterCode.width + loc.x <= screenWidthLimit) {                         //  Checks if the letter is to be drawn within the screen boundaries
            int i = 0;
			unsigned __int64 currentBit = 0x8000000000000000;	//Start at the left-most-bit (this is equivalent to 0b100000........00 (63 zeros)
			currentBit = currentBit >> ((LetterMap::MAX_WIDTH - letterCode.width)*LetterMap::height);
            for (int y = 0; y < LetterMap::height; ++y) {                               //  Iterate through the letter's height
                for (int x = 0; x < letterCode.width; ++x) {                        //  Iterate through the letter's width
                    //  the "map" member variable is an __int64 value where each bit represents a pixel:
                    //  1 = draw a pixel 
                    //  0 = don't draw 
                    if (letterCode.map & currentBit) {   // the checked bit position is = 1 -> Draw bit                                   
                        //  If the string is to be inverted, clearLargePixel. Otherwise, drawLargePixel (Since if it was inverted, there is a black background drawn. Therefore, just clear from the background)
                        invert ? clearLargePixel(current) : drawLargePixel(current);    
                    }
					currentBit = currentBit >> 0b1;
                    current.x++;    //  Shift current location to the right by 1 pixel
                }
                current.x = loc.x;  //  Set current location back to the original leftmost location of the letter's pixels
                current.y++;        //  Shift current location 1 pixel lower
            }
            loc.x += letterCode.width + LETTER_SPACING;     //  When drawing the letter is finished, shift the location's x to where the next letter is to be drawn. So current letter's width + spacing between letters
        }
    dontDraw:   //  Label, program jumps here if no letter is to be drawn

        current.y = loc.y;
    }

}

/**
    Draws the game board and background fill
*/
void Board::draw()  const
{
    const int PIXEL_SPACING = 1;
    //Draws board frame
	for (int y = 0; y < LP_HEIGHT; ++y) {
		for (int x = 0; x < LP_WIDTH; ++x) {
			Vec2_<int> loc = { x, y };
			if (x == 0 || y == 0 || x == LP_WIDTH-1 || y == LP_HEIGHT-1)
				drawLargePixel(loc, PIXEL_SPACING);
		}
	}
}

/**
    Checks if input location is inside the game board

    @param loc
    The input location to check against the game board
    @return bool 
*/

bool Board::isInsideBoard(const Vec2_<int> loc) const
{
	return
		loc.x >= 0 &&
		loc.x < Grid::WIDTH &&
		loc.y >= 0 &&
		loc.y < Grid::HEIGHT;	
}
