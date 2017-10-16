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
	void reset();
	void returnToMenu();
	void drawTopScore(int topScore);
	void drawLastView(const Snake& snekCache, const Food& nomCache);
	void drawInstructions();
	void drawLevel(Snake& snek);
    void draw();
	void navigate();


private:
	void drawItem(Item itemIn, int position, bool selected) const;
	std::string getItem(const Item& itemIn) const;
    void drawSideBar(int height);
	void drawLevelBar(int barNum, bool fill);
	int selectedItemNumber();
	void confirmSelection();

private:
	static constexpr int shownItems = 3;
private:
	std::vector<Item> items;
	Item selectedItem = Item::None;
	int topItemIndex = 0;
	int highlightedItemNumber = 0;
    bool buttonPressed = false;
    int scrollBarPos = 0;

    Keyboard &kbd;
    Food nom;
    Snake snek;
    Board brd;

};