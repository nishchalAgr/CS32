#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
	Level lev(assetPath());
	string levelFile = "level01.txt";
	Level::LoadResult result = lev.loadLevel(levelFile);
	if (result == Level::load_fail_file_not_found)
		cerr << "Cannot find level01.txt data file" << endl;
	else if (result == Level::load_fail_bad_format)
		cerr << "Your level was improperly formatted" << endl;
	else if (result == Level::load_success)
	{
		cerr << "Successfully loaded level" << endl;
		for (int x = 0; x < 16; x++) {
			for (int y = 0; y < 16; y++) {
				
				Level::MazeEntry ge = lev.getContentsOf(x, y);
				
				switch (ge) {
				
				case Level::player:
					m_player = new Penelope(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
					break;

				case Level::wall:
					Wall *temp = new Wall(x,y,this);
					m_objList.push_front(temp);
					break;
				}
			}
		}
	}
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.

	if (!m_player->isAlive()) return GWSTATUS_PLAYER_DIED;

	m_player->doSomething();

	for (list<Actor*>::iterator p = m_objList.begin(); p != m_objList.end(); p++)
		(*p)->doSomething();

    //decLives();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
}

bool StudentWorld::contains(int x, int y, char type) {

	for (list<Actor*>::iterator p = m_objList.begin(); p != m_objList.end(); p++) {
	
		if ((*p)->getType() == type && (*p)->getX() == x && (*p)->getY() == y) return true;
	
	}

	return false;
}
