#ifndef ARENA_INCLUDED
#define ARENA_INCLUDED
#include "History.h"
#include "globals.h"

class Player;
class Zombie;

class Arena
{
public:
	// Constructor/destructor
	Arena(int nRows, int nCols);
	~Arena();

	// Accessors
	int     rows() const;
	int     cols() const;
	Player* player() const;
	int     zombieCount() const;
	int     numZombiesAt(int r, int c) const;
	bool    determineNewPosition(int& r, int& c, int dir) const;
	void    display() const;
	History& history();


	// Mutators
	bool   addZombie(int r, int c);
	bool   addPlayer(int r, int c);
	bool   attackZombieAt(int r, int c, int dir);
	bool   moveZombies();

private:
	int     m_rows;
	int     m_cols;
	Player* m_player;
	Zombie* m_zombies[MAXZOMBIES];
	History m_history;
	int     m_nZombies;
};

#endif
