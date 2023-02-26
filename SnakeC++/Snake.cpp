#include "Snake.h"

void Snake::SetPoint(int x, int y)
{
	sprintf_s(Coord, "%s%d;%dH", CSI, y, x);
	printf(Coord);
}

void Snake::SnakeBody()
{
	body.insert(body.begin(), make_pair(x, y));

	SetPoint(body[0].first, body[0].second);
	cout << "*";
}

void Snake::ThrOver()
{
	thread over(&Snake::GameOver, this);
	over.detach();
}

void Snake::GameOver()
{
	int pX, pY;
	while (!gameOver)
	{
		this_thread::sleep_for(30ms);
		if (((body[0].first <= 1) || (body[0].first >= 118)) || ((body[0].second <= 1) || (body[0].second >= 33))) {

			PlaySound(MAKEINTRESOURCE(IDR_WAVE4), NULL, SND_RESOURCE | SND_ASYNC );

			gameGo = false;
			gameOver = true;

			pX = body[0].first, pY = body[0].second;

			Sleep(70);

			SetPoint(pX, pY);
			cout << "@";

			SetPoint(55, 17);
			cout << "GAME  OVER";

			SetPoint(55, 18);
			cout <<"SCORE: " << score;
		}

		if (body.size() >= 4) {
			for (int i = 5; i < body.size(); i++)
			{
				if ((body[0].first == body[i].first) && (body[0].second == body[i].second)) {
					gameGo = false;
					gameOver = true;

					PlaySound(MAKEINTRESOURCE(IDR_WAVE4), NULL, SND_RESOURCE | SND_ASYNC );

					pX = body[0].first, pY = body[0].second;

					Sleep(70);

					SetPoint(pX, pY);
					cout << "@";

					SetPoint(55, 17);
					cout << "GAME OVER";

					SetPoint(55, 18);
					cout << "SCORE: " << score;
				}
			}
		}
	}
}

void Snake::DrawApple()
{
	bool onSnake = true;
	while (onSnake)
	{
		obj.apple.insert(obj.apple.begin(), make_pair(3 + rand() % 113, 3 + rand() % 29)); 
		for (int i = 0; i < body.size(); i++)
		{
			if ((obj.apple[0].first == body[i].first) && (obj.apple[0].second == body[i].second)) {
				obj.apple.pop_back();
				obj.apple.insert(obj.apple.begin(), make_pair(3 + rand() % 113, 3 + rand() % 29));
			}
			else {
				onSnake = false;
			}
		}
	}

	SetPoint(obj.apple.back().first, obj.apple.back().second);
	cout << "o";
}

void Snake::DrawBonus()
{
	srand(time(NULL));

	this_thread::sleep_for(20ms);

	bool onSnake = true;
	while (onSnake)
	{
		obj.bonus.push_back(make_pair(3 + rand() % 113, 3 + rand() % 29));
		for (int i = 0; i < body.size(); i++)
		{
			if ((obj.bonus[0].first == body[i].first) && (obj.bonus[0].second == body[i].second)) {
				obj.bonus.pop_back();
				obj.bonus.push_back(make_pair(3 + rand() % 113, 3 + rand() % 29));
			}
			else if ((obj.bonus[0].first == obj.apple[0].first) && (obj.bonus[0].second == obj.apple[0].second)) {
				obj.bonus.pop_back();
				obj.bonus.push_back(make_pair(3 + rand() % 113, 3 + rand() % 29));
			}
			else {
				onSnake = false;
			}
		}
	}

	SetPoint(obj.bonus[0].first, obj.bonus[0].second);
	cout << "$";

	bonus = true;

	Sleep(5000);

	SetPoint(obj.bonus[0].first, obj.bonus[0].second);
	cout << " ";

	for (int i = 0; i < body.size(); i++)
	{
		if ((obj.bonus[0].first == body[i].first) && (obj.bonus[0].second == body[i].second))
		{
			SetPoint(obj.bonus[0].first, obj.bonus[0].second);
			cout << "*";
		}
	}

	bonus = false;

	obj.bonus.clear();
}

void Snake::ObjTh()
{
	thread objBonus(&Snake::DrawBonus, this);
	objBonus.detach();
}

void Snake::ClearSnake()
{
	SetPoint(body.back().first, body.back().second);
	cout << " ";

	body.pop_back();
}

void Snake::Score()
{
	SetPoint(20, 36);
	cout << score;
}

void Snake::HotKeys()
{
	while (!gameOver)
	{
		this_thread::sleep_for(25ms);
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			gameGo = false;
			gameOver = true;
		}
		else if (GetAsyncKeyState(0x52) & 0x8000) {
			gameGo = false;
			restart = true;
		}
		else if (GetAsyncKeyState(0x50)) {
			pause = !pause;
			Sleep(50);
		}
	}
}

void Snake::ThHotKeys()
{
	thread hotKeys(&Snake::HotKeys, this);
	hotKeys.detach();
}

void Snake::LevelMenu()
{
	bool contChoose = true;

	SetPoint(55, 13);
	cout << "1 - EASY";
	SetPoint(55, 15);
	cout << "2 - MEDIUM";
	SetPoint(55, 17);
	cout << "3 - HARD";

	do
	{
		if (GetAsyncKeyState(0x31) & 0x8000) {
			SetPoint(50, 15);
			cout << "YOU CHOOSE EASY MODE";
			contChoose = false;
			SetPoint(55, 13);
			cout << "        ";
			SetPoint(55, 17);
			cout << "        ";

			difficulty = 60;

			SetPoint(102, 36);
			cout << "EASY";
		}

		if (GetAsyncKeyState(0x32) & 0x8000) {
			SetPoint(50, 15);
			cout << "YOU CHOOSE MEDIUM MODE";
			contChoose = false;
			SetPoint(55, 13);
			cout << "        ";
			SetPoint(55, 17);
			cout << "        ";

			difficulty = 45;

			SetPoint(102, 36);
			cout << "MEDIUM";
		}

		if (GetAsyncKeyState(0x33) & 0x8000) {
			SetPoint(50, 15);
			cout << "YOU CHOOSE HARD MODE";
			contChoose = false;
			SetPoint(55, 13);
			cout << "        ";
			SetPoint(55, 17);
			cout << "        ";

			difficulty = 30;

			SetPoint(102, 36);
			cout << "HARD";
		}

	} while (contChoose);

	Sleep(1200);

	SetPoint(50, 15);
	cout << "                      ";
}

void Snake::SnakeMove()
{
	gameGo = true, gameOver = false, restart = false, exit = false;

	keyState[3] = 1, keyState[0] = 0, keyState[1] = 0, keyState[2] = 0;

	score = 0, length = 1;
	x = 30, y = 15;

	LevelMenu();
	SnakeBody();
	DrawApple();
	Score();

	ThrOver();
	ThHotKeys();

	while (gameGo) {

		if (pause) {

			SetPoint(43, 38);
			cout << "PAUSED";

			while (pause) {}

			SetPoint(43, 38);
			cout << "      ";
		}

		SnakeBody();

		Sleep(difficulty);

		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			if (keyState[1] == 0) {
				keyState[0] = 1;
				keyState[2] = 0, keyState[3] = 0;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if (keyState[0] == 0) {
				keyState[1] = 1;
				keyState[2] = 0, keyState[3] = 0;
			}
		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			if (keyState[3] == 0) {
				keyState[2] = 1;
				keyState[0] = 0, keyState[1] = 0;
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			if (keyState[2] == 0) {
				keyState[3] = 1;
				keyState[0] = 0, keyState[1] = 0;
			}
		}

		if (keyState[0] == 1) {
			y--;
		}
		else if (keyState[1] == 1) {
			y++;
		}
		else if (keyState[2] == 1) {
			x--;
		}
		else if (keyState[3] == 1) {
			x++;
		}
		// MoveSettings ^

		if ((body[0].first == obj.apple[0].first) && (body[0].second == obj.apple[0].second)) {
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC );
			body.insert(body.begin(), make_pair(obj.apple[0].first, obj.apple[0].second));

			obj.apple.pop_back();
			DrawApple();

			score += 20;
			Score();

			length++;

			if (length % 15 == 0) {
				ObjTh();
			}
		}
		// Apple eating ^

		if (bonus) {
			if ((body[0].first == obj.bonus[0].first) && (body[0].second == obj.bonus[0].second)) {
				PlaySound(MAKEINTRESOURCE(IDR_WAVE3), NULL, SND_RESOURCE | SND_ASYNC );
				score += 400;
				Score();

				bonus = false;
			}
		}

		ClearSnake();
	}

	if (gameOver) {
		while (!GetAsyncKeyState(0x52)) {
			if (GetAsyncKeyState(VK_ESCAPE)) {
				break;
			}
		}
	}

	if (restart) {
		gameOver = true;
		Sleep(500);
	}

	Sleep(150);

	body.clear();
	obj.apple.clear();
	obj.bonus.clear();
}

