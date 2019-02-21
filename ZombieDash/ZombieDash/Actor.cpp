#include "Actor.h"
#include "StudentWorld.h"
#include <list>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
//
//IID_PLAYER(for Penelope)
//IID_ZOMBIE(for both smart	and	dumb zombies)
//IID_CITIZEN
//IID_FLAME
//IID_VOMIT
//IID_PIT
//IID_LANDMINE(for a deployed landmine)
//IID_VACCINE_GOODIE
//IID_GAS_CAN_GOODIE
//IID_LANDMINE_GOODIE
//IID_EXIT
//IID_WALL


void Penelope::doSomething() {

	if (isAlive() == false) return;

	if (getInfStatus()) setInfCount(getInfCount() + 1);

	else if (getInfCount() == 500) {

		setAlive();

		this->getWorld()->playSound(SOUND_PLAYER_DIE);

		return;

	}

	int ch;

	if (this->getWorld()->getKey(ch)) {

		switch (ch) {

		case KEY_PRESS_UP:
			if (!(this->getWorld()->contains(getX(), SPRITE_HEIGHT/2 + (getY() + 1)))) {
				setDirection(up);
				moveTo(getX(), getY() + 1);
			}
			break;

		case KEY_PRESS_DOWN:
			if (!(this->getWorld()->contains(getX(), -SPRITE_HEIGHT/2 + (getY() - 1)))) {
				setDirection(down);
				moveTo(getX(), getY() - 1);
			}
			break;

		case KEY_PRESS_RIGHT:
			if (!(this->getWorld()->contains(SPRITE_WIDTH/2 + (getX() + 1),getY()))) {
				setDirection(right);
				moveTo(getX() + 1, getY());
			}
			break;

		case KEY_PRESS_LEFT:
			if (!(this->getWorld()->contains(-SPRITE_WIDTH/2 + (getX() - 1),getY()))) {
				setDirection(left);
				moveTo(getX() - 1, getY());
			}
			break;

		}

	}

}

void Wall::doSomething() {

	return;

}