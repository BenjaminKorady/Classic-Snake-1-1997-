/**
    Handles the Snake logic

    @author Benjamin Korady
    @version 1.0    13/02/2017
*/

#pragma once

#include "PixelLocation.h"
#include "Keyboard.h"
#include "Board.h"
#include "FrameTimer.h"

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
    void resetMoveBuffer();
    int getFoodEaten();
    void incFoodEaten();
    void resetFoodEaten();
    void updateSpeed();
    bool isTurnToMove(std::chrono::steady_clock::time_point now) const;
    int speedLevel = 3;


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
        bool exists = false;

    private:
        PixelLocation loc;
    };

private:
    //  Keeps track of how much food was eaten
    int foodEaten = 0;
    static constexpr int MAX_SEGMENTS = Board::CELLS_X * Board::CELLS_Y;
    Segment segments[MAX_SEGMENTS];

    //  The classic Snake starts with 9 segments
    int nSegments = 9;

    //  Used to store next move in memory even if idleLimit has not passed yet. 
    //  Allows smoother snake control
    bool moveBuffered = false;

    //Directional vector of the Snake. 0 by default (not moving)
    PixelLocation direction = { 0, 0 };

    float movePeriod = 0.5f;
    std::chrono::steady_clock::time_point lastMoved = std::chrono::steady_clock::now();


};