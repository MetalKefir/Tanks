#pragma once
#include"GameInfo.h"

class Game
{

private:

	Tank *player;
	Enemy *enemy;

	bool GameTrig;
	bool WIN;
	bool LOSE;

	void render(bool &GameTrig) {
		while (GameTrig) {
			this_thread::sleep_for(chrono::milliseconds(80));
			setcur();
			for (int i = 0; i < SizeY_; i++) {
				for (int j = 0; j < SizeX_; j++) {

					if (Card_[i][j] == WALL::symbolWall_) SetColor(WALL::colorWall_);
					if (Card_[i][j] == TANK::symbolTank_) SetColor(TANK::colorTank_);
					if (Card_[i][j] == BULLET::symbolBullet_) SetColor(BULLET::colorBullet_);

					cout << Card_[i][j];
				}
				cout << endl;
			}
			cout << endl;
			GameInfo(*player, *enemy);
		}
		
	}
	
public:
	void Start() {
		GameTrig = true;
		thread rend = thread(&Game::render, *this, ref(GameTrig));
		if (rend.joinable()) rend.detach();
		thread exit = thread(&Game::ExitGame, *this, ref(GameTrig));
		if (exit.joinable()) exit.detach();

		while (GameTrig) {
			player->motion(GameTrig, *enemy);
			enemy->motion(GameTrig, *player);
		}
		Sleep(1000);
		AnalizGame();
		Rezult();
	}

	void AnalizGame() {
		if (enemy->HP_ == 0) {
			GameTrig = false;
			WIN = true;
		}

		if (player->HP_ == 0) {
			GameTrig = false;
			LOSE = true;
		}
	}

	void ExitGame(bool &GameTrig) {
		while (GameTrig)
		{
			if (GetAsyncKeyState(VK_END) || enemy->HP_ == 0 || player->HP_ == 0) {
				keybd_event(VK_END, 0, KEYEVENTF_KEYUP, 0);
				GameTrig = false;
			}
		}
	}

	void Exit() {
		setcur(50, 35);
		cout << "ÏÎÊÀ.";

		delete player;
		delete enemy;

		Sleep(2000); 
		exit(0); 
	}
		
	void Rezult() {
		setcur();
		system("cls");
		SetColor(Cyan);

		if (WIN) {
			setcur(50, 35);
			cout << "ÊÎÍÅÖ ÈÃÐÛ";
			setcur(50, 36);
			cout << "ÒÛ ÏÎÁÅÄÈË\n";
		}

		if (LOSE) {
			setcur(50, 35);
			cout << "ÊÎÍÅÖ ÈÃÐÛ";
			setcur(50, 36);
			cout << "ÒÛ ÏÐÎÈÃÐÀË\n";
		}

		if (!WIN && !LOSE) {
			setcur(50, 35);
			cout << "    ÂÛ ÂÛØËÈ ÈÇ ÈÃÐÛ";
			setcur(50, 36);
			cout << "ÑÅÉ×ÀÑ ÂÀÑ ÂÅÐÍÅÒ Â ÌÅÍÞ";
		}

		Sleep(2000);
		Regame();
	}

	void Regame() {
		Motion::clear(player->Tank_.coordTank_);
		player->Tank_.coordTank_.x_ = 50;
		player->Tank_.coordTank_.y_ = 60;
		player->move_down(player->Tank_.coordTank_);

		Motion::clear(enemy->Tank_.coordTank_);
		enemy->Tank_.coordTank_.x_ = 10;
		enemy->Tank_.coordTank_.y_ = 5;
		enemy->move_down(enemy->Tank_.coordTank_);

		player->HP_ = 30;
		player->tankDamag_ = 10;

		enemy->HP_ = 30;
		enemy->tankDamag_ = 10;

	}

	void SetEasilyMod() {
		player->HP_ = 30;
		player->tankDamag_ = 10;

		enemy->HP_ = 20;
		enemy->tankDamag_ = 5;

		cout << "Âûáðàí ëåêãèé óðîâåíü ñëîæíîñòè\n\n";
		system("PAUSE");
	}

	void SetAverageMod() {
		player->HP_ = 30;
		player->tankDamag_ = 10;

		enemy->HP_ = 30;
		enemy->tankDamag_ = 10;

		cout << "Âûáðàí ñðåäíèé óðîâåíü ñëîæíîñòè\n\n";
		system("PAUSE");
	}

	void SetHardMod() {
		player->HP_ = 20;
		player->tankDamag_ = 5;

		enemy->HP_ = 30;
		enemy->tankDamag_ = 10;

		cout << "Âûáðàí òÿæåëûé óðîâåíü ñëîæíîñòè\n\n";
		system("PAUSE");
	}

	void SetOneGunMod() {
		player->HP_ = 1;
		player->tankDamag_ = 10;

		enemy->HP_ = 50;
		enemy->tankDamag_ = 1;

		cout << R"("Âûáðàí "îäèí âûñòðåë" óðîâåíü ñëîæíîñòè)"<<endl<<endl;
		system("PAUSE");
	}


	Game()
	{
		for (int i = 0; i < SizeY_; i++)
			for (int j = 0; j < SizeX_; j++)
				if (MaskCard_[i][j]) Card_[i][j] = WALL::symbolWall_;

		player = new Tank(50,60);
		enemy = new Enemy(10, 5);

		WIN = false;
		LOSE = false;
	}
};