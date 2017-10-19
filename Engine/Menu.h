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
	void reset();
	void returnToMenu();
	void drawTopScore(int topScore);
	void drawLastView(const Snake& snekCache, const Food& nomCache);
	void drawInstructions();
	void drawLevel(Snake& snek);
    void draw();
	void navigate();
	void navigateInstructions();


private:
	void drawItemName(Item itemIn, int position, bool selected) const;
	void drawItem(Item itemIn) const;
	std::string drawItemString(const Item& itemIn) const;
    void drawScrollbar(int height);
	void drawLevelBar(int barNum, bool fill);
	int getHighlightedItemIndex();
	void confirmSelection();

private:
	static constexpr int shownItems = 3;
	const std::string instructions = "Make the snake grow longer by directing it to the food. Use the arrow keys or W, A, S, and D. You cannot stop the snake or make it go backwards. Try not to hit the walls or the tail.\n";
private:
	std::vector<Item> items;
	Item selectedItem = Item::None;
	int topItemIndex = 0;
	int highlightedItemNumber = 0;
    bool buttonPressed = false;
    int scrollbarPos = 0;


    Keyboard &kbd;
    Food nom;
    Snake snek;
    Board brd;



};