

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {

	if (sr == er && sc == ec) return true;

	char val = maze[sr][sc];

	if (val != '.') return false;

	//mark as visited
	maze[sr][sc] = '*';

	if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec) ||
		pathExists(maze, nRows, nCols, sr, sc + 1, er, ec) ||
		pathExists(maze, nRows, nCols, sr - 1, sc, er, ec) ||
		pathExists(maze, nRows, nCols, sr, sc - 1, er, ec)   ) return true;

	return false;

}
