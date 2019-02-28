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

	bool contains(int x, int y, char type);
	Actor* overlap(int x, int y, char type);

	void setLevelFinish() {
	
		m_levelFinish = true;
		
	}

	bool citizenDead(); //returns whether or not all citizens are not alive

	//get coordinates of player
	int getPX();
	int getPY();

	//std::list<Actor> getObjList(); //access the objList
	//bool StudentWorld::overlaps(int x, int y, char startType, char type);

private:
	std::vector<Actor*> m_objList;
	Penelope* m_player;
	bool m_levelFinish;
	int m_level;

};

#endif // STUDENTWORLD_H_
