#include"Game.h"
#include"menu.h"
#include <windows.h>

int main() {
	
	setlocale(LOCALE_ALL, "");
	system("mode con cols=130 lines=70");

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);

	Game game;
	GameDescription description;

	initializer_list<Items> list_init{
		{ "������ ����",&game,&Game::Start },

		{ "� ����", 2 },
		{ "����������",&description,&GameDescription::GameControl },
		{ "�������",&description,&GameDescription::GameInform },

		{ "��������", 1},

		{ "���������", 4 },
		{ "������",&game,&Game::SetEasilyMod },
		{ "��������",&game,&Game::SetAverageMod },
		{ "������",&game,&Game::SetHardMod },
		{ "���� �������",&game,&Game::SetOneGunMod },

		{ "�����",&game,&Game::Exit },
	};

	Menu MainMenu("Main menu");

	FillMenu(MainMenu, FillVector(list_init));
	SetColor(Cyan);
	

	while (true)
	{
		MainMenu.MenuControl();
	}
}