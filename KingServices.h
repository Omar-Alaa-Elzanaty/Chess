#pragma once
#include "King.h"
class KingServices:IPieceServcies
{
private:
	King _king;
public:
	KingServices(King king) {
		_king = king;
	}
	KingServices();



	bool CheckMove() {
		// check  in grid
		// valid move
	}
	Board Move(Board x);
	Board DisplayValidMoves();

	
};
class Board
{
public:
	Board() {
		board = vector<vector<int>>(rows + 1, vector<int>(columns + 1,nullptr));
		board[1][1] = new King(White);
	}
private:
	const int rows = 8;
	const int columns = 8;
	vector<vector<*piece>>board;
};


