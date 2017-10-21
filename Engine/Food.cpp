#include "Food.h"

/**
    Constructs food object at the center of the screen
*/
Food::Food()
	:
	location(Board::Grid::WIDTH/2, Board::Grid::HEIGHT/2),
	rng(std::random_device()())
{
}

/**
    Constructs food object at the input location

    @param loc
    Specifies the location where the object is to be created
*/
Food::Food(Vec2_<int> tileLocation)
	:
	location(tileLocation),
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
	Vec2_<int> gridLocation = Board::convertToGridLocation(location);
	brd.drawLargePixel({ gridLocation.x + 1,	gridLocation.y	   }, 1);
	brd.drawLargePixel({ gridLocation.x,		gridLocation.y + 1 }, 1);
	brd.drawLargePixel({ gridLocation.x + 2,	gridLocation.y + 1 }, 1);
	brd.drawLargePixel({ gridLocation.x + 1,	gridLocation.y + 2 }, 1);

}

/**
    Returns the location of the food

    @return loc
*/
Vec2_<int> Food::getLocation() const
{
	return location;
}

/**
    Resets the food's location back to the center of the screen (10, 5)
*/
void Food::reset()
{
	location = { Board::Grid::WIDTH / 2, Board::Grid::HEIGHT / 2 };
}
    
/**
    Relocates the food at a random location on the board avoiding the snake's body

    @param snek
    Snake object that needs to be avoided when placing food
*/
void Food::respawn(const Snake & snek)
{
	std::uniform_int_distribution<int> xDist(0, Board::Grid::WIDTH - 1);    //  Sets the distribution for the X location between 0 and 19
	std::uniform_int_distribution<int> yDist(0, Board::Grid::HEIGHT - 1);   //  Sets the distribtuion for the Y location between 0 and 10
                                                                            //  as the grid size is 20 * 11
	
	do {
        //  Sets the food object's location to the newly generated location
		location = { xDist(rng), yDist(rng) };
        //  Generate a new location if the current location is where the snake is
	} while (snek.isInTile(location) || snek.getNextHeadLocation() == location);

}
