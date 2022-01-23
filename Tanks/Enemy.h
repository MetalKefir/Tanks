#pragma once

#include"Tank.h"


class Enemy : public Tank
{

private:

	void lee(Coord coord, vector<Coord> &road) {

		int distanse = (coord.x_ - Tank_.coordTank_.x_) + (coord.y_ - Tank_.coordTank_.y_);
		abs(distanse);

		int dx = (coord.x_ - Tank_.coordTank_.x_);
		int dy = (coord.y_ - Tank_.coordTank_.y_);

		unsigned x = Tank_.coordTank_.x_;
		unsigned y = Tank_.coordTank_.y_;

		do
		{

			if (dx < 0) {
				while (dx != 0) {
					road.push_back(*(new Coord(x - 1, y)));
					dx++;
					x--;
				}
			}

			if (dx > 0) {
				while (dx != 0) {
					road.push_back(*(new Coord(x + 1, y)));
					dx--;
					x++;
				}
			}

			if (dy < 0) {
				while (dy != 0) {
					road.push_back(*(new Coord(x, y - 1)));
					dy++;
					y--;
				}
			}

			if (dy > 0) {
				while (dy != 0) {
					road.push_back(*(new Coord(x, y + 1)));
					dy--;
					y++;
				}
			}
			distanse--;
		} while (distanse > 0);
	}

public:
	Enemy() :Tank() {
	
	
	};

	Enemy(int x, int y) :Tank(x,y) {};


	void motion(bool &GameTrig, Tank &target) {

		vector<Coord> road;
		short Step=6;

			Coord finish = target.Tank_.coordTank_;

			lee(finish, road);

			for (vector<Coord>::iterator it = road.begin(); it < road.end() && Step>0 && GameTrig; it++) {

				if (Tank_.coordTank_.x_ > it->x_) // фиксируем нажатие кнопки.
				{
					if (TestWay(UP))
					{
						clear(Tank_.coordTank_);

						Tank_.coordTank_.x_--;
						move_up(Tank_.coordTank_);

						Tank_.directTank_ = UP;

						gan = bullet_up;

						Step--;
					}

					for (int i = Tank_.coordTank_.x_-1; i < Tank_.coordTank_.x_ - 15; i++) {
						if (Card_[i][Tank_.coordTank_.y_] == TANK::symbolTank_) {
							Bullet *bullet = new Bullet(Tank_, tankDamag_);

							Step_ = 0;

							thread bull(Tank::gan, *bullet, ref(target.HP_));
							if (bull.joinable()) bull.detach();

							return;
						}
					}
				}
				this_thread::sleep_for(chrono::milliseconds(120));

				if (Tank_.coordTank_.x_ < it->x_) // фиксируем нажатие кнопки.
				{
					if (TestWay(DOWN))
					{
						clear(Tank_.coordTank_);

						Tank_.coordTank_.x_++;
						move_down(Tank_.coordTank_);

						Tank_.directTank_ = DOWN;

						gan = bullet_down;

						Step--;
					}

					for (int i = Tank_.coordTank_.x_+1; i < Tank_.coordTank_.x_ + 15; i++) {
						if (Card_[i][Tank_.coordTank_.y_] == TANK::symbolTank_) {
							Bullet *bullet = new Bullet(Tank_, tankDamag_);

							Step_ = 0;

							thread bull(Tank::gan, *bullet, ref(target.HP_));
							if (bull.joinable()) bull.detach();

							return;
						}
					}

				}
				this_thread::sleep_for(chrono::milliseconds(120));

				if (Tank_.coordTank_.y_ > it->y_) // фиксируем нажатие кнопки.
				{
					if (TestWay(LEFT))
					{
						clear(Tank_.coordTank_);

						Tank_.coordTank_.y_--;
						move_left(Tank_.coordTank_);

						Tank_.directTank_ = LEFT;

						gan = bullet_left;

						Step--;
					}

					for (int i = Tank_.coordTank_.y_-1; i < Tank_.coordTank_.y_ - 15; i++) {
						if (Card_[Tank_.coordTank_.x_][i] == TANK::symbolTank_) {
							Bullet *bullet = new Bullet(Tank_, tankDamag_);

							Step_ = 0;

							thread bull(Tank::gan, *bullet, ref(target.HP_));
							if (bull.joinable()) bull.detach();

							return;
						}
					}
				}
				this_thread::sleep_for(chrono::milliseconds(120));

				if (Tank_.coordTank_.y_ < it->y_) // фиксируем нажатие кнопки.
				{
					if (TestWay(RIGHT))
					{
						clear(Tank_.coordTank_);

						Tank_.coordTank_.y_++;
						move_right(Tank_.coordTank_);

						Tank_.directTank_ = RIGHT;

						gan = bullet_right;

						Step--;
					}

					for (int i = Tank_.coordTank_.y_+1; i < Tank_.coordTank_.y_ + 15; i++) {
						if (Card_[Tank_.coordTank_.x_][i] == TANK::symbolTank_) {
							Bullet *bullet = new Bullet(Tank_, tankDamag_);

							Step_ = 0;

							thread bull(Tank::gan, *bullet, ref(target.HP_));
							if (bull.joinable()) bull.detach();

							return;
						}
					}
				}
				this_thread::sleep_for(chrono::milliseconds(120));
			}
		}
};