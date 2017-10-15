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
private:
	class Item {
	public:
		enum class Name {
			Continue,
			LastView,
			NewGame,
			TopScore,
			Instructions,
			Level,
			None
		};
	public:
		Item() = default;
		Item(Name name)
			:
			name(name)
		{}
		Item(Name name, int positionOnScreen, bool highlighted = false)
			:
			name(name), positionOnScreen(positionOnScreen), highlighted(highlighted)
		{}
		Name getName() const {
			return name;
		}
		bool isHighlighted() const {
			return highlighted;
		}
		void highlight() {
			highlighted = true;
		}
		int getPositionOnScreen() const {
			return positionOnScreen;
		}

		//operators
		void operator=(Item& rhs) {
			name = rhs.name;
			positionOnScreen = rhs.positionOnScreen;
			highlighted = rhs.highlighted;
		}
	private:
		Name name;
		int positionOnScreen;
		bool highlighted;
	};


public:
    Menu(Board &brd, Snake &snek, Food &nom, Keyboard &kbd);

	std::string getHighlightedItem();
	bool optionSelected();
	void reset();
	void returnToMenu();
	void drawTopScore(int topScore);
	void drawLastView(const Snake& snekCache, const Food& nomCache);
	void drawInstructions();
	void drawLevel(Snake& snek);
	void goToTop();
    void draw();
	void navigate();


private:
	void drawItemName(Item itemIn, int position, bool selected) const;
	std::string getItemName(const Item& itemIn) const;
    void drawSideBar(int height);
	void drawLevelBar(int barNum, bool fill);
	int selectedItemNumber();

private:
	static constexpr int shownItems = 3;
private:
	std::vector<Item> items;
	Item::Name selectedItemName = Item::Name::None;
	int topItemIndex = 0;
	int highlightedItemNumber = 0;
    bool buttonPressed = false;
    bool confirmSelection = false;
    int scrollBarPos = 0;

    Keyboard &kbd;
    Food nom;
    Snake snek;
    Board brd;

};