#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

using namespace std;

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
// base classes ---------------------------------
class Actor : public GraphObject {

public:

	Actor(int imageID, int x, int y, int depth, StudentWorld* world, char type) :
		GraphObject(imageID, x, y, 0, depth) {

		m_world = world;

	}

	virtual void doSomething() = 0;
	virtual void setAlive();
	virtual bool isAlive();

	StudentWorld* getWorld() {
		return m_world;
	}

	char getType() {

		return m_type;

	}

private:
	StudentWorld* m_world;
	char m_type;

};

class Item : public Actor {

public:
	Item(int imageID, int x, int y, int depth, StudentWorld* world, char type) :
		Actor(imageID, x, y, depth, world, type), m_alive(true) {}; //constuctor that gives default direction

	Item(int imageID, int x, int y, int depth, int dir, StudentWorld* world, char type) : //constructor that allows for direction defined at construction
		Actor(imageID, x, y, depth, world, type), m_alive(true)
	{
		this->setDirection(dir);
	};
	bool isAlive() {
		return m_alive;
	};
	void setAlive() {
		m_alive = !m_alive;
	};
	virtual void doSomething() = 0;


private:
	bool m_alive;

};

class Person : public Item {

public:
	Person(int imageID, int x, int y, StudentWorld* world, char type) :
		Item(imageID, x, y, 0, world, type), m_infStatus(false), m_infCount(0) {};
	int getInfStatus() {
		return m_infStatus;
	};
	int getInfCount() {
		return m_infCount;
	};
	void setInfCount(int count) {
		m_infCount = count;
	};
	virtual void doSomething() = 0;



private:
	bool m_infStatus;
	int m_infCount;

};

class Zombie : public Item {

public:
	Zombie(int imageID, int x, int y, StudentWorld* world, char type) :
		Item(imageID, x, y, 0, world, type), m_movePlan(0) {};
	virtual void doSomething() = 0;


private:
	int m_movePlan;

};

//Classes derived from Actor ---------------------------

class Wall : public Actor {

public:
	Wall(int x, int y, StudentWorld* world) :
		Actor(IID_WALL, x, y, 0, world, '#') {};

	void doSomething();

};

class Pit : public Actor {

public:
	Pit(int x, int y, StudentWorld* world) :
		Actor(IID_PIT, x, y, 0, world, 'O') {};


	void doSomething();

};

class Exit : public Actor {

public:
	Exit(int x, int y, StudentWorld* world) :
		Actor(IID_EXIT, x, y, 1, world, 'X') {};

	void doSomething();

};

//Classes derived from Item --------------------------- Item(int imageID, int x, int y, int depth)

class Flame : public Item {

public:
	Flame(int x, int y, int dir, StudentWorld* world) : //dir given at construction
		Item(IID_FLAME, x, y, 0, dir, world, 'F') {};

	void doSomething();

};

class Vomit : public Item {

public:
	Vomit(int x, int y, int dir, StudentWorld* world) : //dir given at construction
		Item(IID_VOMIT, x, y, 0, dir, world, 'T') {};

	void doSomething();

};

class VaccineGoodie : public Item {

public:
	VaccineGoodie(int x, int y, StudentWorld* world) :
		Item(IID_VACCINE_GOODIE, x, y, 1, world, 'V') {};

	void doSomething();

};

class GasCanGoodie : public Item {

public:
	GasCanGoodie(int x, int y, StudentWorld* world) :
		Item(IID_GAS_CAN_GOODIE, x, y, 1, world, 'G') {};

	void doSomething();

};

class LandmineGoodie : public Item {

public:
	LandmineGoodie(int x, int y, StudentWorld* world) :
		Item(IID_LANDMINE_GOODIE, x, y, 1, world, 'L') {};

	void doSomething();

};

class Landmine : public Item {

public:
	Landmine(int x, int y, StudentWorld* world) :
		Item(IID_LANDMINE, x, y, 1, world, 'B'), m_safetyTicks(30), m_inactive(false) {};

	void doSomething();

private:
	int m_safetyTicks;
	bool m_inactive;


};

//classes derived from Zombie -------------- Zombie(int imageID, int x, int y)

class DumbZombie : public Zombie {

public:
	DumbZombie(int x, int y, StudentWorld* world) :
		Zombie(IID_ZOMBIE, x, y, world, 'D') {};

	void doSomething();

};

class SmartZombie : public Zombie {

public:
	SmartZombie(int x, int y, StudentWorld* world) :
		Zombie(IID_ZOMBIE, x, y, world, 'S') {};

	void doSomething();

};

//classes derived from Person -------------- Person(int imageID, int x, int y)

class Penelope : public Person {

public:
	Penelope(int x, int y, StudentWorld* world) :
		Person(IID_PLAYER, x, y, world, '@'), m_landmineCount(0), m_flameCount(0), m_vaccineCount(0) {};

	void doSomething();

private:
	int m_landmineCount;
	int m_flameCount;
	int m_vaccineCount;

};

class Citizen : public Person {

public:
	Citizen(int x, int y, StudentWorld* world) :
		Person(IID_CITIZEN, x, y, world, 'C') {};

	void doSomething();

};

#endif // ACTOR_H_
