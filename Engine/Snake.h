/**
    Handles the Snake logic

    @author Benjamin Korady
    @version 1.0    13/02/2017
*/

#pragma once

#include "Keyboard.h"
#include "Board.h"
#include <chrono>

class Snake {

public:
    Snake();
    void reset();
    void move( const Vec2_<int>& direction, Board & brd);
    void grow();
    void draw(Board& brd) const;
    Vec2_<int> getNextDirection(Keyboard& kbd);
    bool isInLocation(const Vec2_<int>& loc) const;
    Vec2_<int> getNextHeadLocation(const Vec2_<int> direction) const;
    void resetMoveBuffer();
    int getFoodEaten();
	int getSpeed() const;
	void setSpeed(int speed);
    void incFoodEaten();
    void resetFoodEaten();
    bool isTurnToMove(std::chrono::steady_clock::time_point now) const;
    void cacheDirection();

	static constexpr int MaxSpeed = 9;
	static constexpr int MinSpeed = 1;


private:

    /**
        Manages each individual segment of the snake
    */
    class Segment {
    public:
        void initSegment(const Vec2_<int>& locIn);
        void follow(const Segment& next);
        void move(const Vec2_<int>& direction, Board & brd);
        void draw(Board& brd, const Segment& next) const;

        const Vec2_<int>& getLocation() const;
		Vec2_<int>& getLocation();

		Vec2_<int> getGridLocation() const;
        bool exists = false;

    private:
        Vec2_<int> loc;
    };

private:
    //  Keeps track of how much food was eaten
    int foodEaten = 0;
    static constexpr int MAX_SEGMENTS = Board::Grid::WIDTH * Board::Grid::HEIGHT;
    Segment segments[MAX_SEGMENTS];

    //  The classic Snake starts with 9 segments
    int nSegments = 9;

    //  Used to store next move in memory even if idleLimit has not passed yet. 
    //  Allows smoother snake control
    bool moveBuffered = false;

    //Directional vector of the Snake. 0 by default (not moving)
    Vec2_<int> direction = { 0, 0 };
    Vec2_<int> lastDirection = { 0, 0 };

    float movePeriod = 0.375f;
	int speedLevel = 3;

    // 9: 5/60
    // 6: 15/60
    // 3: 22/60

    std::chrono::steady_clock::time_point lastMoved = std::chrono::steady_clock::now();


};