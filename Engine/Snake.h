/**
    Handles the controllable Snake

    @author Benjamin Korady
    @version 1.0    13/02/2017
*/

#pragma once

#include "PixelLocation.h"
#include "Keyboard.h"
#include "Board.h"

class Snake {

public:
    Snake();
    void reset();
    void move( const PixelLocation& direction, Board & brd);
    void grow();
    void draw(Board& brd) const;
    PixelLocation getNextDirection(Keyboard& kbd);
    bool isInLocation(const PixelLocation& loc) const;
    PixelLocation getNextHeadLocation(const PixelLocation direction) const;
    void incIdleFor();
    void resetMoveBuffer();
    int getFoodEaten();
    void incFoodEaten();
    void resetFoodEaten();
    int getSpeed();
    bool isTurnToMove() const;
    int getIdleLimit() const;

private:

    /**
        Manages each individual segment of the snake
    */
    class Segment {
    public:
        void initSegment(const PixelLocation& locIn);
        void follow(const Segment& next);
        void move(const PixelLocation& direction, Board & brd);
        void draw(Board& brd, const Segment& next) const;

        PixelLocation getLocation() const;
        //  As we are not working with dynamic memory. We create all the initial segments with a default value of
        //  exists as false. When we initialize the segment, we change that value to true
        bool exists = false;

    private:
        PixelLocation loc;
    };

private:
    //  Keeps track of how much food was eaten
    int foodEaten = 0;
    int speedLevel = 3;
    static constexpr int MAX_SEGMENTS = Board::CELLS_X * Board::CELLS_Y;
    Segment segments[MAX_SEGMENTS];

    //  The classic Snake starts with 9 segments
    int nSegments = 9;

    //  Used to store next move in memory even if idleLimit has not passed yet. 
    //  Allows smoother snake control
    bool moveBuffered = false;

    //  Keeps track of how many frames the snake has been idle for
    int idleFor = 0;

    //  The amount of frames that have to pass before the snake can move
    int idleLimit = 20;

    //Directional vector of the Snake. 0 by default (not moving)
    PixelLocation direction = { 0, 0 };

};