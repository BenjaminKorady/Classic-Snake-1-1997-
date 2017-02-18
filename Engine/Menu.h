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
    int getSelection();
    bool optionSelected();
    void reset();
    void returnToMenu();
    void drawTopScore(int topScore);
    void addLastView();
    void drawLastView(const Snake& snekCache, const Food& nomCache);
    void drawInstructions();
    void drawLevel();

private:

    class MenuItem {
    public:
        std::string label;
        MenuItem* next;
    };

    MenuItem item[5];
    Keyboard &kbd;

    bool showLastView = false;
    bool initialized = false;
    int selectedItem = 0;
    int firstItem = 0;
    int nMenuItems = 4;
    bool buttonPressed = false;
    bool confirmSelection = false;   
    int menuSelection = -1;
    int scrollBarPos = 0;

    Food nom;
    Snake snek;
    Board brd;

};