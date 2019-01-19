#include "stdafx.h"
#include "GameClass.h"

//Define the console handle 
//HANDLE Utilities::hConsole_c = 0;

GameClass::GameClass()
{
	//Utilities::initialize();
}


GameClass::~GameClass()
{
}

void  GameClass::genedateFruitLocation() {
	bool location_good = false;

	while (!location_good) {
		location_good = true;
		_fruitX = rand() % Utilities::WIDTH;
		_fruitY = rand() % Utilities::HEIGHT;
		
		if (_fruitX <= 2 || _fruitY <= 2 ||
			_fruitX >= Utilities::WIDTH - 2 || _fruitY >= Utilities::HEIGHT - 2) {
			location_good = false;
		}
		for (auto i : snake.getBody()) {
			if (_fruitX == i.pos().X && _fruitY == i.pos().Y) {
				location_good = false;
			}
		}

	}
}

void  GameClass::initBoard() {
	system("cls");//Windows os
	for (int i = 0; i < Utilities::HEIGHT; i++) {
		for (int j = 0; j < Utilities::WIDTH; j++) {
			if (i == 0 || i == Utilities::HEIGHT - 1) {
				std::cout << "=";
			}
			else if (j == 0 || j == Utilities::WIDTH - 1) {
				std::cout << "|";
			}
			else {
				std::cout << " ";
			}

		}
		if (i < Utilities::HEIGHT - 1) {
			std::cout << std::endl;
		}

	}

	Utilities::drawString(Utilities::WIDTH / 2 - 10, Utilities::HEIGHT / 2 - 2, "Press any arrow to begin..");

	_gameState = Utilities::GAME_DRAW;
}

void  GameClass::renderLoop() {

	for (auto i : snake.getBody()) {
		Utilities::drawChar(i.lastPos(), ' ');
		if (i == snake.head()) {
			Utilities::drawChar(i.pos(), 'O');
		}
		else {
			Utilities::drawChar(i.pos(), 'o');
		}

	}
	
	Utilities::drawChar(_fruitX, _fruitY, '#');

}


void GameClass::gameSetup() {
	_gameState = Utilities::GAME_START;
	snake.updateHeadPos(Utilities::START_POS);
	genedateFruitLocation();
	_score = 0;
	score_changed = true;
	_life = 1;
	life_changed = true;
	_first_init = true;
}

void GameClass::Logic() {

	if (_gameState == Utilities::GAME_WAIT) return;

	snake.move();

	//Borders Collision:
	if (snake.collisionOnWidth(0, Utilities::WIDTH - 1) || snake.collisionOnHeight(0, Utilities::HEIGHT - 1)) {
		_life--;
		life_changed = true;
		if (_life <= 0) {
			_gameState = Utilities::GAME_RESET;
		}
	}

	//Fruit Collision:
	if (snake.collisionCheck(_fruitX, _fruitY)) {
		_score++;
		score_changed = true;
		snake.addNode();
		genedateFruitLocation();
	}

	//Collide Himself:
	for (auto i : snake.getBody()) {
		if (i == snake.head())continue;
		if (snake.collisionCheck(i.lastPos())) {
			_life--;
			life_changed = true;
			if (_life == 0) {
				_gameState = Utilities::GAME_RESET;
			}
		}
	}

	if (_gameState == Utilities::GAME_RESET) {
		snake.reset();
	}

}

void GameClass::inputProcess() {
	if (_kbhit()) {
		char c = _getch();
		switch (c) {
			//Arrow Pressed:
		case -32: // Arrow: first value
			if (_gameState != Utilities::GAME_START && _gameState != Utilities::GAME_DRAW)
				return;
			_gameState = Utilities::GAME_DRAW;
			if(_first_init)
				_first_init = false;
			c = _getch(); // skip the [
			switch (c)
			{
			case 'H': //ARROW UP
				snake.changeDirection(snake.UP);
				break;
			case 'P': //ARROW DOWN
				snake.changeDirection(snake.DOWN);
				break;
			case 'M': //ARROW RIGHT
				snake.changeDirection(snake.RIGHT);
				break;
			case 'K': //ARROW LEFT
				snake.changeDirection(snake.LEFT);
				break;
			default:
				break;
			}
			break;
			//Yes Pressed(While on RESET mode):
		case 'y':
		case 'Y':
			if (_gameState == Utilities::GAME_RESET)
				gameSetup();//Reset
			break;
			//Exit Pressed:
		case 'x':
		case 'X':
			_gameState = Utilities::GAME_OVER;
			return;
			break;
			//Pause Pressed:
		case 'p':
		case 'P':
			if (_gameState == Utilities::GAME_WAIT) {
				_gameState = Utilities::GAME_DRAW;
			}
			else {
				_gameState = Utilities::GAME_WAIT;
			}
			break;
			//Else:
		default:
			break;
		}
	}
}

void GameClass::Draw() {
	//-----------------
	//Game Wait:
	//-----------------
	if (_gameState == Utilities::GAME_WAIT) return;
	//-----------------
	//Game Initialize:
	//-----------------
	if (_gameState == Utilities::GAME_START) {
		initBoard();
		return;
	}
	//-----------------
	//Game Over:
	//-----------------
	if (_gameState == Utilities::GAME_RESET) {
		Utilities::drawOn((Utilities::WIDTH / 2) - 10, (Utilities::HEIGHT / 2) - 3);
		std::cout << "Game Over! Your score: [" << _score << "]";
		Utilities::drawOn((Utilities::WIDTH / 2) - 10, (Utilities::HEIGHT / 2) - 2);
		std::cout << "SO... Again? <Y/X>  ";
		inputProcess();
		return;
	}
	//-----------------
	//Game Play:
	//-----------------
	if (!_first_init) {
		//Deleting the 'press an arrow' string
		Utilities::deleteString(Utilities::WIDTH / 2 - 10, Utilities::HEIGHT / 2 - 2,27);
	}
	//----------------------------------------------
	//                RENDERING:
	//----------------------------------------------
	//Score:
	if (score_changed) {
		Utilities::drawOn(0, Utilities::HEIGHT);
		std::cout << "Score: [" << _score << "]";
		score_changed = false;
	}
	//--------------------------------
	//Life:
	if (life_changed) {
		Utilities::drawOn(0, Utilities::HEIGHT + 1);
		std::cout << "Life: [" << _life << "]";
		Utilities::drawString(0, Utilities::HEIGHT + 2, "<Press 'P' To Pause>");
		life_changed = false;
		snake.updateHeadPos(Utilities::START_POS);
		return;
	}
	//--------------------------------
	//Game:
	renderLoop();
	//--------------------------------
	//For smoother drawing:
	Utilities::drawOn(0, 0);

}

void GameClass::gameLoop() {
	gameSetup();

	while (_gameState != Utilities::GAME_OVER) {

		inputProcess();
		Logic();
		Draw();

		Sleep(66);
	}
}