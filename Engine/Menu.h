#pragma once

#include "Board.h"
#include <string>
#include "Keyboard.h"
#include "Snake.h"
#include "Food.h"
#include "LetterMap.h"
#include <math.h>
#include <vector>

class Menu {
public:
	enum class Item {
		Continue,
		LastView,
		NewGame,
		TopScore,
		Instructions,
		Level,
		None
	};

public:
    Menu(Board &brd, Snake &snek, Food &nom, Keyboard &kbd);

	Item getSelection();
	bool hasItem(Item itemIn) const;

	void addItem(Item item);
	void removeItem(Item item);
	void returnToMenu();
	void returnToMenuOnReturnKeyPress();
	void drawTopScore(int topScore);
	void drawLastView(const Snake& snekCache, const Food& nomCache);
	void drawInstructions();
	void drawLevel(Snake& snek);
    void draw();
	void navigate();
	void navigateInstructions();
	void navigateLevel(Snake& snek);


private:
	void drawItemName(Item itemIn, int position, bool selected) const;
	void drawItem(Item itemIn) const;
	std::string drawItemString(const Item& itemIn) const;
    void drawScrollbar(int height);
	void drawLevelBar(int barNum, bool fill);
	int getHighlightedItemIndex();
	void confirmSelection();

private:
	std::vector<Item> items;
	Item selectedItem = Item::None;
	int topItemIndex = 0;
	int highlightedItemNumber = 0;
    bool buttonPressed = false;
    int scrollbarPos = 0;

    Keyboard& kbd;
    Food& nom;
    Snake& snek;
    Board& brd;

// General values
private:
	static constexpr int TOP_LEFT_TEXT_X = 2;
	static constexpr int TOP_LEFT_TEXT_Y = 2;

// Level specific values
private:
	const int MAX_LEVEL = 9;

// Instructions specific values
private:
	static constexpr int SHOWN_ITEMS = 3;
	static constexpr int SCROLLBAR_HEIGHT = 7;
	const std::string instructions = "Make the snake grow longer by directing it to the food. Use the arrow keys or W, A, S, and D. You cannot stop the snake or make it go backwards. Try not to hit the walls or the tail.\n";
	const std::vector<std::string> instructionsLines = LetterMap::splitStringByLimit(instructions, MAX_PIXELS_ON_SCREEN_WIDTH, LETTER_SPACING);
	static constexpr int MAX_LINES_ON_SCREEN = 4;
	static constexpr int MAX_PIXELS_ON_SCREEN_WIDTH = 77;
	static constexpr int LETTER_SPACING = 1;
	static constexpr int LINE_START_X = 2;
	static constexpr int LINE_START_Y = 2;
	static constexpr int LINE_Y_SPACING = 10;

	static constexpr int RIGHT_SIDE_OFFSET = 2;
	const int MAX_INSTRUCTIONS_SCROLLBAR_POS = (int)instructionsLines.size() -1;




};