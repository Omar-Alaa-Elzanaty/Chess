#pragma once
#include "Piece.h"
class Rook :public Piece
{
public:
	Rook() {
		int dy[] = { -1, 1, 0, 0, -1, 1, 1, -1 };
		int dx[] = { 0, 0, 1, -1, 1, -1, 1, -1 };
		this->dRow = new int[4];
		this->dColumn = new int[4];
		dRow[0] = -1; dRow[1] = 1;
		dRow[2] = 0; dRow[3] = 0;

		dColumn[0] = 0; dColumn[1] = 0;
		dColumn[2] = 1; dColumn[3] = -1;
	}
};

