#include "Actor.h"
#include "StudentWorld.h"
#include <list>

using namespace std;

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

	int x = getX();
	int y = getY();

	if (this->getWorld()->getKey(ch)) {

		switch (ch) {

		case KEY_PRESS_UP:
			setDirection(up);
			if (!(this->getWorld()->contains(x, y + SPRITE_HEIGHT / 2 + 1, '#'))) {
				moveTo(getX(), getY() + 1);
			}
			//else cout << "collide" << endl;
			break;

		case KEY_PRESS_DOWN:
			setDirection(down);
			if (!(this->getWorld()->contains(x, y - SPRITE_HEIGHT / 2 - 1, '#'))) {
				moveTo(getX(), getY() - 1);
			}
			break;

		case KEY_PRESS_RIGHT:
			setDirection(right);
			if (!(this->getWorld()->contains(x + SPRITE_WIDTH / 2 + 1, y, '#'))) {
				moveTo(getX() + 1, getY());
			}
			break;

		case KEY_PRESS_LEFT:
			setDirection(left);
			if (!(this->getWorld()->contains(x - SPRITE_WIDTH / 2 - 1, y, '#'))) {
				moveTo(getX() - 1, getY());
			}
			break;

		}

	}

}

void Wall::doSomething() {

	return;

}

void Exit::doSomething() {

	int thisX = this->getX();
	int thisY = this->getY();

	Actor* temp = this->getWorld()->overlap(thisX, thisY, '@');
	//list<Actor*> tempList = this->getWorld()->getObjList();

	if (temp != nullptr) {

		if (this->getWorld()->citizenDead()) this->getWorld()->setLevelFinish();

	}

	temp = this->getWorld()->overlap(thisX, thisY, 'C');

	if (temp != nullptr) {
		//add 500 points
		temp->setAlive(); //kill the citizen
		this->getWorld()->playSound(SOUND_CITIZEN_SAVED);
	}

}