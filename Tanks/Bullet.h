#pragma once
#include"GameObject.h"
#include"Card.h"

class Bullet
{
protected:

	BULLET bullet_;

	unsigned short bulletDamag_;

	friend class Motion;


public:

	Bullet() {
		bullet_.coordBullet_.x_ = 0;
		bullet_.coordBullet_.y_ = 0;
		bulletDamag_ = 8;

	}

	Bullet(TANK Tank, unsigned short damage) {

		switch (Tank.directTank_) {
		case UP:
			bullet_.coordBullet_.x_ = Tank.coordTank_.y_;
			bullet_.coordBullet_.y_ = Tank.coordTank_.x_ - 1;
			break;

		case DOWN:
			bullet_.coordBullet_.x_ = Tank.coordTank_.y_;
			bullet_.coordBullet_.y_ = Tank.coordTank_.x_ + 1;
			break;

		case LEFT:
			bullet_.coordBullet_.x_ = Tank.coordTank_.y_ - 1;
			bullet_.coordBullet_.y_ = Tank.coordTank_.x_;
			break;

		case RIGHT:
			bullet_.coordBullet_.x_ = Tank.coordTank_.y_ + 1;
			bullet_.coordBullet_.y_ = Tank.coordTank_.x_;
			break;
		}
		bulletDamag_ = damage;
	}
};
