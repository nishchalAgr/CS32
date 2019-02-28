#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <string>
#include <list>

class Actor;
class Penelope;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetPath);
	~StudentWorld() { cleanUp(); };
	virtual int init();
	virtual int move();
	virtual void cleanUp();
	bool contains(int x, int y);
	std::list<Actor*> getObjList(); //access the objList
	//bool StudentWorld::overlaps(int x, int y, char startType, char type);

private:
	std::list<Actor*> m_objList;
	Penelope* m_player;

};

#endif // STUDENTWORLD_H_
