#pragma once
#include "Snake.h"
#include "Utilities.h"

class GameClass
{
public:
	GameClass();
	~GameClass();

	void genedateFruitLocation();

	void initBoard();
	

	void renderLoop();

	void gameSetup();
	void Logic();
	void Draw();
	void inputProcess();

	void gameLoop();


private:
	Snake snake;
	Utilities::Game_States _gameState;
	int _fruitX, _fruitY, _score, _life;
	bool score_changed;
	bool life_changed;
	bool _first_init;
	 
};

