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
	void handleKeyPressEvent(const Keyboard::Event e);	// Snake controls

	bool isInTile(const Vec2_<int>& tileLocation) const;
	Vec2_<int> getNextHeadLocation() const;
	Vec2_<int> getDirection() const;
	int getSpeed() const;
    void draw(Board& brd) const;
    bool isTurnToMove(std::chrono::steady_clock::time_point now) const;

private:
	Vec2_<int> getNextDirection() const;
public:
	static constexpr int MaxSpeed = 9;
	static constexpr int MinSpeed = 1;

private:
	static constexpr int nStartingSegments = 9;
	std::vector<Segment> segments;
	std::deque<Vec2_<int>> bufferedMoves;	// Stores changes in direction queued up from the keyboard
    Vec2_<int> direction = {DIR_ZERO};		// Current direction
	Vec2_<int> nextDirection = {DIR_ZERO};	// Direction after reading an input from the keyboard input queue

    float movePeriod = 0.375f;
	int speedLevel = 3;						// Proportional to movePeriod but doesn't have a continuous function f(speedLevel) = movePeriod

    std::chrono::steady_clock::time_point lastMoved = std::chrono::steady_clock::now(); 
	// Stores point in time when snake last moved and uses this to determine if enough time has passed 
	// for it to move again

};