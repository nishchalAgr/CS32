#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
// base classes ---------------------------------
class Actor : public GraphObject {

public:
	Actor(int imageID, int x, int y, int depth) :
		GraphObject(imageID, x, y, 0, depth) {};

private:
	virtual void doSomething() = 0;

};

class Item : public Actor {

public:
	Item(int imageID, int x, int y, int depth) :
		Actor(imageID, x, y, depth), m_alive(true) {}; //constuctor that gives default direction

	Item(int imageID, int x, int y, int depth, int dir) : //constructor that allows for direction defined at construction
		Actor(imageID, x, y, depth), m_alive(true) 
	{
		this->setDirection(dir);
	};


private:
	bool m_alive;

};

class Person : public Item {

public:
	Person(int imageID, int x, int y) :
		Item(imageID, x, y, 0), m_infStatus(false), m_infCount(0) {};

private:
	bool m_infStatus;
	int m_infCount;

};

class Zombie : public Item {

public:
	Zombie(int imageID, int x, int y) :
		Item(imageID, x, y, 0), m_movePlan(0) {};

private:
	int m_movePlan;

};

//Classes derived from Actor ---------------------------

class Wall : public Actor {

public:
	Wall(int x, int y) :
		Actor(IID_WALL, x, y, 0){};

};

class Pit : public Actor {

public:
	Pit(int x, int y) :
		Actor(IID_PIT, x, y, 0) {};

};

class Exit : public Actor {

public:
	Exit(int x, int y) :
		Actor(IID_EXIT, x, y, 1) {};

};

//Classes derived from Item --------------------------- Item(int imageID, int x, int y, int depth)

class Flame : public Item {

public:
	Flame(int x, int y, int dir) : //dir given at construction
		Item(IID_FLAME, x, y, 0, dir) {};



};

class Vomit : public Item {

public:
	Vomit(int x, int y, int dir) : //dir given at construction
		Item(IID_VOMIT, x, y, 0, dir) {};

};

class VaccineGoodie : public Item {

public:
	VaccineGoodie(int x, int y) : 
		Item(IID_VACCINE_GOODIE, x, y, 1) {};

};

class GasCanGoodie : public Item {

public:
	GasCanGoodie(int x, int y) :
		Item(IID_GAS_CAN_GOODIE, x, y, 1) {};

};

class LandmineGoodie : public Item {

public:
	LandmineGoodie(int x, int y) :
		Item(IID_LANDMINE_GOODIE, x, y, 1) {};

};

class Landmine : public Item {

public:
	Landmine(int x, int y) :
		Item(IID_LANDMINE, x, y, 1) {}, m_safetyTicks(30), m_inactive(false);

private:
	int m_safetyTicks;
	bool m_inactive;

};

//classes derived from Zombie -------------- Zombie(int imageID, int x, int y)

class DumbZombie : public Zombie {

public:
	DumbZombie(int x, int y) :
		Zombie(IID_ZOMBIE, x, y) {};

};

class SmartZombie : public Zombie {

public:
	SmartZombie(int x, int y) :
		Zombie(IID_ZOMBIE, x, y) {};

};

//classes derived from Person -------------- Person(int imageID, int x, int y)

class Penelope : public Person {

public:
	Penelope(int x, int y) :
		Person(IID_PLAYER, x, y) {};

};

class Citizen : public Person {

public:
	Citizen(int x, int y) :
		Person(IID_CITIZEN, x, y) {};

};

#endif // ACTOR_H_
