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
	switch (menu.getSelectedItem()) {
	case Menu::Item::None: {
		menu.navigate();
	} break;
	case Menu::Item::Continue: {
		updateGame();
	} break;
	case Menu::Item::NewGame: {
		if (menu.hasItem(Menu::Item::Continue)) {
			menu.removeItem(Menu::Item::Continue);
			gameReset();
		}
		updateGame();
	} break;
	case Menu::Item::Level: {
		menu.navigateLevel(snek);
	} break;
	case Menu::Item::Instructions:
		menu.navigateInstructions();
	case Menu::Item::LastView: 
	case Menu::Item::TopScore:
		menu.returnToMenuOnReturnKeyPress();
    break;
	}

}

void Game::ComposeFrame()
{
    drawBackground();

	switch (menu.getSelectedItem()) {
	case Menu::Item::None:
		menu.draw();
		break;
	case Menu::Item::NewGame:
	case Menu::Item::Continue:
		if (isGameOver) {
			drawGameOver();
		}
		else {
			drawGame();
		}
		break;
	case Menu::Item::Instructions:
		menu.drawInstructions();
		break;
	case Menu::Item::LastView:
		menu.drawLastView(snekCache, nomCache);
		break;
	case Menu::Item::Level:
		menu.drawLevel(snek);
		break;
	case Menu::Item::TopScore:
		menu.drawTopScore(topScore);
		break;
	}

}


/**
Draws the background fill
*/
void Game::drawBackground()
{
	gfx.DrawRectDim(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight, bgColor);
}

void Game::drawGame()
{
	brd.draw();
	snek.draw(brd);
	nom.draw(brd);
}

/**
Draws the game over screen
*/
void Game::drawGameOver()
{	
	brd.drawString({ 3, 3 }, "Game over!\nYour score:\n" + std::to_string(score), false);
}

/**
Resets the game functionality
*/
void Game::gameReset()
{
	isGameOver = false;
	snek.reset();
	nom.reset();
	score = 0;
}

void Game::updateGame()
{
	// Handle keyboard input
	while (!wnd.kbd.KeyIsEmpty()) {
		const Keyboard::Event e = wnd.kbd.ReadKey();
		if (e.IsPress()) {
			if (isGameOver) {
				if (e.GetCode() == VK_ESCAPE || e.GetCode() == VK_RETURN) {
					if (score > topScore) {
						topScore = score;
					}
					menu.returnToMenu();
					gameReset();
					return;
				}
			}
			else {
				if (e.GetCode() == VK_ESCAPE || e.GetCode() == VK_RETURN) {
					menu.returnToMenu();
					if (!menu.hasItem(Menu::Item::Continue)) {
						menu.addItem(Menu::Item::Continue);
					}
					return;
				}
				snek.handleKeyPressEvent(e);
			}

		}
	}

	if (!isGameOver) {
		const auto now = std::chrono::steady_clock::now();								// Store current time
		if (snek.isTurnToMove(now) && snek.getDirection() != Vec2_<int>(DIR_ZERO)) {	
			Vec2_<int> nextLocation = snek.getNextHeadLocation();						// Check where snake is about to go in its next step
			if (brd.isInsideBoard(nextLocation) && !snek.isInTile(nextLocation)) {		// Snake is not about to collide with the walls or its body
				if (nextLocation == nom.getLocation()) { // Snake is about to eat food
					snek.grow();
					nom.respawn(snek);
					score += snek.getSpeed();
				}
				snek.move(brd);
			}
			else { // Snake dies
				isGameOver = true;
				if (menu.hasItem(Menu::Item::Continue)) {
					menu.removeItem(Menu::Item::Continue);
				}
				snekCache = snek;	// Store last snake and food to 
				nomCache = nom;		// draw them in "Last view"
				if (!menu.hasItem(Menu::Item::LastView)) {
					menu.addItem(Menu::Item::LastView);
				}
			}
		}
	}
}
