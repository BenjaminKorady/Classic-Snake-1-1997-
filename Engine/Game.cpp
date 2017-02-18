/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),               //  Window
	gfx(wnd),               //  Graphics
	brd(gfx),               //  Board
    snek(),                 //  Snake
    snekCache(),
    nom(),                  //  Food
    nomCache(),
    menu(brd, snek, nom, wnd.kbd),
    bgColor(172, 193, 0)   // Green background color


{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
    if(!inMenu) {
        updateGame();
    }
}

void Game::drawBackground()
{
    //Draws background fill
    gfx.DrawRectDim(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight, bgColor);

}

void Game::drawGameOver()
{
    int score = snek.getFoodEaten() * snek.getSpeed();
    if (score > topScore) {
        topScore = score;
    }
    brd.drawString({ 3, 3 }, "Game over!\nYour score:\n" + std::to_string(score), false);
    bool buttonPressed = false;
    while (!wnd.kbd.KeyIsEmpty()) {
        const Keyboard::Event e = wnd.kbd.ReadKey();
        if (e.IsRelease()) {
            if (e.GetCode() == VK_RETURN) {
                buttonPressed = false;
            }
        }

        if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
            if (!buttonPressed) {
                buttonPressed = true;
                menuSelection = -1;
                menu.reset();
                inMenu = true;
                return;
            }
        }
    }
}

void Game::gameReset()
{
    isGameOver = false;
    snek.reset();
    nom.reset();
}

void Game::updateGame()
{
    if (!isGameOver) {
        direction = snek.getNextDirection(wnd.kbd);
        PixelLocation zero(0, 0);
        if (direction != zero) {

            //  Increments snake's idleFor value (Snake has been idle for a frame)
            snek.incIdleFor();

            //  If has been idle long enough to move (This manages the snake's speed)
            if (snek.isTurnToMove()) {

                PixelLocation nextLocation = snek.getNextHeadLocation(direction);

                //  If snakes is not about to collide with the board from or its body
                if (brd.isInsideBoard(nextLocation) && !snek.isInLocation(nextLocation)) {

                    //  If snake is about to eat food
                    if (nextLocation == nom.getLocation()) {
                        snek.grow();
                        nom.respawn(snek);
                        nom.draw(brd);
                        snek.incFoodEaten();
                    }

                    snek.resetMoveBuffer();
                    snek.move(direction, brd);

                }

                else {
                    direction = { 0, 0 };
                    isGameOver = true;
                    snekCache = snek;
                    nomCache = nom;
                    menu.addLastView();
                    menu.initMenuItems();
                }
            }
        }
    }

}

void Game::ComposeFrame()
{
    drawBackground();

    //  Menu
    if (inMenu) {
        if (menu.getSelection() == -1) {
            menu.navigate();
        }
        //  New game
        if (menu.getSelection() == 0) {
            gameReset();        
            inMenu = false;
        }
        //  Top score
        else if (menu.getSelection() == 1) {
            menu.drawTopScore(topScore);            
        }
        //  Instructions
        else if (menu.getSelection() == 2) {
            menuSelection = 2;
            menu.showInstructions();
        }
        //  Level
        else if (menu.getSelection() == 3) {
            menuSelection = 3;
        }
        //  Last view
        else if (menu.getSelection() == 4) {
            menu.drawLastView(snekCache, nomCache);
        }

    }
    else {
        if (!isGameOver) {
            brd.drawBoard();
            snek.draw(brd);
            nom.draw(brd);
        }
        else {
            drawGameOver();
        }
    }
}
