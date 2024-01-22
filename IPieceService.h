#pragma once
#include "Board.h"
class IPieceService
{
public:
	Board CheckMove(int row, int column);
	void Move(int row, int column);
	void DisplayValidMoves();
};

