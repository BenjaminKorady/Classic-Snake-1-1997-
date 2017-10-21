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
private:

	/**
	Manages each individual segment of the snake
	*/
	class Segment {
	public:
		Segment(const Vec2_<int>& tileLocation);

		void follow(const Segment& next);
		void move(const Vec2_<int>& direction, Board & brd);

		const Vec2_<int>& getLocation() const;
		Vec2_<int>& getLocation();
		void draw(Board& brd) const;

	private:
		Vec2_<int> location;	// tile
	};

public:
    Snake();
    void reset();
    void move(Board & brd);
    void grow();
	void setSpeed(int speed);
	void handleKeyboardPressEvent(const Keyboard::Event e);

	bool isInLocation(const Vec2_<int>& loc) const;
	Vec2_<int> getNextHeadLocation() const;
	Vec2_<int> getDirection() const;
	int getFoodEaten() const;
	int getSpeed() const;
    void draw(Board& brd) const;

    void incFoodEaten();
    void resetFoodEaten();
    bool isTurnToMove(std::chrono::steady_clock::time_point now) const;
    void cacheDirection();

private:
	Vec2_<int> getNextDirection() const;
public:
	static constexpr int MaxSpeed = 9;
	static constexpr int MinSpeed = 1;

private:
    int foodEaten = 0;
	static constexpr int nStartingSegments = 9;
    static constexpr int MAX_SEGMENTS = Board::Grid::WIDTH * Board::Grid::HEIGHT;
	std::vector<Segment> segments;

    bool moveBuffered = false;     //  Used to store next move in memory even if idleLimit has not passed yet. 
								   //  Allows smoother snake control
	std::deque<Vec2_<int>> bufferedMoves;
    Vec2_<int> direction = {DIR_ZERO};
	Vec2_<int> nextDirection = {DIR_ZERO};
    Vec2_<int> lastDirection = {DIR_ZERO};

    float movePeriod = 0.375f;
	int speedLevel = 3;

    std::chrono::steady_clock::time_point lastMoved = std::chrono::steady_clock::now();


};