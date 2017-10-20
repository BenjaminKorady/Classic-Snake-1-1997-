/**
Manages the gaming board

@author: Benjamin Korady
@version: 1.0   11/02/2017
*/
#pragma once

#include "Graphics.h"
#include "PixelLocation.h"
#include <string>
class Board {
public:
	Board(Graphics& gfx);
	void drawPixel(const PixelLocation& loc, int pixelSpacing) const;
    void clearPixel(const PixelLocation& loc, int pixelSpacing) const;
    void drawPixelRectangle(const PixelLocation& locIn, const int width, const int height, int pixelSpacing) const;
    void clearPixelRectangle(const PixelLocation& locIn, const int width, const int height, int pixelSpacing) const;
    void drawString(PixelLocation loc, std::string input, const bool invert) const;
	void drawBoard() const;
	bool isInsideBoard(const PixelLocation loc) const;

    //  Gaming grid is 20x11 cells
    static constexpr int CELLS_X = 20;
    static constexpr int CELLS_Y = 11;

    //  To figure out how big each cell is going to be:
    //  Screen's width needs to fit 20 cells
    //  Screen's height needs to fit 11 cells
    //  800 / 20 = 40       SCREEN_WIDTH / CELLS_X
    //  600 / 11 = 54       SCREEN_HEIGHT / CELLS_Y
    //  Pick the smaller number to make cells square and ensure they fit in both X and Y.
    //  So 40x40 px would be the maximum cell size
    //  In the classic Snake, each cell was 3x3 black pixels separated by 1 blank pixel:
    //   http://i.imgur.com/NoEEl4J.png
    static constexpr int CELL_SIZE = 3;
    static constexpr int CELL_LARGE_PIXEL_OFFSET = 1;

    //  The actual cell size will therefore be 4 pixels, so we store that in a new constant
    static constexpr int CELL_INC_OFFSET = CELL_SIZE + CELL_LARGE_PIXEL_OFFSET; //4

    //  And if the snake segments were connected, the 1x3 line of pixels inbetween them 
    //  was filled with black pixels as well:
    //    http://i.imgur.com/FEP30q6.png
    //  So the game frame on the X-axis fills 20 cells of 3x3 pixels (20x3), each separated by
    //  a single pixel (20*3 + 19*1). The frame itself is 1 pixel wide on each side 
    //  (20*3 + 19*1 + 2) and the frame is also separated from the cells by 1 pixel on each
    //  side (20*3 + 19*1 + 2 + 2) = 83
	static constexpr int GRID_WIDTH = CELLS_X * CELL_SIZE + (CELLS_X-1) * CELL_LARGE_PIXEL_OFFSET + 2 * CELL_LARGE_PIXEL_OFFSET
                                      + 2 * CELL_LARGE_PIXEL_OFFSET; //83

    //  For the grid height, the same formula is used but with 11 cells instead of 20:
    //  (11*3 + 10*1 + 2 + 2) = 47
    static constexpr int GRID_HEIGHT = CELLS_Y * CELL_SIZE + (CELLS_Y - 1) * CELL_LARGE_PIXEL_OFFSET + 2 * CELL_LARGE_PIXEL_OFFSET
                                       + 2 * CELL_LARGE_PIXEL_OFFSET; //47
	
    //  As the PC screen resolution is much larger than the old phones' resolution. The actual PC
    //  pixels are smaller to the human eye and playing on a 83x47 resolution would be nothing special.
    //  So we create a sort of "large pixel". What seems like 1 pixel on the phone, will be more pixels
    //  on the PC monitor. The largest possible value for each pixel would be:
    //  (800 / 83) which is approximately 9.64 so to round it up: 1 phone pixel = 9 PC monitor pixels
    static constexpr int LARGE_PIXEL_DIMENSION = Graphics::ScreenWidth / GRID_WIDTH;	//9

    //  If you look at the phone screen, the pixels are not right next to each other and are actually
    //  separated by a small space:
    //  http://i.imgur.com/pvGfdoS.png
    //  Here I experimented a bit and just tried what looked the best. 3 was too big of a space, 1 seemed too small
    //  So 2 pixels it was!
	static constexpr int LARGE_PIXEL_OFFSET = 2;   

    //  This means that the actual large pixel's dimension will be LARGE_PIXEL_DIMENSION - LARGE_PIXEL_OFFSET = ( 9 - 2 )
    //  7 black pixels + 2 blank (green) pixels:
    //  (7+2) * (7+2)
    //  http://i.imgur.com/zwOEIYd.png

    //  As we have rounded up from 9.64 to 9 pixels, there will be some unused pixels on the screen:
    static constexpr int unusedPixelsX = Graphics::ScreenWidth - (LARGE_PIXEL_DIMENSION) * GRID_WIDTH;   //53
	static constexpr int unusedPixelsY = Graphics::ScreenHeight - (LARGE_PIXEL_DIMENSION) * GRID_HEIGHT; //177
    //  We will use these values to place the gaming grid to the center of the screen

	static constexpr int LETTER_SPACING = 1;


private:
    Color bgColor;
	Color pxColor;
	Graphics& gfx;
};