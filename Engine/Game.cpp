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
	switch (menu.getSelection()) {
	case Menu::Item::Continue: {
		updateGame();
	} break;
	case Menu::Item::None: {
		menu.navigate(); 
	} break;
	case Menu::Item::NewGame: {
		updateGame();
	} break;

	}

}

void Game::ComposeFrame()
{
    
    drawBackground();


    if (menu.getSelection() == Menu::Item::None) {
		menu.draw();
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
	while (!wnd.kbd.KeyIsEmpty()) {
		const Keyboard::Event e = wnd.kbd.ReadKey();
		if (e.IsRelease()) {
			if (e.GetCode() == VK_RETURN || e.GetCode() == VK_ESCAPE) {
			}
		}

		//  Return back to the menu if Enter or Esc was pressed
		if (wnd.kbd.KeyIsPressed(VK_RETURN) || wnd.kbd.KeyIsPressed(VK_ESCAPE)) {
				menu.reset();
				return;
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

void Game::updateGame()
{
	if (!isGameOver) {
		const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

		// Check for game pause
		while (!wnd.kbd.KeyIsEmpty()) {
			const Keyboard::Event e = wnd.kbd.ReadKey();
			if (e.IsPress()) {
				if (e.GetCode() == VK_ESCAPE || e.GetCode() == VK_RETURN) {
					menu.returnToMenu();
					if (!menu.hasItem(Menu::Item::Continue)) {
						menu.addItem(Menu::Item::Continue);
					}
					snek.cacheDirection();
					return;
				}
			}
		}

		direction = snek.getNextDirection(wnd.kbd);
		PixelLocation zero(0, 0);
		if (direction != zero) {
			//  If has been idle long enough to move (This manages the snake's speed)
			if (snek.isTurnToMove(now)) {
				PixelLocation nextLocation = snek.getNextHeadLocation(direction);
				//  If snake is not about to collide with the board or its body
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

				// Snake dies
				else {
					direction = { 0, 0 };
					isGameOver = true;
					if (menu.hasItem(Menu::Item::Continue)) {
						menu.removeItem(Menu::Item::Continue);
					}
					snekCache = snek;
					nomCache = nom;
					if (!menu.hasItem(Menu::Item::LastView)) {
						menu.addItem(Menu::Item::LastView);
					}
				}
			}
		}
	}
	else {
		while (!wnd.kbd.KeyIsEmpty()) {
			const Keyboard::Event e = wnd.kbd.ReadKey();
			if (e.IsPress()) {
				if (e.GetCode() == VK_ESCAPE || e.GetCode() == VK_RETURN) {

					menu.returnToMenu();
					snek.cacheDirection();
					gameReset();
					return;
				}
			}
		}
	}
}
