#include "Menu.h"
#include <assert.h>
#include <string>

Menu::Menu(Board &brd, Snake &snek, Food &nom, Keyboard &kbd)
    :
    brd(brd),
    snek(snek),
    nom(nom),
    kbd(kbd)
{
	items.emplace_back(Item::NewGame);
	items.emplace_back(Item::TopScore);
	items.emplace_back(Item::Instructions);
	items.emplace_back(Item::Level);

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

    //  IT TOOK ME TOO LONG TO FIGURE OUT THIS FORMULA
    drawSideBar(((brd.GRID_HEIGHT - selectorHeight) / (int)items.size()) * ((highlightedItemNumber + selectedItemNumber()) % ((int)items.size())));
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

    brd.drawString(pos[position], getItemName(itemIn), isHighlighted);
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

void Menu::drawSideBar(int height)
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

std::string Menu::getItemName(const Item & itemIn) const
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

void Menu::reset()
{
    buttonPressed = false;
}

void Menu::returnToMenu()
{
    while (!kbd.KeyIsEmpty()) {
        const Keyboard::Event e = kbd.ReadKey();
        if (e.IsRelease()) {
            if (e.GetCode() == VK_RETURN || e.GetCode() == VK_ESCAPE) {
                buttonPressed = false;
            }
        }

        if (kbd.KeyIsPressed(VK_RETURN) || kbd.KeyIsPressed(VK_ESCAPE)) {
            if (!buttonPressed) {
                buttonPressed = true;
                reset();
                return;
            }
        }
    }
}

void Menu::drawTopScore(int topScore)
{
    brd.drawString({ 3, 3 }, "Top score:\n " + std::to_string(topScore), false);
    returnToMenu();
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
    const int ARRAY_SIZE = 15;
    const int SELECTOR_HEIGHT = 7;
    const int LINES_ON_SCREEN = 4;
    const int SCREEN_POSSIBILITIES = ARRAY_SIZE - LINES_ON_SCREEN + 1;
    const int RIGHT_SIDE_OFFSET = 2;

    std::string asd[ARRAY_SIZE] = { "" };
    LetterMap::splitStringByLimit(asd, "Make the snake grow longer by directing it to the food. Use the arrow keys or W, A, S, and D. You cannot stop the snake or make it go backwards. Try not to hit the walls or the tail.\n", 77, 1);

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
                if (scrollBarPos != 0) {
                    --scrollBarPos;
                }
            }
        }

        if (kbd.KeyIsPressed(VK_DOWN) || kbd.KeyIsPressed(0x53)) {
            if (!buttonPressed) {
                buttonPressed = true;
                if (scrollBarPos != ARRAY_SIZE - LINES_ON_SCREEN) {
                    ++scrollBarPos;
                }
            }

        }

        if (kbd.KeyIsPressed(VK_RETURN) || kbd.KeyIsPressed(VK_ESCAPE)) {
            if (!buttonPressed) {
                buttonPressed = true;
                scrollBarPos = 0;
                reset();
            }
        }

    }

    brd.drawString({ 2, 2 }, asd[scrollBarPos], false);
    brd.drawString({ 2, 12 }, asd[scrollBarPos + 1], false);
    brd.drawString({ 2, 22 }, asd[scrollBarPos + 2], false);
    brd.drawString({ 2, 32 }, asd[scrollBarPos + 3], false);

    drawSideBar(int(ceil(brd.GRID_HEIGHT - SELECTOR_HEIGHT) / (SCREEN_POSSIBILITIES)) * ((scrollBarPos) % (SCREEN_POSSIBILITIES)));
    returnToMenu();
  
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
                reset();
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

int Menu::selectedItemNumber()
{
	/*
    int counter = 0;
    MenuItem *temp = top;
    while (temp != first) {
        ++counter;
        temp = temp->next;
    }
    return counter;
	*/
	return 0;
}

void Menu::confirmSelection()
{
}


void Menu::goToTop()
{
	/*
    first = top;
    selectedItem = 0;
	*/
}


