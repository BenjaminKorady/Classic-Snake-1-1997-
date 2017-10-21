#include "Snake.h"
#include <assert.h>
#include <iterator>

/**
    Constructs the snake object and calls reset() to initialize it to default values
*/
Snake::Snake()
{
	reset();
}

/**
	Initializes snake to default values, resets its segments, buffered moves, and direction
*/
void Snake::reset()
{ 
	segments.clear();
    Vec2_<int> loc(nStartingSegments-1, Board::Grid::HEIGHT - 1);	// Initialize from the right-most segment (head)
	for (int i = 0; i < nStartingSegments; ++i) {
		segments.push_back(Segment({ loc.x--, loc.y }));
	}
    direction = {DIR_ZERO};
	bufferedMoves.clear();
}

/**
    Moves the snake in the next direction in queue

    @param brd Board object reference on which the snake is to move
*/
void Snake::move(Board & brd)
{
	// First all the segments, except the head, follow the segment in front of them...
	for (int i = (int)segments.size() - 1; i > 0; --i) {
		segments[i].follow(segments[i - 1]);
	}

	Vec2_<int> dir = getNextDirection();	
	if (!bufferedMoves.empty()) {
		bufferedMoves.pop_front();	// Pop an element if a direction from the queue was used
	}								// If queue is empty, uses last used direction to move

	segments[0].move(dir, brd);
	lastMoved = std::chrono::steady_clock::now();	// Timestamp when the snake last moved. The time of the next move will be based on this
}

/**
    Grows the snake by 1 segment at the tail.
*/
void Snake::grow()
{
	Vec2_<int> lastSegmentLoc = segments.back().getLocation();	
	segments.push_back(lastSegmentLoc);
}

/**
    Returns the location where the snake is going to be after its next move

    @return The next position of the snake's head
*/
Vec2_<int> Snake::getNextHeadLocation() const
{
	Vec2_<int> dir = getNextDirection();
	Vec2_<int> l(segments.front().getLocation());
	l = l+(dir);
	return l;
}

/**
	Returns snake's current direction
	
	@return direction
*/
Vec2_<int> Snake::getDirection() const
{
	return direction;
}

/**
	Returns snake's speed level (1-9)

	@return speed level
*/
int Snake::getSpeed() const
{
	return speedLevel;
}

/**
	Sets the snake's movePeriod based on input speedLevel. 

	@param speedLevel: Expected values are 1-9, uses default 3 otherwise
*/
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
    States whether or not the snake can move (Has enough time passed since the last movement?)
    The required frames idle are based on the snake's movement speed;

    @return bool is it the snake's turn to move
*/
bool Snake::isTurnToMove(std::chrono::steady_clock::time_point now) const
{
    std::chrono::duration<float> diff = now - lastMoved;
    return diff.count() >= movePeriod;
}

/**
	Returns the next direction which is going to be used

	@return direction
*/
Vec2_<int> Snake::getNextDirection() const
{
	Vec2_<int> dir;
	if (!bufferedMoves.empty()) {
		dir = bufferedMoves.front();	// If queue is not empty, read from the queue
	}
	else {
		dir = direction;				// Otherwise read the last used direction
	}

	return dir;
}

/**
    Draws all of the snake's segments and the spacing between them to the board 

    @param board object for the snake to be drawn to
*/
void Snake::draw(Board & brd) const {
	for (int i = (int)segments.size() - 1; i >= 0; --i) {
		segments[i].draw(brd);

		if (i != 0) {	// If not drawing the head, draw spacing between segments (Head has no "next" segment)
			const Vec2_<int> nextLoc = segments[i-1].getLocation();

			const Vec2_<int> currentLoc = segments[i].getLocation();
			const Vec2_<int> currentGridLocation = Board::convertToGridLocation(currentLoc);

			for (int j = 0; j < Board::Tile::SIZE; ++j) {
				//  next segment is to the right
				if (nextLoc.x - currentLoc.x == 1)
					brd.drawLargePixel({ currentGridLocation.x + Board::Tile::SIZE, currentGridLocation.y + j }); // Draw vertical line to the right of the segment
				//  next segment is to the left
				else if (nextLoc.x - currentLoc.x == -1)
					brd.drawLargePixel({ currentGridLocation.x - 1, currentGridLocation.y + j });	// Draw vertical line to the left of the segment
				//  next segment is below 
				else if (nextLoc.y - currentLoc.y == 1)
					brd.drawLargePixel({ currentGridLocation.x + j, currentGridLocation.y + Board::Tile::SIZE });	// Horizontal line underneath
				//  next segment is above
				else if (nextLoc.y - currentLoc.y == -1)
					brd.drawLargePixel({ currentGridLocation.x + j , currentGridLocation.y - 1 });	// Horizontal line above
			}
		}
	}
}

/**
    Listens for keyboard input and loads a direction into the queue based on keys pressed
    Controls: Arrow Keys or WASD

    @param e Key press event
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

	if (newDirection != -direction) {	// Only use new input if snake isn't trying to walk into itself 
		direction = newDirection;		// Otherwise use old direction
	}

	if (bufferedMoves.empty() || (direction != -bufferedMoves.back() && direction != bufferedMoves.back())) {	// Make sure two consequent moves aren't in the same or opposite direction of each other
		bufferedMoves.push_back(direction);																		// i.e. only allow 90 degree turns one after another
	}
}

/**
    States whether or not the input location collides with any of the snake's body segments

    @param tileLocation Input location in Tile units
    @return bool
*/
bool Snake::isInTile(const Vec2_<int> & tileLocation) const
{
	for (int i = 0; i < segments.size(); ++i) {
		if (tileLocation == segments[i].getLocation())
			return true;
	}
	return false;
}

/**
    Constructs a new Segment at input location
    
    @param tileLocation states where the segment is to be located
*/
Snake::Segment::Segment(const Vec2_<int>& tileLocation)
	:
	location(tileLocation)
{
}

/**
    Makes current segment follow the segment in front of it (main logic behind how the snake moves)

    @param nextSegment reference to the next segment of the snake
*/
void Snake::Segment::follow(const Segment & nextSegment)
{
	location = nextSegment.location;
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
    Draws the segment to the board

    @param brd Board reference on which the segment is to be drawn
*/
void Snake::Segment::draw(Board & brd) const
{
	// A single segment occupies a 1x1 tile space. We need to convert that to 3x3 large pixel space so we can draw each individual large pixel
	Vec2_<int> gridLocation = Board::convertToGridLocation(location);

    //  Draws the 3x3 large pixel segment
	for (int i = 0; i < Board::Tile::SIZE; ++i) {
		for (int j = 0; j <  Board::Tile::SIZE; ++j) {
			brd.drawLargePixel({gridLocation.x+i, gridLocation.y+j});
		}
	}
}

/**
    const segment location getter

    @return const reference location of segment
*/

const Vec2_<int>& Snake::Segment::getLocation() const
{
	return location;
}

/**
	segment location getter

	@return reference location of segment
*/

Vec2_<int>& Snake::Segment::getLocation()
{
	return location;
}





