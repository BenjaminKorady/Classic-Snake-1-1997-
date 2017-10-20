/**
Manages the food object

@author: Benjamin Korady
@version: 1.0   11/02/2017
*/

#pragma once

#include "Snake.h"
#include "Board.h"
#include <random>

class Food {
public:
	Food();
	Food(Vec2_<int> tileLocation);
	void draw(Board &brd) const;
	Vec2_<int> getLocation() const;
    void reset();
	void respawn(const Snake & snek);

private:
	Vec2_<int> tileLocation;
	Vec2_<int> gridLocation = Board::convertToGridLocation(tileLocation);
	std::mt19937 rng;
	
	

};