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
}

void Menu::draw()
{
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

}

void Menu::drawItem(MenuItem itemIn, int position, bool selected)
{

    const PixelLocation pos[3] = { { 2, 2 }, { 2, 12 }, {2, 22} };

    brd.drawString(pos[position], itemIn.label, selected);

}

void Menu::initMenuItems()
{
    if (!initialized) {
        item[0].label = "New Game";
        item[1].label = "Top Score";
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
    const int pixelSpacing = 0;
    const int selectorHeight = 7;
    const int rightSideOffset = 2;

    PixelLocation sideBarSelectorPos = { brd.GRID_WIDTH - rightSideOffset, height };
    brd.drawPixelRectangle({ brd.GRID_WIDTH - rightSideOffset, 1 }, 1, brd.GRID_HEIGHT - 1, pixelSpacing);
    brd.clearPixelRectangle(sideBarSelectorPos, 1, selectorHeight, pixelSpacing);
    brd.drawPixel({ sideBarSelectorPos.x, sideBarSelectorPos.y }, pixelSpacing);
    brd.drawPixel({ sideBarSelectorPos.x + 1, sideBarSelectorPos.y }, pixelSpacing);
    brd.drawPixelRectangle({ sideBarSelectorPos.x + 2, sideBarSelectorPos.y + 1 }, 1, selectorHeight - 1, pixelSpacing);
    brd.drawPixel({ sideBarSelectorPos.x + 1, sideBarSelectorPos.y + selectorHeight }, pixelSpacing);
    brd.drawPixel({ sideBarSelectorPos.x, sideBarSelectorPos.y + selectorHeight }, pixelSpacing);

}

void Menu::showInstructions()
{
    drawSideBar(7);
    //ke grow longer by directing it to the food.Use the keys 2,4,6 and 8. You cannot stop the snake or make it go backwards. Try not to hit the walls or the tail.")
    brd.drawString({ 2, 2 }, "Make the snake\ngrow longer by\ndirecting it to", false);
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
    selectedItem = 0;
    firstItem = 0;
    buttonPressed = false;
    menuSelection = -1;
    confirmSelection = false;
}

void Menu::showTopScore(int topScore)
{
    brd.drawString({ 3, 3 }, "Top score:\n " + std::to_string(topScore), false);
    while (!kbd.KeyIsEmpty()) {
        const Keyboard::Event e = kbd.ReadKey();
        if (e.IsRelease()) {
            if (e.GetCode() == VK_RETURN) {
                buttonPressed = false;
            }
        }

        if (kbd.KeyIsPressed(VK_RETURN) || kbd.KeyIsPressed(0x57)) {
            if (!buttonPressed) {
                buttonPressed = true;
                reset();
                selectedItem = 1;
                return;
            }
        }
    }
}

void Menu::addLastView()
{
    showLastView = true;
}


