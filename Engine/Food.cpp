#include "Food.h"

/**
    Constructs food object at the center of the screen
*/
Food::Food()
	:
	loc(10 * Board::CELL_INC_OFFSET + Board::LARGE_PIXEL_OFFSET, 5 * Board::CELL_INC_OFFSET + Board::LARGE_PIXEL_OFFSET),
	rng(std::random_device()())
{
}

/**
    Constructs food object at the input location

    @param loc
    Specifies the location where the object is to be created
*/
Food::Food(PixelLocation loc)
	:
	loc({ loc.x * Board::CELL_INC_OFFSET + Board::LARGE_PIXEL_OFFSET, loc.y * Board::CELL_INC_OFFSET + Board::LARGE_PIXEL_OFFSET }),
	rng(std::random_device()())
{
}

/**
    Draws the food onto the board

    @param brd
    Board object reference
*/
void Food::draw(Board &brd) const
{
	brd.drawPixel({ loc.x + 1, loc.y}, 2);
	brd.drawPixel({ loc.x, loc.y +1 }, 2);
	brd.drawPixel({ loc.x + 2, loc.y + 1 }, 2);
	brd.drawPixel({ loc.x + 1, loc.y + 2 }, 2);

}

/**
    Returns the location of the food

    @return loc
*/
PixelLocation Food::getLocation() const
{
	return loc;
}

void Food::reset()
{
    loc = { 10 * Board::CELL_INC_OFFSET + Board::LARGE_PIXEL_OFFSET, 5 * Board::CELL_INC_OFFSET + Board::LARGE_PIXEL_OFFSET };

}

    
/**
    Relocates the food at a random location on the board avoiding the snake's body

    @param snek
    Snake object that needs to be avoided when placing food
*/
void Food::respawn(const Snake & snek)
{
	std::uniform_int_distribution<int> xDist(0, Board::GRID_WIDTH / Board::CELL_INC_OFFSET - 1);    //Sets the distribution for the X location between 0 and 19
	std::uniform_int_distribution<int> yDist(0, Board::GRID_HEIGHT / Board::CELL_INC_OFFSET - 1);   //Sets the distribtuion for the Y location between 0 and 10
                                                                                                    //as the grid size is 20 * 11
	
	do {
        //Sets the food object's location to the newly generated location
		loc = { 
                xDist(rng) * Board::CELL_INC_OFFSET + Board::LARGE_PIXEL_OFFSET,   
                yDist(rng) * Board::CELL_INC_OFFSET + Board::LARGE_PIXEL_OFFSET 
              };
        //Generate a new location if the current location is where the snake is
	} while (snek.isInLocation(loc));

}
