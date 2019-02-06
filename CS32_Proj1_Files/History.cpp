#include <iostream>
#include "History.h"


using namespace std;

void clearScreen();

History::History(int nrows, int ncols) {

	m_rows = nrows;
	m_cols = ncols;

	for (int i = 0; i < m_rows; i++) {

		for (int j = 0; j < m_cols; j++) {

			m_board[i][j] = '.';

		}

	}

}

bool History::record(int r, int c) {

	if (r < 1 || r > m_rows || c < 1 || c > m_cols) return false;

	int row = r - 1;
	int col = c - 1;

	if (m_board[row][col] == '.') m_board[row][col] = 'A';
	else if (m_board[row][col] != 'Z') m_board[row][col]++;

	return true;

}

void History::display() const {


	clearScreen();

	for (int i = 0; i < m_rows; i++) {
	
		for (int j = 0; j < m_cols; j++) {
		
			cout << m_board[i][j];
		
		}

		cout << endl;
	}

	cout << endl;

}
