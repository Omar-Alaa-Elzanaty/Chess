#pragma once
#include "Piece.h"
class Rook :public Piece
{
public:
	Rook() {
<<<<<<< HEAD
		
		this->dRow = new int[4];
		this->dColumn = new int[4];
		dRow[0] = -1; dRow[1] = 1;
		dRow[2] = 0; dRow[3] = 0;

		dColumn[0] = 0; dColumn[1] = 0;
		dColumn[2] = 1; dColumn[3] = -1;
	}
};
=======

		this->dRow = new int[4];
		this->dColumn = new int[4];
		dRow[0] = -1; dRow[1] = 1;
		dRow[2] = 0; dRow[3] = 0;
>>>>>>> e4be1512806cce3c57b6e58de26464d13914ac62

		dColumn[0] = 0; dColumn[1] = 0;
		dColumn[2] = 1; dColumn[3] = -1;
	}
};