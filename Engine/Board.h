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
    
    static constexpr int CELL_SIZE = 3;
    static constexpr int CELL_LARGE_PIXEL_OFFSET = 1;

    static constexpr int CELL_INC_OFFSET = CELL_SIZE + CELL_LARGE_PIXEL_OFFSET; 

    static constexpr int GRID_WIDTH = CELLS_X * CELL_SIZE + (CELLS_X-1) * CELL_LARGE_PIXEL_OFFSET + 2 * CELL_LARGE_PIXEL_OFFSET
                                      + 2 * CELL_LARGE_PIXEL_OFFSET; //83

    static constexpr int GRID_HEIGHT = CELLS_Y * CELL_SIZE + (CELLS_Y - 1) * CELL_LARGE_PIXEL_OFFSET + 2 * CELL_LARGE_PIXEL_OFFSET
                                       + 2 * CELL_LARGE_PIXEL_OFFSET; //47
	
    static constexpr int LARGE_PIXEL_DIMENSION = Graphics::ScreenWidth / GRID_WIDTH;	//9

    static constexpr int LARGE_PIXEL_OFFSET = 2;   
    static constexpr int unusedPixelsX = Graphics::ScreenWidth - (LARGE_PIXEL_DIMENSION) * GRID_WIDTH;   //53
	static constexpr int unusedPixelsY = Graphics::ScreenWidth - (LARGE_PIXEL_DIMENSION) * GRID_HEIGHT; //177

	static constexpr int LETTER_SPACING = 1;


private:
    Color bgColor;
	Color pxColor;
	Graphics& gfx;
};