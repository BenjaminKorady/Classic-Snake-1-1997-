#pragma once

#include "Board.h"
#include <string>
#include "Keyboard.h"
#include "Snake.h"
#include "Food.h"
#include "LetterMap.h"
#include <math.h>

class Menu {
private:
    class MenuItem;
public:
    Menu(Board &brd, Snake &snek, Food &nom, Keyboard &kbd);
    void draw();
    void drawItem(MenuItem itemIn, int position, bool selected);
    void initMenuItems();
    void navigate();
    void drawSideBar(int height);
    std::string getSelection();
    bool optionSelected();
    void reset();
    void returnToMenu();
    void drawTopScore(int topScore);
    void drawLastView(const Snake& snekCache, const Food& nomCache);
    void drawInstructions();
    void drawLevel(Snake& snek);
    void addMenuItem(std::string labelIn);
    bool hasItem(std::string labelIn);
    void goToTop();

private:

    class MenuItem {
    public:
        std::string label;
        MenuItem* next;
        MenuItem* previous;
    };

    bool initialized = false;
    int selectedItem = 0;
    int nMenuItems = 0;
    const int MAX_MENU_ITEMS = 6;
    bool buttonPressed = false;
    bool confirmSelection = false;
    int scrollBarPos = 0;
    MenuItem* top;
    MenuItem* first;
    Keyboard &kbd;
    Food nom;
    Snake snek;
    Board brd;

    void drawLevelBar(int barNum, bool fill);
    int selectedItemNumber();
};