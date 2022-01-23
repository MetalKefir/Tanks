﻿#pragma once
#include"Enemy.h"
#include"GameObject.h"

 void GameInfo(Tank &player, Enemy &enemy) {
		
		setcur(SizeX_ + 5, 1);
		cout << "Осталось ходов: " << player.Step_;
		
		setcur(SizeX_ + 5, 3);
		cout << "Игрок:";
		setcur(SizeX_ + 5, 4);
		cout << "HP: " << setfill('0') << player.HP_;
		setcur(SizeX_ + 5, 5);
		cout << "Урон за выстрел: " << setfill('0') << player.tankDamag_;

		setcur(SizeX_ + 5, 7);
		cout << "Противник:";
		setcur(SizeX_ + 5, 8);
		cout << "HP: " << setfill('0') << setw(2) << enemy.HP_;
		setcur(SizeX_ + 5, 9);
		cout << "Урон за выстрел: " << setfill('0') << enemy.tankDamag_;
	}

 class GameDescription {



 public:
	 void GameControl() {
		 cout << "Управление осуществляется с помощью стрелок на клавиатуре,\n ↑(верх), ↓(низ), →(право), ←(лево).\n"
			  << "Стрельба SHIFT.\n\n";

		 system("PAUSE");
	 }

	 void GameInform() {
		 cout << "Процесс игры разбит на шаги.\n У игрока 5 шагов, нажатие любой клавиши движения тратить один ход, выстрел тратит все ходы.\n"
			  << "После этого происходит ход противника, у него будет 6 шагов. Он движется по кратчайшему пути и в конце концов вас догонит.\n";

		 cout << "\nДальность выстрела 6 клеток, снаряд летит не зависимо от ходов, так что вы можете сбежать с лини огня,\n да и противник тоже... наверное.\n";

		 cout << "\nИнформация об игре выводится справа от карты.\n"
			  << "Осталось ходов: количество оставшихся у вас ходов."
			  << "Игрок: информация об игроке\n  HP - здоровье\n Урон за выстрел - урон наносимы за один выстрел.\n\n"
			  << "Противник: информация о проивнике\n  HP - здоровье\n Урон за выстрел - урон наносимы за один выстрел.\n";

		 cout << "\nИгра завершится как только здоровье игрока или проивника упадет до 0.\n";

		 cout << "\nПриятной игры.\n\n";

		 system("PAUSE");
	 }
 };