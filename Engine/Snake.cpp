#include "Snake.h"
#include <assert.h>
#include <iterator>

/**
    Constructs the snake object with its head at location 0, 0
    Initializes all of its segments
*/
Snake::Snake()
{
	reset();
}

void Snake::reset()
{ 
	segments.clear();
    Vec2_<int> loc(nStartingSegments-1, Board::Grid::HEIGHT - 1);
	for (int i = 0; i < nStartingSegments; ++i) {
		segments.push_back(Segment({ loc.x--, loc.y }));
	}
    direction = { 0, 0 };
	bufferedMoves.clear();
}

/**
    Moves the snake in the direction of its input directional vector

    @param direction directional vector stating where the snake is to move
    @param brd Board object reference on which the snake is to move
*/
void Snake::move(Board & brd)
{
	for (int i = (int)segments.size() - 1; i > 0; --i) {
		segments[i].follow(segments[i - 1]);
	}
	Vec2_<int> dir = getNextDirection();

	if (!bufferedMoves.empty()) {
		bufferedMoves.pop_front();
	}

	segments[0].move(dir, brd);
	lastMoved = std::chrono::steady_clock::now();
}

/**
    Grows the snake by 1 segment.
*/
void Snake::grow()
{
	Vec2_<int> lastSegmentLoc = segments.back().getLocation();
	segments.push_back(lastSegmentLoc);
}

/**
    Returns the location where the snake is about to be after its next move

    @param direction directional vector stating where the snake is to move
    @return The next position of the snake's head
*/
Vec2_<int> Snake::getNextHeadLocation() const
{
	Vec2_<int> dir = getNextDirection();
	Vec2_<int> l(segments.front().getLocation());
	l = l+(dir);
	return l;
}

Vec2_<int> Snake::getDirection() const
{
	return direction;
}

int Snake::getSpeed() const
{
	return speedLevel;
}

void Snake::setSpeed(int speedLevelIn)
{
    switch (speedLevelIn) {
    case 1:
        movePeriod = 45.0 / 60.0; break;
    case 2:
        movePeriod = 30.0 / 60.0; break;
    case 3:
        movePeriod = 22.0 / 60.0; break;
    case 4:
        movePeriod = 19.0 / 60; break;
    case 5: 
        movePeriod = 17.5 / 60; break;
    case 6:
        movePeriod = 16.0 / 60.0; break;
    case 7:
        movePeriod = 12.0 / 60.0; break;
    case 8:
        movePeriod = 8.0 / 60.0; break;
    case 9:
        movePeriod = 5.0 / 60.0; break;
    default:
        movePeriod = 22.0 / 60.0; 
		speedLevel = 3;
		return;
    }
	speedLevel = speedLevelIn;

}


/**
    States whether the snake can move (Has enough required frames passed for it to move?)
    The required frames idle are based on the snake's movement speed;

    @return is it the snake's turn to move
*/
bool Snake::isTurnToMove(std::chrono::steady_clock::time_point now) const
{
    std::chrono::duration<float> diff = now - lastMoved;
    return diff.count() >= movePeriod;
}

Vec2_<int> Snake::getNextDirection() const
{
	Vec2_<int> dir;
	if (!bufferedMoves.empty()) {
		dir = bufferedMoves.front();
	}
	else {
		dir = direction;
	}

	return dir;
}

/**
    Draws all of the snake's segments to the board

    @param board object for the snake to be drawn to
*/
void Snake::draw(Board & brd) const {
	for (int i = (int)segments.size() - 1; i >= 0; --i) {
		segments[i].draw(brd);

		if (i != 0) {
			const Vec2_<int> nextLoc = segments[i-1].getLocation();
			const Vec2_<int> currentLoc = segments[i].getLocation();
			const Vec2_<int> currentGridLocation = Board::convertToGridLocation(currentLoc);
			for (int j = 0; j < Board::Tile::SIZE; ++j) {
				//  next segment is to the right
				if (nextLoc.x - currentLoc.x == 1)
					brd.drawLargePixel({ currentGridLocation.x + Board::Tile::SIZE, currentGridLocation.y + j });
				//  next segment is to the left
				else if (nextLoc.x - currentLoc.x == -1)
					brd.drawLargePixel({ currentGridLocation.x - 1, currentGridLocation.y + j });
				//  next segment is below 
				else if (nextLoc.y - currentLoc.y == 1)
					brd.drawLargePixel({ currentGridLocation.x + j, currentGridLocation.y + Board::Tile::SIZE });
				//  next segment is above
				else if (nextLoc.y - currentLoc.y == -1)
					brd.drawLargePixel({ currentGridLocation.x + j , currentGridLocation.y - 1 });
			}
		}
	}
	

}
/**
    Listens for keyboard input and changes the snake's directional vector based on keys pressed
    Controls: Arrow Keys or WASD

    @param kbd Keyboard processor
    @return direction where the snake is about to move
*/
void Snake::handleKeyPressEvent(const Keyboard::Event e)
{
	assert(e.IsPress());

	Vec2_<int> newDirection;

	if (e.GetCode() == (VK_UP) || e.GetCode() == ('W')) {
		newDirection = {DIR_UP};		
	}
	else if (e.GetCode() == (VK_LEFT) || e.GetCode() == ('A')) {
		newDirection = {DIR_LEFT};
	}
	else if (e.GetCode() == (VK_DOWN) || e.GetCode() == ('S')) {
		newDirection = {DIR_DOWN};
	}
	else if (e.GetCode() == (VK_RIGHT) || e.GetCode() == ('D')) {
		newDirection = {DIR_RIGHT};
	}

	if (newDirection != -direction) {
		direction = newDirection;
	}

	if (bufferedMoves.empty() || (direction != -bufferedMoves.back() && direction != bufferedMoves.back())) {
		bufferedMoves.push_back(direction);
	}
	
}

/**
    States whether the input location collides with any of the snake's body segments

    @param loc Input location
    @return bool
*/
bool Snake::isInTile(const Vec2_<int> & loc) const
{
	for (int i = 0; i < segments.size(); ++i) {
		if (loc == segments[i].getLocation())
			return true;
	}
	return false;
}

/**
    Initializes a segment by changing its "exists" variable to true and setting its location to the input location
    
    @param locIn states where the segment is to be located
*/
Snake::Segment::Segment(const Vec2_<int>& tileLocation)
	:
	location(tileLocation)
{
}

/**
    Makes current segment follow the next segment (main logic behind how the snake moves)

    @param next reference to the next segment of the snake
*/
void Snake::Segment::follow(const Segment & next)
{
	location = next.location;
}

/**
    Moves the segment

    @param direction directional vector stating where the segment is to move to
    @param brd Board object reference on which the snake moves
*/
void Snake::Segment::move(const Vec2_<int> & direction, Board & brd)
{
	assert(abs(direction.x) + abs(direction.y) == 1);
	location += direction;
}

/**
    Draws the segment to the board as well as the spacing between the segments

    @param brd Board reference on which the segment is to be drawn
    @param next a reference to the next segment connected to the current segment
*/
void Snake::Segment::draw(Board & brd) const
{
	Vec2_<int> gridLocation = Board::convertToGridLocation(location);

    //  Draws the 3x3 large pixel segment
	for (int i = 0; i < Board::Tile::SIZE; ++i) {
		for (int j = 0; j <  Board::Tile::SIZE; ++j) {
			brd.drawLargePixel({gridLocation.x+i, gridLocation.y+j});
		}
	}

}

/**
    Segment location getter

    @retun location of segment
*/

const Vec2_<int>& Snake::Segment::getLocation() const
{
	return location;
}

Vec2_<int>& Snake::Segment::getLocation()
{
	return location;
}





