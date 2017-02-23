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
    initMenuItems();
    addMenuItem("Level");
    addMenuItem("Instructions");
    addMenuItem("Top Score");
    addMenuItem("New game");
}

void Menu::draw()
{
    /*
    assert(selectedItem >= 0 && selectedItem <= 2);

    bool selected0 = (selectedItem == 0);
    bool selected1 = (selectedItem == 1);
    bool selected2 = (selectedItem == 2);

    drawItem(item[firstItem], 0, selected0);
    drawItem(*item[firstItem].next, 1, selected1);
    drawItem(*item[firstItem].next->next, 2, selected2);

    brd.drawString({ 27, 39 }, "Select", false);

    const int selectorHeight = 7;

    //  IT TOOK ME TOO LONG TO FIGURE OUT THIS FORMULA
    drawSideBar(((brd.GRID_HEIGHT - selectorHeight) / nMenuItems) * ((firstItem + selectedItem) % (nMenuItems)));
    */
}

void Menu::drawItem(MenuItem itemIn, int position, bool selected)
{

    const PixelLocation pos[3] = { { 2, 2 }, { 2, 12 }, {2, 22} };

    brd.drawString(pos[position], itemIn.label, selected);

}

void Menu::initMenuItems()
{
    root = new MenuItem;
    root->next = nullptr;
    root->previous = nullptr;

    /*
    if (!initialized) {
        item[0].label = "New game";
        item[1].label = "Top score";
        item[2].label = "Instructions";
        item[3].label = "Level";
        item[4].label = "Last view";
        item[0].next = &item[1];
        item[1].next = &item[2];
        item[2].next = &item[3];
        item[4].next = &item[0];

        initialized = true;
    }

    if (showLastView) {
        item[3].next = &item[4]; 
        nMenuItems = 5;
    }
    else {
        item[3].next = &item[0];
    }
    */

}

void Menu::navigate()
{
    
    while ( !kbd.KeyIsEmpty() ) {         	
        const Keyboard::Event e = kbd.ReadKey();
        if (e.IsRelease()) {
            if (e.GetCode() == VK_UP || e.GetCode() == VK_DOWN || e.GetCode() == 0x53 || e.GetCode() == 0x57) {
                buttonPressed = false;
            }             	
        }
    
        if (kbd.KeyIsPressed(VK_UP) || kbd.KeyIsPressed(0x57)) {
            if (!buttonPressed) {
                buttonPressed = true;
                if (selectedItem != 0) {
                    --selectedItem;
                }
                else {
                if (--firstItem == -1) {
                    firstItem = nMenuItems - 1;
                }
            }
        }
    }

    if (kbd.KeyIsPressed(VK_DOWN) || kbd.KeyIsPressed(0x53)) {
        if (!buttonPressed) {
            buttonPressed = true;
            if (selectedItem != 2) {
                ++selectedItem;                
            }
            else {
                ++firstItem;
                firstItem = firstItem % nMenuItems;
                                       
            }
        }
        
    }

    if (kbd.KeyIsPressed(VK_RETURN)) {
        if (!buttonPressed) {
            buttonPressed = true;
            confirmSelection = true;
            menuSelection = 0;
            return;            
        }
    }

  

   
    
    }
    draw();
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

int Menu::getSelection()
{
    if (confirmSelection)
        return (firstItem + selectedItem) % nMenuItems;
    return -1;
}

bool Menu::optionSelected()
{
    return confirmSelection;
}

void Menu::reset()
{
    buttonPressed = false;
    menuSelection = -1;
    confirmSelection = false;
}

void Menu::returnToMenu()
{
    while (!kbd.KeyIsEmpty()) {
        const Keyboard::Event e = kbd.ReadKey();
        if (e.IsRelease()) {
            if (e.GetCode() == VK_RETURN) {
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
                return;
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

void Menu::addMenuItem(std::string labelIn)
{
    MenuItem *newItem = new MenuItem;
    

    if (root->next == nullptr) {
        root->next = newItem;
        newItem->next = newItem;
        newItem->previous = newItem;
    }
    else {
        MenuItem *first;
        first = root->next;
        root->next = newItem;
        newItem->next = first;
        newItem->previous = first->previous;
        first->previous->next = newItem;
        first->previous = newItem;
    }
    newItem->label = labelIn;

}


