
/**   
    Main game logic

    Note: This code uses the basic logic from the
    Beginner C++ Game Programming DirectX [Snake Game] Tutorial 14a/b by ChiliTomatoNoodle on YouTube
    https://www.youtube.com/watch?v=KTyemy82Zqk
    https://www.youtube.com/watch?v=DoO_NEksf3c

    @author Benamin Korady
    @version 1.0    12/02/2017
        
*/

/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Snake.h"
#include <random>
#include "Food.h"
#include "PixelLocation.h"
#include "Menu.h"
#include <string>
#include <chrono>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();

private:
	void ComposeFrame();
	void UpdateModel();
    void drawBackground();
    void drawGameOver();
    void gameReset();
    void updateGame();

	MainWindow& wnd;
	Graphics gfx;
	Board brd;
	bool isGameOver = false;
    Color bgColor;
    Snake snek;
    Snake snekCache;
    Food nom;
    Food nomCache;
	PixelLocation direction = { 1, 0 };     //  Directional vector. Default is { 1, 0 } (right)
    Menu menu;
    int menuSelection = -1;
    int topScore = 0;
};