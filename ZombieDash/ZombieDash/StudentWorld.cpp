#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include <string>
#include <sstream>

using namespace std;

bool isOverlap(int x1, int y1, int x2, int y2) {

	int deltaX = x1 - x2;
	int deltaY = y1 - y2;

	return deltaX * deltaX + deltaY * deltaY <= 100;

}

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
	: GameWorld(assetPath)
{
	m_levelFinish = false;
	m_level = 1;
}

int StudentWorld::init()
{
	Level lev(assetPath());
	ostringstream oss;
	if (m_level < 10) {
		oss << "level0" << m_level << ".txt";
	}
	else {
		oss << "level" << m_level << ".txt";
	}
	string levelFile = oss.str();
	Level::LoadResult result = lev.loadLevel(levelFile);
	if (result == Level::load_fail_file_not_found)
		cerr << "Cannot find level01.txt data file" << endl;
	else if (result == Level::load_fail_bad_format)
		cerr << "Your level was improperly formatted" << endl;
	else if (result == Level::load_success)
	{
		cerr << "Successfully loaded level" << endl;
		//cout << levelFile << endl;
		for (int x = 0; x < 16; x++) {
			for (int y = 0; y < 16; y++) {
				//cout << x << "," << y << endl;
				Level::MazeEntry ge = lev.getContentsOf(x, y);

				switch (ge) {

				case Level::player:
					m_player = new Penelope(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
					break;

				case Level::wall:
					m_objList.push_back(new Wall(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this));
					break;

				case Level::exit:
					m_objList.push_front(new Exit(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this));
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
	//cout << "1" << endl;
	m_player->doSomething();
	//cout << "2" << endl;
	for (list<Actor*>::iterator p = m_objList.begin(); p != m_objList.end(); p++)
		(*p)->doSomething();
	//cout << "3" << endl;
	if (m_levelFinish) {
		m_levelFinish = false;
		m_level++;
		return GWSTATUS_FINISHED_LEVEL;
	}

	//decLives();
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	m_objList.clear();
	//if (m_objList.empty()) cout << "empty" << endl;
	delete m_player;
}

Actor* StudentWorld::overlap(int x, int y, char type) {

	if (type == '@') {
		if (isOverlap(x, y, m_player->getX(), m_player->getY())) return m_player;
	}

	for (list<Actor*>::iterator p = m_objList.begin(); p != m_objList.end(); p++) {

		if (type == (*p)->getType() && isOverlap(x, y, (*p)->getX(), (*p)->getY()))
			return (*p);

	}

	return nullptr;

}

bool StudentWorld::contains(int x, int y, char type) {

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
		//cout << (*p)->getType() << endl;
		if ((*p)->getType() == type) {

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
	}

	return false;
}

bool StudentWorld::citizenDead() {

	for (list<Actor*>::iterator p = m_objList.begin(); p != m_objList.end(); p++) {

		if ((*p)->getType() == 'C' && (*p)->isAlive()) return false;

	}

	return true;
}

list<Actor*> StudentWorld::getObjList() {

	return m_objList;

}

int StudentWorld::getPX() {

	return m_player->getX();

}

int StudentWorld::getPY() {

	return m_player->getY();

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
