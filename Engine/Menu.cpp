#include "Menu.h"
#include <assert.h>
#include <string>
#include <iterator>
#include <vector>

/**
	Constructs menu class and pushes the 4 main menu items into the menu items vector

	@param brd 
	@param snek
	@param nom
	@param kbd
*/
Menu::Menu(Board &brd, Snake &snek, Food &nom, Keyboard &kbd)
    :
    brd(brd),
    snek(snek),
    nom(nom),
    kbd(kbd)
{
	items.push_back(Item::NewGame);
	items.push_back(Item::TopScore);
	items.push_back(Item::Instructions);
	items.push_back(Item::Level);
}

/**
	Draws the menu to the board
*/
void Menu::draw() const
{
    assert(highlightedItemNumber >= 0 && highlightedItemNumber < SHOWN_ITEMS);

	for (int i = 0; i < SHOWN_ITEMS; ++i) {
		int index = (i + topItemIndex) % (int)items.size();	// Draw 3 items starting from the current top item. Loop around the menu to the first item if we have reached past the last item
		drawItemName(items[index], i, highlightedItemNumber == i);
	}

	drawConfirmButton("Select");

	int scrollbarPos = ((brd.LP_HEIGHT - SCROLLBAR_HEIGHT) / (int)items.size()) * ((getHighlightedItemIndex()) % ((int)items.size()));
    drawScrollbar(scrollbarPos);	// Draw scrollbar at position relative to the index of highlighted item
									// i.e., index 0 -> draw at top, index [last] -> draw at bottom
}			

/**
	Checks whether or not an item is already in the menu

	@param itemIn an item to look for
	@return bool
*/
bool Menu::hasItem(Item itemIn) const
{
	for (Item i : items) {
		if (i == itemIn) {
			return true;
		}
	}
	return false;
}

/**
	Draws the name of the menu item onto the screen (e.g. "New game")

	@param itemIn item to draw the name of
	@param position position of item, either 0, 1, or 2 (top, middle, bottom)
	@param isHighlighted highlighted item has inverted colors to signify it is the current selection
*/
void Menu::drawItemName(Item itemIn, int position, bool isHighlighted) const
{
	assert(position >= 0);
	assert(position < SHOWN_ITEMS);

	Vec2_<int> pos[SHOWN_ITEMS];
	for (int i = 0; i < SHOWN_ITEMS; ++i) {
		pos[i] = { LINE_START_X, LINE_START_Y + i*LINE_Y_SPACING };	// Draws menu items at pos[0], pos[1], pos[2]. Each separated by defined LINE_Y_SPACING
	}

    brd.drawString(pos[position], getItemString(itemIn), isHighlighted);
}

/**
	Handles keyboard input to navigate through the menu
*/
void Menu::navigate()
{ 
    while (!kbd.KeyIsEmpty()) {
        const Keyboard::Event e = kbd.ReadKey();
		if (e.IsPress()) {
			if (e.GetCode() == (VK_UP) || e.GetCode() == ('W')) {
				if (highlightedItemNumber != 0) {		// If scrolling through the current view of the menu, only change the highlighted item number (0, 1, or 2)
					--highlightedItemNumber;			// Otherwise the whole menu view window has to shift (the top item swaps to a different item)
				}										// And wraps around if a boundary has been reached
				else {
					topItemIndex = topItemIndex == 0 ? (int)items.size() - 1 : topItemIndex - 1;
				}
			}
			if (e.GetCode() == (VK_DOWN) || e.GetCode() == ('S')) {
				if (highlightedItemNumber < SHOWN_ITEMS - 1) {
					++highlightedItemNumber;
				}
				else {
					topItemIndex = (topItemIndex + 1) % (int)items.size();
				}
			}
			if (e.GetCode() == (VK_RETURN)) {
				confirmSelection();
				return;
			}
		}
    }   
}

/**
	Handles keyboard input to navigate through the instructions menu item
	This function only changes the position of the scrollbar, which is later used in the draw function
	to determine which line of the instructions is to be drawn
*/
void Menu::navigateInstructions()
{
	while (!kbd.KeyIsEmpty()) {
		const Keyboard::Event e = kbd.ReadKey();
		if (e.IsPress()) {

			if (e.GetCode() == (VK_UP) || e.GetCode() == ('W')) {
				if (scrollbarPos != 0) {
					--scrollbarPos;
				}
			}

			else if (e.GetCode() == VK_DOWN || e.GetCode() == ('S')) {
				if(scrollbarPos != MAX_INSTRUCTIONS_SCROLLBAR_POS) {
					++scrollbarPos;
				}
			}

			else if (e.GetCode() == VK_RETURN) {
				scrollbarPos = 0;
				returnToMenu();
			}
		}
	}

}

/**
	Handles keyboard input to navigate through the Level menu item
	Allows to change the difficulty / snake speed

	@param snek Snake of which the speed is to be altered
*/
void Menu::navigateLevel(Snake & snek)
{
	while (!kbd.KeyIsEmpty()) {
		const Keyboard::Event e = kbd.ReadKey();
		if (e.IsPress()) {
			int snekSpeed = snek.getSpeed();
			if (e.GetCode() == (VK_UP) || e.GetCode() == ('W')) {
				if (snekSpeed != Snake::MaxSpeed) {
					snek.setSpeed(++snekSpeed);
				}
			}

			else if (e.GetCode() == (VK_DOWN) || e.GetCode() == ('S')) {
				if (snekSpeed != Snake::MinSpeed) {
					snek.setSpeed(--snekSpeed);
				}
			}
			else if (e.GetCode() == (VK_RETURN) || e.GetCode() == (VK_ESCAPE)) {
				returnToMenu();
			}
		}
	}
}

/**
	Draws the scrollbar on the right side of the screen while in the main menu and Instructions

	@param height Height in pixels at which the top side of the scrollbar is to be drawn
*/
void Menu::drawScrollbar(int height) const
{
    constexpr int RIGHT_OFFSET_X = 1;
	constexpr int TOP_OFFSET_Y = 1;

    Vec2_<int> scrollbarPos = { brd.LP_WIDTH - RIGHT_OFFSET_X, height };

	{			
		// RECTANGLE					// Location: X												// Width	// Height
		brd.drawLargePixelRectangle(	{ scrollbarPos.x, TOP_OFFSET_Y },							1,			brd.LP_HEIGHT - 1	 );
		brd.clearLargePixelRectangle(	{ scrollbarPos.x, scrollbarPos.y},							1,			SCROLLBAR_HEIGHT	 );
		brd.drawLargePixelRectangle(	{ scrollbarPos.x + 2, scrollbarPos.y + 1 },					1,			SCROLLBAR_HEIGHT - 1 );
		// LARGE PIXEL					// Location													--------	---------
		brd.drawLargePixel(				{ scrollbarPos.x, scrollbarPos.y }							);
		brd.drawLargePixel(				{ scrollbarPos.x + 1, scrollbarPos.y }						);
		brd.drawLargePixel(				{ scrollbarPos.x + 1, scrollbarPos.y + SCROLLBAR_HEIGHT }	);
		brd.drawLargePixel(				{ scrollbarPos.x, scrollbarPos.y + SCROLLBAR_HEIGHT }		);
	}
}

/**
	Returns a string storing the name of the input item

	@param itemIn 
	@return std::string stringified name of the enum class Menu::Item
*/
std::string Menu::getItemString(const Item & itemIn) const
{
	switch (itemIn) {
	case Item::Continue: return "Continue"; 
	case Item::LastView: return "Last view"; 
	case Item::NewGame: return "New game"; 
	case Item::TopScore: return "Top score"; 
	case Item::Instructions: return "Instructions";
	case Item::Level: return "Level";
	default: return "";
	}
}

/**
	
*/
Menu::Item Menu::getSelectedItem() const
{
	return selectedItem;
}

void Menu::addItem(Item item)
{
	assert(!hasItem(item));
	items.insert(items.begin(), item);
}

void Menu::removeItem(Item item)
{
	assert(hasItem(item));
	items.erase(std::remove(items.begin(), items.end(), item), items.end());
}

void Menu::returnToMenu()
{
	selectedItem = Item::None;
	topItemIndex = 0;
	highlightedItemNumber = 0;
}

void Menu::returnToMenuOnReturnKeyPress()
{
	while (!kbd.KeyIsEmpty()) {
		const Keyboard::Event e = kbd.ReadKey();
		if (e.IsPress()) {
			if (e.GetCode() == VK_RETURN) {
				returnToMenu();
			}
		}
	}
}

void Menu::drawTopScore(int topScore) const
{
    brd.drawString({ LINE_START_X, LINE_START_Y }, "Top score:\n " + std::to_string(topScore), false);
}

void Menu::drawLastView(const Snake& snekCache, const Food& nomCache) const
{
    brd.draw();
    snekCache.draw(brd);
    nomCache.draw(brd);
}

void Menu::drawInstructions() const
{
	for (int i = 0; i < MAX_LINES_ON_SCREEN; ++i) {
		if (scrollbarPos + i <= MAX_INSTRUCTIONS_SCROLLBAR_POS) {
			brd.drawString({ LINE_START_X, LINE_START_Y + LINE_Y_SPACING*i }, instructionsLines[scrollbarPos + i], false);
		}
	}

	int currentScrollbarPos = int(ceil(brd.LP_HEIGHT - SCROLLBAR_HEIGHT) / (MAX_INSTRUCTIONS_SCROLLBAR_POS)) * ((scrollbarPos) % (MAX_INSTRUCTIONS_SCROLLBAR_POS + 1));
    drawScrollbar(currentScrollbarPos);
}

void Menu::drawLevel(Snake& snek) const
{
    brd.drawString({ LINE_START_X, LINE_START_Y }, "Level:", false);

    for (int i = 0; i < snek.getSpeed(); ++i) {
        drawLevelBar(i, true);
    }
    for (int i = snek.getSpeed(); i < Snake::MaxSpeed; ++i) {
        drawLevelBar(i, false);
    }

	drawConfirmButton("Accept");
}

void Menu::drawLevelBar(int barNum, bool fill) const
{
    const int PIXEL_SPACING = 1;
    const int X_LEFT = 2;
    const int Y_LOW = 36;
    const int BAR_X_SPACING = 3;
    const int BAR_Y_SPACING = 2;
    const int BAR_WIDTH = 5;
    const int BAR_HEIGHT = 9;

    brd.drawLargePixelRectangle({ X_LEFT + (BAR_X_SPACING + BAR_WIDTH)*barNum, Y_LOW - BAR_HEIGHT - BAR_Y_SPACING*barNum }, 1, BAR_HEIGHT + BAR_Y_SPACING*barNum, PIXEL_SPACING);
    brd.drawLargePixelRectangle({ X_LEFT + (BAR_X_SPACING + BAR_WIDTH)*barNum + 1, Y_LOW - BAR_HEIGHT - BAR_Y_SPACING*barNum }, BAR_WIDTH - 1, 1, PIXEL_SPACING);
    
    for (int y = Y_LOW; y < Y_LOW + BAR_HEIGHT + BAR_Y_SPACING*barNum; y += 2) {
        if (fill) {
            brd.drawLargePixelRectangle({ X_LEFT + (BAR_X_SPACING + BAR_WIDTH)*barNum + 1, y - BAR_HEIGHT - BAR_Y_SPACING*barNum }, BAR_WIDTH - 1, 1, PIXEL_SPACING);
        }
    }
}

void Menu::drawConfirmButton(std::string label) const
{
	const int CONFIRM_WIDTH = LetterMap::getStringWidth(label, Board::LETTER_SPACING);
	brd.drawString({ (Board::LP_WIDTH - RIGHT_SIDE_OFFSET - CONFIRM_WIDTH) / 2, CONFIRM_BUTTON_Y }, label, false);
}

int Menu::getHighlightedItemIndex() const
{
	return (topItemIndex + highlightedItemNumber) % (int)items.size();
}

void Menu::confirmSelection()
{
	selectedItem = items[getHighlightedItemIndex()];	
}


