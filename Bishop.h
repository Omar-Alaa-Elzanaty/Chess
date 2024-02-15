#pragma once
#include "Piece.h"

using namespace std;
class Bishop :public Piece
{
public:
	Bishop() {
		this->dRow.resize(4);
		this->dColumn.resize(4);
		dRow[0] = 1; dRow[1] = 1;
		dRow[2] = -1; dRow[3] = -1;

		dColumn[0] = 1; dColumn[1] = -1;
		dColumn[2] = 1; dColumn[3] = -1;
	}
};