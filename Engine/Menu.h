#pragma once

#include "Board.h"
#include <string>
#include "Keyboard.h"
#include "Snake.h"
#include "Food.h"

class Menu {
private:
    class MenuItem;
public:
    Menu(Board &brd, Snake &snek, Food &nom);
    void draw();
    void drawItem(MenuItem itemIn, int position, bool selected);
    void initMenuItems();
    void navigate(Keyboard &kbd);
    void drawSideBar(int height);
    void showInstructions();
    void blockInput(int delay);
    int getSelection();
    bool optionSelected();
    void backToMenu();
    int inputDelay = 0;
   // brd.drawString({ 27, 39 }, "Select", false);
 
private:

    class MenuItem {
    public:
        std::string label;
        MenuItem* next;
    };

    MenuItem item[5];

    bool showLastView = false;
    bool initialized = false;
    int selectedItem = 0;
    int firstItem = 0;
    int nMenuItems = 4 + int(showLastView);
    bool buttonPressed = false;
    bool confirmSelection = false;   
    int menuSelection = -1;

    Food nom;
    Snake snek;
    Board brd;

};