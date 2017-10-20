/**
Manages the gaming board

@author: Benjamin Korady
@version: 1.0   11/02/2017
*/
#pragma once

#include "Graphics.h"
#include <string>
#include "Vec2.h"
#include <vector>

class Board {
public:
	class LargePixel {
	public:
		static const int DRAWN_SIZE = 7; // pixels
		static const int SPACING = 2; // pixels
		static const int SIZE = DRAWN_SIZE + SPACING; // pixels
	};
	class Tile {
	public:
		Tile() : loc(0,0) {}
		Tile(Vec2_<int> location) : loc(location) {}
		Vec2_<int> getLocation() const { return loc; }
		static constexpr int SIZE = 3;		// large pixels
		static constexpr int SPACING = 1;	// large pixels
	private:
		Vec2_<int> loc;
		/*
		// static constexpr int CELL_INC_OFFSET = CELL_SIZE + CELL_LARGE_PIXEL_OFFSET; //4
		static constexpr int CELL_SIZE = 3;
		static constexpr int CELL_LARGE_PIXEL_OFFSET = 1;
		*/
	};
	class Grid {
	public:
		Grid() {
			for (int y = 0; y < HEIGHT; ++y) {
				for (int x = 0; x < WIDTH; ++x) {
					tiles.push_back(Tile({x, y }));
				}
			}
		}
		static constexpr int WIDTH = 20;	// Tiles
		static constexpr int HEIGHT = 11;   // Tiles
		// CELLS_X
		// CELLS_Y
	private:
		std::vector<Tile> tiles;

	};

public:
	Board(Graphics& gfx);

	void draw() const;

	bool isInsideBoard(const Vec2_<int> location) const;
	void drawString(Vec2_<int> location, std::string input, const bool invert) const;
	void drawLargePixel(const Vec2_<int>& location, int pixelSpacing) const;
	void drawLargePixelRectangle(const Vec2_<int>& location, const int width, const int height, int pixelSpacing) const;
    void clearLargePixel(const Vec2_<int>& location, int pixelSpacing) const;
    void clearLargePixelRectangle(const Vec2_<int>& location, const int width, const int height, int pixelSpacing) const;

	static int getWidth();
	static int getHeight();
	static Vec2_<int> convertToGridLocation(Vec2_<int> tileLocation);

public:
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