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
					Wall *temp = new Wall(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
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

	//if (!m_player->isAlive()) return GWSTATUS_PLAYER_DIED;

	m_player->doSomething();

	for (list<Actor*>::iterator p = m_objList.begin(); p != m_objList.end(); p++)
		(*p)->doSomething();

	//decLives();
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	for (list<Actor*>::iterator p = m_objList.begin(); p != m_objList.end(); p++)
		delete *p;
	delete m_player;
}

bool StudentWorld::contains(int x, int y) {

	int tempX1;
	int tempY1;
	int tempX2;
	int tempY2;

	int right = 0;
	int left = 180;
	int up = 90;
	int down = 270;

	for (list<Actor*>::iterator p = m_objList.begin(); p != m_objList.end(); p++) {

		//cout << (*p)->getX() << "," << (*p)->getY() << endl;
		//cout << "~" << x << "," << y << endl;

		tempX1 = (*p)->getX() - SPRITE_WIDTH / 2;//left bound
		tempX2 = (*p)->getX() + SPRITE_WIDTH / 2;//right bound
		tempY1 = (*p)->getY() - SPRITE_HEIGHT / 2;//lower bound
		tempY2 = (*p)->getY() + SPRITE_HEIGHT / 2;//upper bound

		if (m_player->getDirection() == right) {
			//cout << "right" << endl;
			//x += SPRITE_WIDTH / 2;
			if (x >= tempX1 && x <= tempX2 && y >= tempY1 && y <= tempY2) return true;

		}
		else if (m_player->getDirection() == left) {

			//x = x - SPRITE_WIDTH / 2;
			if (x >= tempX1 && x <= tempX2 && y >= tempY1 && y <= tempY2) return true;

		}
		else if (m_player->getDirection() == up) {

			//y = y + SPRITE_HEIGHT / 2;
			if (x >= tempX1 && x <= tempX2 && y >= tempY1 && y <= tempY2) return true;

		}
		else if (m_player->getDirection() == down) {

			//y = y - SPRITE_HEIGHT / 2;
			if (x >= tempX1 && x <= tempX2 && y >= tempY1 && y <= tempY2) return true;

		}
	}

	return false;
}

std::list<Actor*> StudentWorld::getObjList() {

	return m_objList;

}

//bool StudentWorld::overlaps(int x, int y, char startType, char type) {
//
//	int tempX;
//	int tempY;
//
//	for (list<Actor*>::iterator p = m_objList.begin(); p != m_objList.end(); p++){
//		
//		tempX = (*p)->getX();
//		tempY = (*p)->getY();
//
//		if ((*p)->getType() == type && isOverlap(x, y, tempX, tempY)) {
//
//			if((*p)->getType() == type)
//
//			return true;
//
//		}
//	}
//
//	return false;
//}
