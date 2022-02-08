#pragma once
#include "stdfix.h"

class Snake
{

private:

	vector<pair <int, int>> body;

	int x = 30, y = 15;
	int difficulty, score, length;

	bool bonus, gameGo, gameOver, restart, pause = false, exit = false;

	char Coord[50];
	char keyState[4]{ 0 };

	class Objects 
	{
	public:

		vector<pair<int, int>> apple;
		vector<pair<int, int>> bonus;
	};

	Objects obj;

public:

	void SetPoint(int x, int y);

	void SnakeBody();

	void DrawApple();

	void DrawBonus();

	void ObjTh();

	void ThrOver();

	void GameOver();

	void ClearSnake();

	void Score();

	void HotKeys();

	void ThHotKeys();

	void LevelMenu();

	void SnakeMove();
};

