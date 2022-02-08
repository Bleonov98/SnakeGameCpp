#include "World.h"

void World::SetPoint(int x, int y)
{
	sprintf_s(handCoord, "%s%d;%dH", CSI, y, x);
	printf(handCoord);
}

void World::End()
{
	while (!quit) {
		this_thread::sleep_for(10ms);
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			exit = true;
		}
		if (GetAsyncKeyState(0x52) & 0x8000) {
			exit = false;
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			skip = true;
		}
	}
}

void World::EndThread()
{
	thread end(&World::End, this);
	end.detach();
}

void World::DrawTitle()
{
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC );

	HRSRC hResource = FindResource(hInstance, MAKEINTRESOURCE(IDR_TEXT2), L"TEXT");

	if (hResource)
	{
		HGLOBAL hLoadedResource = LoadResource(hInstance, hResource);

		if (hLoadedResource)
		{
			LPCSTR title = (LPCSTR)LockResource(hLoadedResource);

			if (title)
			{
				DWORD dwResourceSize = SizeofResource(hInstance, hResource);

				if (0 != dwResourceSize)
				{
					int j = 0;
					int k = 1;
					for (int i = 0; i < 39; i++)
					{
						for (; j < 121 * k; j++)
						{
							cout << title[j];
						}
						k++;
						Sleep(20);
					}
				}
			}
		}
	}

	skip = false;

	while (!skip) {
		SetPoint(50, 30);
		cout << "PRESS ENTER TO START";
		Sleep(650);
		SetPoint(50, 30);
		cout << "                    ";
		Sleep(650);
	}

	system("cls");
}

void World::DrawArea()
{
	// Set console code page to UTF-8 so console known how to interpret string data
	SetConsoleOutputCP(CP_UTF8);

	// Enable buffering to prevent VS from chopping up UTF-8 byte sequences
	setvbuf(stdout, nullptr, _IOFBF, 1000);

	HRSRC hResource = FindResource(hInstance, MAKEINTRESOURCE(IDR_TEXT1), L"TEXT");

	if (hResource)
	{
		HGLOBAL hLoadedResource = LoadResource(hInstance, hResource);

		if (hLoadedResource)
		{
			LPCSTR area = (LPCSTR)LockResource(hLoadedResource);

			if (area)
			{
				DWORD dwResourceSize = SizeofResource(hInstance, hResource);

				if (0 != dwResourceSize)
				{
					for (int i = 0; i < strnlen(area, 5560); i++) {
						cout << area[i];
					}
				}
			}
		}
	}

	setvbuf(stdout, NULL, _IONBF, 0);
}

void World::InitAndRunWorld()
{
	srand(time(NULL));

	term.Terminal();
	term.SetScreenSize();
	term.ScreenBuf();

	printf(CSI "?1049h");
	printf(CSI "?25l");

	EndThread();

	while (!exit) {
		DrawTitle();
		DrawArea();

		sk.SnakeMove();

		system("cls");
	}

	quit = true;

	printf(CSI "?1049l");
}
