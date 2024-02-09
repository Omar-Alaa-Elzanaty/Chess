#pragma once
#include "Piece.h"
class Queen : public Piece
{
public:

	Queen() {

		this->dRow.resize(8);
		this->dColumn.resize(8);
		dRow[0] = -1; dColumn[0] = 0;
		dRow[0] = 1; dColumn[0] = 0;
		dRow[0] = 0; dColumn[0] = 1;
		dRow[0] = 0; dColumn[0] = -1;

		dRow[0] = -1; dColumn[0] = 1;
		dRow[0] = 1; dColumn[0] = -1;
		dRow[0] = 1; dColumn[0] = 1;
		dRow[0] = -1; dColumn[0] = -1;

	}


};