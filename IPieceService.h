#pragma once
#include "Board.h"
class IPieceService
{
public:
	virtual bool  CanMove(Board* board, Piece* piece) = 0;
	virtual Board AllValidMove(Board* board, Piece* piece) = 0;
	virtual Board MakeMove(int x, int y, Board* board, Piece* piece) = 0;
};

