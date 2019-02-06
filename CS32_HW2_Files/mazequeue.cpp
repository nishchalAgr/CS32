#include <iostream>
#include <queue>

using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
	//void print() const{ cout << m_r << "," << m_c << endl; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {

	if (sr == er && sc == ec) return true;

	queue<Coord> cStack;

	cStack.push(Coord(sr, sc));

	maze[sr][sc] = '*';

	while (!cStack.empty()) {

		int r = cStack.front().r();
		int c = cStack.front().c();
		cStack.pop();

		//return true if we reach the end coordinates
		if (r == er && c == ec) return true;

		if (maze[r + 1][c] != '*' && maze[r + 1][c] != 'X') {

			cStack.push(Coord(r + 1, c));
			maze[r + 1][c] = '*';

		}

		if (maze[r - 1][c] != '*' && maze[r - 1][c] != 'X') {

			cStack.push(Coord(r - 1, c));
			maze[r - 1][c] = '*';

		}

		if (maze[r][c + 1] != '*' && maze[r][c + 1] != 'X') {

			cStack.push(Coord(r, c + 1));
			maze[r][c + 1] = '*';

		}

		if (maze[r][c - 1] != '*' && maze[r][c - 1] != 'X') {

			cStack.push(Coord(r, c - 1));
			maze[r][c - 1] = '*';

		}

	}

	return false;

}

//int main()
//{
//	string maze[10] = {
//		"XXXXXXXXXX",
//		"X....X...X",
//		"X.XX.XX..X",
//		"XXX....X.X",
//		"X.XXX.XXXX",
//		"X.X...X..X",
//		"X...X.X..X",
//		"XXXXX.X.XX",
//		"X........X",
//		"XXXXXXXXXX"
//	};
//
//	if (pathExists(maze, 10, 10, 3, 5, 8, 8))
//		cout << "Solvable!" << endl;
//	else
//		cout << "Out of luck!" << endl;
//}
