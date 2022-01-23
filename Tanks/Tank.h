#pragma once
#include<vector>
#include<cmath>
#include"Motion.h"

class Tank : public Motion
{
protected:

	TANK Tank_;
	
	unsigned short HP_;
	unsigned short tankDamag_;
	
	void (*gan)(Bullet &, unsigned short &);

	static const short MAX_Step_ = 5;

	unsigned short Step_;

	friend class Enemy;
	friend class Game;

	friend void GameInfo(Tank &player, Enemy &enemy);

	bool TestWay(Direction direct) {
		bool TrigWay = true;
		switch (direct)
		{
		case UP:
			for (int i = Tank_.coordTank_.y_ - 1; i < Tank_.coordTank_.y_ + 1 && TrigWay; i++)
				TrigWay = Card_[Tank_.coordTank_.x_ - 2][i] != WALL::symbolWall_ && Card_[Tank_.coordTank_.x_ - 3][i] != TANK::symbolTank_;
			break;

		case DOWN:
			for (int i = Tank_.coordTank_.y_ - 1; i < Tank_.coordTank_.y_ + 1 && TrigWay; i++)
				TrigWay = Card_[Tank_.coordTank_.x_ + 2][i] != WALL::symbolWall_;
			break;

		case LEFT:
			for (int i = Tank_.coordTank_.x_ - 1; i < Tank_.coordTank_.x_ + 1 && TrigWay; i++)
				TrigWay = Card_[i][Tank_.coordTank_.y_ - 2] != WALL::symbolWall_ && Card_[i][Tank_.coordTank_.y_ - 3] != TANK::symbolTank_;
			break;

		case RIGHT:
			for (int i = Tank_.coordTank_.x_ - 1; i < Tank_.coordTank_.x_ + 1 && TrigWay; i++)
				TrigWay = Card_[i][Tank_.coordTank_.y_ + 2] != WALL::symbolWall_ && Card_[i][Tank_.coordTank_.y_ + 3] != TANK::symbolTank_;
			break;
		}

		return TrigWay;
	};

public:

	Tank(){

		tankDamag_ = 10;
		HP_ = 30;
		
		move_down(Tank_.coordTank_);
		gan = bullet_down;
	};

	Tank(int x, int y) {
		Tank_.coordTank_.x_ = x;
		Tank_.coordTank_.y_ = y;
		
		tankDamag_ = 10;
		HP_ = 30;

		move_down(Tank_.coordTank_);
		Tank_.directTank_ = DOWN;
		gan = bullet_down;
	};

	void motion(bool &GameTrig, Tank &target) {

		for (Step_ = MAX_Step_; Step_ > 0 && GameTrig;) {

			if (GetAsyncKeyState(VK_UP)) // фиксируем нажатие кнопки.
			{
				keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0); // "отжимаем" кнопку. 

				if (TestWay(UP)){

					clear(Tank_.coordTank_);

					Tank_.coordTank_.x_--;
					move_up(Tank_.coordTank_);

					Tank_.directTank_ = UP;

					gan = bullet_up;	

					Step_--;
				}
			}
			

			if (GetAsyncKeyState(VK_DOWN)) // фиксируем нажатие кнопки.
			{
				keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0); // "отжимаем" кнопку. 

				if (TestWay(DOWN)){

					clear(Tank_.coordTank_);

					Tank_.coordTank_.x_++;
					move_down(Tank_.coordTank_);

					Tank_.directTank_ = DOWN;

					gan = bullet_down;

					Step_--;
				}
			}
			

			if (GetAsyncKeyState(VK_LEFT)) // фиксируем нажатие кнопки.
			{
				keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0); // "отжимаем" кнопку. 

				if (TestWay(LEFT)){

					clear(Tank_.coordTank_);

					Tank_.coordTank_.y_--;
					move_left(Tank_.coordTank_);

					Tank_.directTank_ = LEFT;

					gan = bullet_left;	

					Step_--;
				}
			}
			

			if (GetAsyncKeyState(VK_RIGHT)) // фиксируем нажатие кнопки.
			{
				keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0); // "отжимаем" кнопку. 

				if (TestWay(RIGHT)){

					clear(Tank_.coordTank_);

					Tank_.coordTank_.y_++;
					move_right(Tank_.coordTank_);

					Tank_.directTank_ = RIGHT;

					gan = bullet_right;

					Step_--;
					
				}
			}


			if (GetAsyncKeyState(VK_SHIFT)) // фиксируем нажатие кнопки.
			{
				keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0); // "отжимаем" кнопку. 

				Bullet *bullet;
				bullet = new Bullet(Tank_, tankDamag_);

				Step_ = 0;

				thread bull(Tank::gan, *bullet, ref(target.HP_));
				if (bull.joinable()) bull.detach();
				

			}
			this_thread::sleep_for(chrono::milliseconds(120));	
		}
	}
};