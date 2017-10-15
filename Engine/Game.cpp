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
#include "LetterMap.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),                       //  Window
	gfx(wnd),                       //  Graphics
	brd(gfx),                       //  Board
    snek(),                         //  Snake
    snekCache(),
    nom(),                          //  Food
    nomCache(),
    menu(brd, snek, nom, wnd.kbd),  //  Menu
    bgColor(172, 193, 0)            //  Green background color
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
        const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        bool buttonPressed = false;
        if (!isGameOver) {
            while (!wnd.kbd.KeyIsEmpty()) {
                const Keyboard::Event e = wnd.kbd.ReadKey();
                if (e.IsRelease()) {
                    if (e.GetCode() == VK_RETURN || e.GetCode() == VK_ESCAPE) {
                        buttonPressed = false;
                    }
                }
                if (wnd.kbd.KeyIsPressed(VK_ESCAPE) || wnd.kbd.KeyIsPressed(VK_RETURN)) {
                    inMenu = true;
                 //   menu.addItem("Continue");
                    menu.reset();
                    menu.goToTop();
                    snek.cacheDirection();
                    return;
                }
            }
        }
        updateGame(now);
    } 
	else {
		menu.navigate();
	}
}

/**
    Draws the background fill
*/
void Game::drawBackground()
{    
    gfx.DrawRectDim(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight, bgColor);
}

/**
    Draws the game over screen
*/
void Game::drawGameOver()
{
    //  Calculate current score
    int score = snek.getFoodEaten() * snek.speedLevel;

    //  Set topScore if it was beaten
    if (score > topScore) {
        topScore = score;
    }

    //  Draw the game over message
    brd.drawString({ 3, 3 }, "Game over!\nYour score:\n" + std::to_string(score), false);

    //  Handle keyboard input
    bool buttonPressed = false;
    while (!wnd.kbd.KeyIsEmpty()) {
        const Keyboard::Event e = wnd.kbd.ReadKey();
        if (e.IsRelease()) {
            if (e.GetCode() == VK_RETURN || e.GetCode() == VK_ESCAPE) {
                buttonPressed = false;
            }
        }

        //  Return back to the menu if Enter or Esc was pressed
        if (wnd.kbd.KeyIsPressed(VK_RETURN) || wnd.kbd.KeyIsPressed(VK_ESCAPE)) {
            if (!buttonPressed) {
                buttonPressed = true;
                menu.reset();
                menu.goToTop();
                inMenu = true;
                return;
            }
        }
    }
}

/**
    Resets the game functionality
*/
void Game::gameReset()
{
    isGameOver = false;
    snek.reset();
    nom.reset();
}

/**
    Handles the main game functionality
*/
void Game::updateGame(std::chrono::steady_clock::time_point now)
{
    if (!isGameOver) {
        direction = snek.getNextDirection(wnd.kbd);
        PixelLocation zero(0, 0);
        if (direction != zero) {

            //  If has been idle long enough to move (This manages the snake's speed)
            
            if (snek.isTurnToMove(now)) {

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
      //              if (!menu.hasItem("Last view")) {
      //                  menu.addItem("Last view");
     //               }
                }
            }
        }
    }

}

void Game::ComposeFrame()
{
    
    drawBackground();


    if (inMenu) {
		menu.draw();
/*
	
        //  Menu
        if (menu.getSelection() == "No selection") {
            menu.navigate();
        }
        //  New game
        if (menu.getSelection() == "New game") {
            gameReset();        
            inMenu = false;
        }
        //  Top score
        else if (menu.getSelection() == "Top score") {
            menu.drawTopScore(topScore);            
        }
        //  Instructions
        else if (menu.getSelection() == "Instructions") {
            menu.drawInstructions();
        }
        //  Level
        else if (menu.getSelection() == "Level") {
            menu.drawLevel(snek);
        }
        //  Last view
        else if (menu.getSelection() == "Last view") {
            menu.drawLastView(snekCache, nomCache);
        }
        else if (menu.getSelection() == "Continue") {
            inMenu = false;
            menu.removeItem("Continue");
        }
		*/
    }

    //  Out of menu / in game
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
