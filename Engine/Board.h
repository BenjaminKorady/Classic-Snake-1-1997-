/**
Manages the gaming board

@author: Benjamin Korady
@version: 1.1   22/10/2017
*/
#pragma once

#include "Graphics.h"
#include <string>
#include "Vec2.h"
#include <vector>

class Board {
public:
	struct LargePixel {
		static const int DRAWN_SIZE = 7;				// pixels
		static const int SPACING = 2;					// pixels
		static const int SIZE = DRAWN_SIZE + SPACING;	// pixels
	};
	struct Tile {
		static constexpr int SIZE = 3;		// large pixels
		static constexpr int SPACING = 1;	// large pixels
	};
	struct Grid {
		static constexpr int WIDTH = 20;	// tiles
		static constexpr int HEIGHT = 11;   // tiles
	};

public:
	Board(Graphics& gfx);

	void draw() const;

	bool isInsideBoard(const Vec2_<int> location) const;
	void drawString(Vec2_<int> location, std::string input, const bool invert) const;
	void drawLargePixel(const Vec2_<int>& location, int pixelSpacing = DEFAULT_PIXEL_SPACING) const;
	void drawLargePixelRectangle(const Vec2_<int>& location, const int width, const int height, int pixelSpacing = DEFAULT_PIXEL_SPACING) const;
    void clearLargePixel(const Vec2_<int>& location, int pixelSpacing = DEFAULT_PIXEL_SPACING) const;
    void clearLargePixelRectangle(const Vec2_<int>& location, const int width, const int height, int pixelSpacing = DEFAULT_PIXEL_SPACING) const;

	static int getWidth();
	static int getHeight();
	static Vec2_<int> convertToGridLocation(Vec2_<int> tileLocation);

public:
	static constexpr int DEFAULT_PIXEL_SPACING = 1;
	static constexpr int LETTER_SPACING = 1;
	static constexpr int LP_WIDTH = 83;
	static constexpr int LP_HEIGHT = 47;

private:
	Grid grid;
	static constexpr int LP_OFFSET_X = 2;
	static constexpr int LP_OFFSET_Y = 2;

private:
    Color bgColor;
	Color pxColor;
	Graphics& gfx;
};