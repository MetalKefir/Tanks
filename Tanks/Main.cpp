#include"Game.h"
#include"menu.h"

int main() {
	
	setlocale(LOCALE_ALL, "");
	system("mode con cols=130 lines=70");

	Game game;
	GameDescription description;

	initializer_list<Items> list_init{
		{ "Начать игру",&game,&Game::Start },

		{ "О игре", 2 },
		{ "Управление",&description,&GameDescription::GameControl },
		{ "Правила",&description,&GameDescription::GameInform },

		{ "Настроки", 1},

		{ "Сложность", 4 },
		{ "Просто",&game,&Game::SetEasilyMod },
		{ "Средений",&game,&Game::SetAverageMod },
		{ "Тяжело",&game,&Game::SetHardMod },
		{ "ОДИН ВЫСТРЕЛ",&game,&Game::SetOneGunMod },

		{ "Выйти",&game,&Game::Exit },
	};

	Menu MainMenu("Main menu");

	FillMenu(MainMenu, FillVector(list_init));
	SetColor(Cyan);
	

	while (true)
	{
		MainMenu.MenuControl();
	}
}