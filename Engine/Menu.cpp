#include "Menu.h"
#include <assert.h>
#include <string>
#include <iterator>
#include <vector>

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

// TODO: Fix magic numbers here
void Menu::draw() const
{
    assert(highlightedItemNumber >= 0 && highlightedItemNumber < SHOWN_ITEMS);

	for (int i = 0; i < SHOWN_ITEMS; ++i) {
		drawItemName(items[(i + topItemIndex)%(int)items.size()], i, highlightedItemNumber == i);
	}

	static constexpr int buttonPosX = 27;
	static constexpr int buttonPosY = 39;

    brd.drawString({ buttonPosX, buttonPosY }, "Select", false);

    drawScrollbar(((brd.GRID_HEIGHT - SCROLLBAR_HEIGHT) / (int)items.size()) * ((getHighlightedItemIndex()) % ((int)items.size())));
}

bool Menu::hasItem(Item itemIn) const
{
	for (Item i : items) {
		if (i == itemIn) {
			return true;
		}
	}
	return false;
}

// TODO: Fix magic numbers here
void Menu::drawItemName(Item itemIn, int position, bool isHighlighted) const
{
	assert(position >= 0);
	assert(position < SHOWN_ITEMS);

	static constexpr int yItemSpacing = 10;
	static constexpr int startLocX = 2;
	static constexpr int startLocY = 2;

	PixelLocation pos[SHOWN_ITEMS];
	for (int i = 0; i < SHOWN_ITEMS; ++i) {
		pos[i] = { startLocX, startLocY + i*yItemSpacing };
	}

    brd.drawString(pos[position], getItemString(itemIn), isHighlighted);
}

void Menu::navigate()
{ 
    while (!kbd.KeyIsEmpty()) {
        const Keyboard::Event e = kbd.ReadKey();
		if (e.IsPress()) {
			if (e.GetCode() == (VK_UP) || e.GetCode() == ('W')) {
				if (highlightedItemNumber != 0) {
					--highlightedItemNumber;
				}
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

void Menu::navigateLevel(Snake & snek)
{
	while (!kbd.KeyIsEmpty()) {
		const Keyboard::Event e = kbd.ReadKey();
		if (e.IsPress()) {
			int snekSpeed = snek.getSpeed();
			if (e.GetCode() == (VK_UP) || e.GetCode() == ('W')) {
				if (snekSpeed != MAX_LEVEL) {
					snek.setSpeed(++snekSpeed);
				}
			}

			if (e.GetCode() == (VK_DOWN) || e.GetCode() == ('S')) {
				if (snekSpeed != MIN_LEVEL) {
					snek.setSpeed(--snekSpeed);
				}
			}
			if (e.GetCode() == (VK_RETURN) || e.GetCode() == (VK_ESCAPE)) {
				returnToMenu();
			}
		}
	}
}

void Menu::drawScrollbar(int height) const
{
    constexpr int PIXEL_SPACING = 1;
    constexpr int RIGHT_OFFSET_X = 1;
	constexpr int TOP_OFFSET_Y = 1;

    PixelLocation sideBarSelectorPos = { brd.GRID_WIDTH - RIGHT_OFFSET_X, height };

	{
							
		brd.drawPixelRectangle({ brd.GRID_WIDTH - RIGHT_OFFSET_X, TOP_OFFSET_Y }, 1, brd.GRID_HEIGHT - 1, PIXEL_SPACING);
		brd.clearPixelRectangle(sideBarSelectorPos, 1, SCROLLBAR_HEIGHT, PIXEL_SPACING);
		brd.drawPixel({ sideBarSelectorPos.x, sideBarSelectorPos.y }, PIXEL_SPACING);
		brd.drawPixel({ sideBarSelectorPos.x + 1, sideBarSelectorPos.y }, PIXEL_SPACING);
		brd.drawPixelRectangle({ sideBarSelectorPos.x + 2, sideBarSelectorPos.y + 1 }, 1, SCROLLBAR_HEIGHT - 1, PIXEL_SPACING);
		brd.drawPixel({ sideBarSelectorPos.x + 1, sideBarSelectorPos.y + SCROLLBAR_HEIGHT }, PIXEL_SPACING);
		brd.drawPixel({ sideBarSelectorPos.x, sideBarSelectorPos.y + SCROLLBAR_HEIGHT }, PIXEL_SPACING);
	}

}

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

Menu::Item Menu::getSelectedItem()
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
    brd.drawString({ TOP_LEFT_TEXT_X, TOP_LEFT_TEXT_Y }, "Top score:\n " + std::to_string(topScore), false);
}

void Menu::drawLastView(const Snake& snekCache, const Food& nomCache) const
{
    brd.drawBoard();
    snekCache.draw(brd);
    nomCache.draw(brd);
}

// TODO: Maybe not use scrollbarPos as index?
void Menu::drawInstructions() const
{
	for (int i = 0; i < MAX_LINES_ON_SCREEN; ++i) {
		if (scrollbarPos + i < (int)instructionsLines.size()) {
			brd.drawString({ LINE_START_X, LINE_START_Y + LINE_Y_SPACING*i }, instructionsLines[scrollbarPos + i], false);
		}
	}

	int currentScrollbarPos = int(ceil(brd.GRID_HEIGHT - SCROLLBAR_HEIGHT) / (MAX_INSTRUCTIONS_SCROLLBAR_POS)) * ((scrollbarPos) % (MAX_INSTRUCTIONS_SCROLLBAR_POS));
    drawScrollbar(currentScrollbarPos);
}

// TODO: Magic numbers fix
void Menu::drawLevel(Snake& snek) const
{
    brd.drawString({ TOP_LEFT_TEXT_X, TOP_LEFT_TEXT_Y }, "Level:", false);

    for (int i = 0; i < snek.getSpeed(); ++i) {
        drawLevelBar(i, true);
    }
    for (int i = snek.getSpeed(); i < MAX_LEVEL; ++i) {
        drawLevelBar(i, false);
    }

    brd.drawString({ 25, 39 }, "Accept", false);   
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

    brd.drawPixelRectangle({ X_LEFT + (BAR_X_SPACING + BAR_WIDTH)*barNum, Y_LOW - BAR_HEIGHT - BAR_Y_SPACING*barNum }, 1, BAR_HEIGHT + BAR_Y_SPACING*barNum, PIXEL_SPACING);
    brd.drawPixelRectangle({ X_LEFT + (BAR_X_SPACING + BAR_WIDTH)*barNum + 1, Y_LOW - BAR_HEIGHT - BAR_Y_SPACING*barNum }, BAR_WIDTH - 1, 1, PIXEL_SPACING);
    
    for (int y = Y_LOW; y < Y_LOW + BAR_HEIGHT + BAR_Y_SPACING*barNum; y += 2) {
        if (fill) {
            brd.drawPixelRectangle({ X_LEFT + (BAR_X_SPACING + BAR_WIDTH)*barNum + 1, y - BAR_HEIGHT - BAR_Y_SPACING*barNum }, BAR_WIDTH - 1, 1, PIXEL_SPACING);
        }
    }
}

int Menu::getHighlightedItemIndex() const
{
	return (topItemIndex + highlightedItemNumber) % (int)items.size();
}

void Menu::confirmSelection()
{
	selectedItem = items[getHighlightedItemIndex()];	
}


