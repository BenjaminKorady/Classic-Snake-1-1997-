/**
Manages the food object

@author: Benjamin Korady
@version: 1.0   11/02/2017
*/

#pragma once

#include "PixelLocation.h"
#include "Snake.h"
#include "Board.h"
#include <random>

class Food {
public:
	Food();
	Food(PixelLocation loc);
	void draw(Board &brd) const;
	PixelLocation getLocation() const;
	void respawn(const Snake & snek);
private:
	PixelLocation loc;
	std::mt19937 rng;
	
	

};