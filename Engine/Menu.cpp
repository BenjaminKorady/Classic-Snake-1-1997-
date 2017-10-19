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

void Menu::draw()
{
    assert(highlightedItemNumber >= 0 && highlightedItemNumber < shownItems);

	for (int i = 0; i < shownItems; ++i) {
		drawItemName(items[(i + topItemIndex)%(int)items.size()], i, highlightedItemNumber == i);
	}

	static constexpr int buttonPosX = 27;
	static constexpr int buttonPosY = 39;

    brd.drawString({ buttonPosX, buttonPosY }, "Select", false);

    static constexpr int selectorHeight = 7;


    drawScrollbar(((brd.GRID_HEIGHT - selectorHeight) / (int)items.size()) * ((getHighlightedItemIndex()) % ((int)items.size())));
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

void Menu::drawItemName(Item itemIn, int position, bool isHighlighted) const
{
	assert(position >= 0);
	assert(position < shownItems);

	static constexpr int yItemSpacing = 10;
	static constexpr int startLocX = 2;
	static constexpr int startLocY = 2;

	PixelLocation pos[shownItems];
	for (int i = 0; i < shownItems; ++i) {
		pos[i] = { startLocX, startLocY + i*yItemSpacing };
	}

    brd.drawString(pos[position], drawItemString(itemIn), isHighlighted);
}

void Menu::drawItem(Item itemIn) const
{
}

void Menu::navigate()
{ 
    while (!kbd.KeyIsEmpty()) {
        const Keyboard::Event e = kbd.ReadKey();
		if (e.IsPress()) {
			if (e.GetCode() == (VK_UP) || e.GetCode() == (0x57)) {
				if (highlightedItemNumber != 0) {
					--highlightedItemNumber;
				}
				else {
					topItemIndex = topItemIndex == 0 ? (int)items.size() - 1 : topItemIndex - 1;
				}
			}
			if (e.GetCode() == (VK_DOWN) || e.GetCode() == (0x53)) {
				if (highlightedItemNumber < shownItems - 1) {
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

	//  Handle keyboard input

	while (!kbd.KeyIsEmpty()) {
		const Keyboard::Event e = kbd.ReadKey();
		if (e.IsPress()) {
			if (e.GetCode() == (VK_UP) || e.GetCode() == (0x57)) {
				if (scrollbarPos != 0) {
					--scrollbarPos;
				}
			}

			else if (e.GetCode() == VK_DOWN || e.GetCode() == (0x53)) {
				if(scrollbarPos != MAX_SCROLLBAR_POS) {
					++scrollbarPos;
				}
			}

			else if (e.GetCode() == VK_RETURN || e.GetCode() == VK_ESCAPE) {
				scrollbarPos = 0;
				returnToMenu();
			}
		}
	}

}

void Menu::drawScrollbar(int height)
{
    const int pixelSpacing = 1;
    const int selectorHeight = 7;
    const int rightSideOffset = 1;

    PixelLocation sideBarSelectorPos = { brd.GRID_WIDTH - rightSideOffset, height };
    brd.drawPixelRectangle({ brd.GRID_WIDTH - rightSideOffset, 1 }, 1, brd.GRID_HEIGHT - 1, pixelSpacing);
    brd.clearPixelRectangle(sideBarSelectorPos, 1, selectorHeight, pixelSpacing);
    brd.drawPixel({ sideBarSelectorPos.x, sideBarSelectorPos.y }, pixelSpacing);
    brd.drawPixel({ sideBarSelectorPos.x + 1, sideBarSelectorPos.y }, pixelSpacing);
    brd.drawPixelRectangle({ sideBarSelectorPos.x + 2, sideBarSelectorPos.y + 1 }, 1, selectorHeight - 1, pixelSpacing);
    brd.drawPixel({ sideBarSelectorPos.x + 1, sideBarSelectorPos.y + selectorHeight }, pixelSpacing);
    brd.drawPixel({ sideBarSelectorPos.x, sideBarSelectorPos.y + selectorHeight }, pixelSpacing);

}

std::string Menu::drawItemString(const Item & itemIn) const
{
	switch (itemIn) {
	case Item::Continue: return "Continue"; break;
	case Item::LastView: return "Last view"; break;
	case Item::NewGame: return "New game"; break;
	case Item::TopScore: return "Top score"; break;
	case Item::Instructions: return "Instructions"; break;
	case Item::Level: return "Level"; break;
	default: return ""; break;
	}
}

Menu::Item Menu::getSelection()
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
}

void Menu::returnToMenuOnReturnKeyPress()
{
	while (!kbd.KeyIsEmpty()) {
		const Keyboard::Event e = kbd.ReadKey();
		if (e.IsPress()) {
			if (e.GetCode() == VK_RETURN) {
				selectedItem = Item::None;
			}
		}
	}
}

void Menu::drawTopScore(int topScore)
{
    brd.drawString({ 3, 3 }, "Top score:\n " + std::to_string(topScore), false);
}

void Menu::drawLastView(const Snake& snekCache, const Food& nomCache)
{
    brd.drawBoard();
    snekCache.draw(brd);
    nomCache.draw(brd);
    returnToMenu();
 
}

void Menu::drawInstructions()
{


	for (int i = 0; i < MAX_LINES_ON_SCREEN; ++i) {
		if (scrollbarPos + i < (int)instructionsLines.size()) {
			brd.drawString({ LINE_START_X, LINE_START_Y + LINE_Y_SPACING*i }, instructionsLines[scrollbarPos + i], false);
		}
	}

    drawScrollbar(int(ceil(brd.GRID_HEIGHT - SCROLLBAR_HEIGHT) / (MAX_SCROLLBAR_POS)) * ((scrollbarPos) % (MAX_SCROLLBAR_POS)));
   
}

void Menu::drawLevel(Snake& snek)
{
    brd.drawString({ 2, 2 }, "Level:", false);
    const int MAX_SPEED = 9;

    //  Handle keyboard input
    while (!kbd.KeyIsEmpty()) {
        const Keyboard::Event e = kbd.ReadKey();
        if (e.IsRelease()) {
            if (e.GetCode() == VK_UP || e.GetCode() == VK_DOWN || e.GetCode() == 0x53 || e.GetCode() == 0x57 || e.GetCode() == VK_RETURN || e.GetCode() == VK_ESCAPE) {
                buttonPressed = false;
            }
        }

        if (kbd.KeyIsPressed(VK_UP) || kbd.KeyIsPressed(0x57)) {
            if (!buttonPressed) {
                buttonPressed = true;
                if (snek.speedLevel != MAX_SPEED) {
                    ++snek.speedLevel;
                }
            }
        }

        if (kbd.KeyIsPressed(VK_DOWN) || kbd.KeyIsPressed(0x53)) {
            if (!buttonPressed) {
                buttonPressed = true;
                if (snek.speedLevel != 1) {
                    --snek.speedLevel;
                }
            }

        }

        if (kbd.KeyIsPressed(VK_RETURN) || kbd.KeyIsPressed(VK_ESCAPE)) {
            if (!buttonPressed) {
                buttonPressed = true;
                return;
            }
        }
    }

    for (int i = 0; i < snek.speedLevel; ++i) {
        drawLevelBar(i, true);
    }
    for (int i = snek.speedLevel; i < MAX_SPEED; ++i) {
        drawLevelBar(i, false);
    }


    brd.drawString({ 25, 39 }, "Accept", false);

    snek.updateSpeed();
}

void Menu::drawLevelBar(int barNum, bool fill)
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

int Menu::getHighlightedItemIndex()
{
	return (topItemIndex + highlightedItemNumber) % (int)items.size();
}

void Menu::confirmSelection()
{
	selectedItem = items[getHighlightedItemIndex()];
	
}


