#pragma once
#include"Bullet.h"


class Motion
{
protected:

	static void bullet_down(Bullet &bullet, unsigned short &targetHP) {
		
		while (Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_] != WALL::symbolWall_) {

			Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_] = BULLET::symbolBullet_;

			this_thread::sleep_for(chrono::milliseconds(160));

			Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_] = ' ';

			if (Card_[bullet.bullet_.coordBullet_.y_+1][bullet.bullet_.coordBullet_.x_] == WALL::symbolWall_)
			{
				Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_] = ' ';
				return;
			}
			if (Card_[bullet.bullet_.coordBullet_.y_+1][bullet.bullet_.coordBullet_.x_] == TANK::symbolTank_) {
				targetHP -= bullet.bulletDamag_;
				return;
			}

			bullet.bullet_.coordBullet_.y_++;
			}
	}

	static void bullet_up(Bullet &bullet, unsigned short &targetHP) {

		while (Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_] != WALL::symbolWall_) {

			Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_] = BULLET::symbolBullet_;

			this_thread::sleep_for(chrono::milliseconds(160));

			Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_] = ' ';

			if (Card_[bullet.bullet_.coordBullet_.y_-1][bullet.bullet_.coordBullet_.x_] == WALL::symbolWall_)
			{
				Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_] = ' ';
				return;
			}
			if (Card_[bullet.bullet_.coordBullet_.y_-1][bullet.bullet_.coordBullet_.x_] == TANK::symbolTank_) {
				targetHP -= bullet.bulletDamag_;
				return;
			}

			bullet.bullet_.coordBullet_.y_--;
		}
	}

	static void bullet_right(Bullet &bullet, unsigned short &targetHP) {

		while (Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_] != WALL::symbolWall_) {

			Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_] = BULLET::symbolBullet_;

			this_thread::sleep_for(chrono::milliseconds(160));

			Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_] = ' ';

			if (Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_+1] == WALL::symbolWall_)
			{
				Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_] = ' ';
				return;
			}
			if (Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_+1] == TANK::symbolTank_) {
				targetHP -= bullet.bulletDamag_;
				return;
			}

			bullet.bullet_.coordBullet_.x_++;
		
		}
	}
	
	static void bullet_left(Bullet &bullet, unsigned short &targetHP) {

		while (Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_] != WALL::symbolWall_) {

			Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_] = BULLET::symbolBullet_;

			this_thread::sleep_for(chrono::milliseconds(160));

			Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_] = ' ';

			if (Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_-1] == WALL::symbolWall_)
			{
				Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_] = ' ';
				return;
			}
			if (Card_[bullet.bullet_.coordBullet_.y_][bullet.bullet_.coordBullet_.x_-1] == TANK::symbolTank_) {
				targetHP -= bullet.bulletDamag_;
				return;
			}

			bullet.bullet_.coordBullet_.x_--;
		}
	}


	static void move_down(const Coord &coord) {

		for (unsigned short i = coord.x_ - 1; i <= coord.x_ + 1; i++)
			for (unsigned short j = coord.y_ - 1; j <= coord.y_ + 1; j++)
				(i == coord.x_ + 1 && j == coord.y_) ? Card_[i][j] = ' ' : Card_[i][j] = TANK::symbolTank_;
	}
	
	static void move_up(const Coord &coord) {

		for (unsigned short i = coord.x_ - 1; i <= coord.x_ + 1; i++)
			for (unsigned short j = coord.y_ - 1; j <= coord.y_ + 1; j++)
				(i == coord.x_ - 1 && j == coord.y_) ? Card_[i][j] = ' ' : Card_[i][j] = TANK::symbolTank_;
	}

	static void move_left(const Coord &coord) {

		for (unsigned short i = coord.x_ - 1; i <= coord.x_ + 1; i++)
			for (unsigned short j = coord.y_ - 1; j <= coord.y_ + 1; j++)
				(i == coord.x_ && j == coord.y_ - 1) ? Card_[i][j] = ' ' : Card_[i][j] = TANK::symbolTank_;
	}

	static void move_right(const Coord &coord) {

		for (unsigned short i = coord.x_ - 1; i <= coord.x_ + 1; i++)
			for (unsigned short j = coord.y_ - 1; j <= coord.y_ + 1; j++)
				(i == coord.x_ && j == coord.y_+1) ? Card_[i][j] = ' ' : Card_[i][j] = TANK::symbolTank_;	
	}


	static void clear(const Coord &coord) {

		for (unsigned short i = coord.x_ - 1; i <= coord.x_ + 1; i++)
			for (unsigned short j = coord.y_ - 1; j <= coord.y_ + 1; j++)
					Card_[i][j] = ' ';
	}

public:
	Motion(){}
};