#include "Snake.h"
#include <assert.h>


/**
    Constructs the snake object with its head at location 0, 0
    Initializes all of its segments
*/
Snake::Snake()
{
    PixelLocation loc(0 + Board::LARGE_PIXEL_OFFSET, 10 * Board::CELL_INC_OFFSET + Board::LARGE_PIXEL_OFFSET);
    for (int i = nSegments - 1; i >= 0; --i) {
        segments[i].initSegment(loc);
        loc = { loc.x + Board::CELL_INC_OFFSET, loc.y };
    }
}

void Snake::reset()
{
    PixelLocation loc(0 + Board::LARGE_PIXEL_OFFSET, 10 * Board::CELL_INC_OFFSET + Board::LARGE_PIXEL_OFFSET);
    for (int i = nSegments - 1; i >= 0; --i) {
        segments[i].initSegment(loc);
        loc = { loc.x + Board::CELL_INC_OFFSET, loc.y };
    }
    foodEaten = 0;
    nSegments = 9;
    direction = { 0, 0 };
    moveBuffered = false;
}

/**
    Moves the snake in the direction of its input directional vector

    @param direction directional vector stating where the snake is to move
    @param brd Board object reference on which the snake is to move
*/
void Snake::move(const PixelLocation & direction, Board & brd)
{
     for (int i = nSegments - 1; i > 0; --i) {
         segments[i].follow(segments[i - 1]);
     }

     segments[0].move(direction, brd);

     idleFor = 0;
}

/**
    Grows the snake by 1 segment.
*/
void Snake::grow()
{
	PixelLocation lastSegmentLoc = segments[nSegments - 1].getLocation();
	if (nSegments < MAX_SEGMENTS) {
		++nSegments;
	}
	segments[nSegments - 1].initSegment(lastSegmentLoc);	
}

/**
    Returns the location where the snake is about to be after its next move

    @param direction directional vector stating where the snake is to move
    @return The next position of the snake's head
*/
PixelLocation Snake::getNextHeadLocation(const PixelLocation direction) const
{
	PixelLocation l(segments[0].getLocation());
	l = l+(direction*Board::CELL_INC_OFFSET);
	return l;
}

/**
    Increments idleFor
*/
void Snake::incIdleFor() {
    ++idleFor;
}

/**
    Resets moveBuffer
*/
void Snake::resetMoveBuffer()
{
    moveBuffered = false;
}

int Snake::getFoodEaten()
{
    return foodEaten;
}

void Snake::incFoodEaten()
{
    foodEaten++;
}

void Snake::resetFoodEaten()
{
    foodEaten = 0;
}

int Snake::getSpeed()
{
    return speedLevel;
}

/**
    States whether the snake can move (Has enough required frames passed for it to move?)
    The required frames idle are based on the snake's movement speed;

    @return is it the snake's turn to move
*/
bool Snake::isTurnToMove() const
{
    return idleFor>=idleLimit;
}

int Snake::getIdleLimit() const
{
    return idleLimit;
}

/**
    Draws all of the snake's segments to the board

    @param board object for the snake to be drawn to
*/
void Snake::draw(Board & brd) const {
	for (int i = nSegments-1; i >= 0; --i) {
		segments[i].draw(brd, segments[i-1]);
	}
}
/**
    Listens for keyboard input and changes the snake's directional vector based on keys pressed
    Controls: Arrow Keys or WASD

    @param kbd Keyboard processor
    @return direction where the snake is about to move
*/
PixelLocation Snake::getNextDirection(Keyboard & kbd)
{
    if(!moveBuffered) {
        if (kbd.KeyIsPressed(VK_UP) || kbd.KeyIsPressed(0x57)) { // W
            if (!(direction.x == 0 && direction.y == 1) && !moveBuffered) {
                direction = { 0, -1 };
                moveBuffered = true;
            }
        }
        else if (kbd.KeyIsPressed(VK_LEFT) || kbd.KeyIsPressed(0x41)) { // A
            if (!(direction.x == 1 && direction.y == 0) && !moveBuffered) {
                direction = { -1, 0 };
                moveBuffered = true;
            }

        }
        else if (kbd.KeyIsPressed(VK_DOWN) || kbd.KeyIsPressed(0x53)) { // S
            if (!(direction.x == 0 && direction.y == -1) && !moveBuffered) {
                direction = { 0, 1 };
                moveBuffered = true;
            }

        }
        else if (kbd.KeyIsPressed(VK_RIGHT) || kbd.KeyIsPressed(0x44)) { // D
            if (!(direction.x == -1 && direction.y == 0) && !moveBuffered) {
                direction = { 1, 0 };
                moveBuffered = true;
            }
        }
    }

    return direction;
}

/**
    States whether the input location collides with any of the snake's body segments

    @param loc Input location
    @return bool
*/
bool Snake::isInLocation(const PixelLocation & loc) const
{
	for (int i = 0; i < nSegments; ++i) {
		if (segments[i].getLocation() == loc)
			return true;
	}
	return false;
}

/**
    Initializes a segment by changing its "exists" variable to true and setting its location to the input location
    
    @param locIn states where the segment is to be located
*/
void Snake::Segment::initSegment(const PixelLocation & locIn)
{
	loc = locIn;
	exists = true;
}

/**
    Makes current segment follow the next segment (main logic behind how the snake moves)

    @param next reference to the next segment of the snake
*/
void Snake::Segment::follow(const Segment & next)
{
	loc = next.loc;
}

/**
    Moves the segment

    @param direction directional vector stating where the segment is to move to
    @param brd Board object reference on which the snake moves
*/
void Snake::Segment::move(const PixelLocation & direction, Board & brd)
{
	assert(abs(direction.x) + abs(direction.y) == 1);
	loc = loc + direction*Board::CELL_INC_OFFSET;
}

/**
    Draws the segment to the board as well as the spacing between the segments

    @param brd Board reference on which the segment is to be drawn
    @param next a reference to the next segment connected to the current segment
*/
void Snake::Segment::draw(Board & brd, const Segment& next) const
{
    const int pixelSpacing = 1;
    //  Draws the 3x3 large pixel segment
    for (int i = 0; i < Board::CELL_SIZE; ++i) {
		for (int j = 0; j < Board::CELL_SIZE; ++j) {
			brd.drawPixel({loc.x+i, loc.y+j}, pixelSpacing);
		}
	}

    //  Draws the spacing between the segments
	if (next.exists) {
		for (int j = 0; j < Board::CELL_SIZE; ++j) {
            //  next segment is to the right
			if(next.loc.x - loc.x == Board::CELL_INC_OFFSET)
				brd.drawPixel({ loc.x + Board::CELL_SIZE, loc.y + j }, pixelSpacing);
            //  next segment is to the left
			else if(next.loc.x - loc.x == - Board::CELL_INC_OFFSET)
				brd.drawPixel({ loc.x  - Board::CELL_LARGE_PIXEL_OFFSET, loc.y + j }, pixelSpacing);
            //  next segment is below 
			if (next.loc.y - loc.y == Board::CELL_INC_OFFSET)
				brd.drawPixel({ loc.x + j, loc.y + Board::CELL_SIZE }, pixelSpacing);
            //  next segment is above
			else if (next.loc.y - loc.y == - Board::CELL_INC_OFFSET)
				brd.drawPixel({ loc.x + j, loc.y - Board::CELL_LARGE_PIXEL_OFFSET }, pixelSpacing);
		}
	}

}

/**
    Segment location getter

    @retun location of segment
*/

PixelLocation Snake::Segment::getLocation() const
{
	return loc;
}





