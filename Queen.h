#pragma once
#include "Piece.h"
class Queen : public Piece
{
public:

	Queen() {

		this->dRow.resize(8);
		this->dColumn.resize(8);
		dRow[0] = -1; dColumn[0] = 0;
		dRow[1] = 1; dColumn[1] = 0;
		dRow[2] = 0; dColumn[2] = 1;
		dRow[3] = 0; dColumn[3] = -1;

		dRow[4] = -1; dColumn[4] = 1;
		dRow[5] = 1; dColumn[5] = -1;
		dRow[6] = 1; dColumn[6] = 1;
		dRow[7] = -1; dColumn[7] = -1;

	}


};