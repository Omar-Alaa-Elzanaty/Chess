#pragma once
#include "Board.h"
class IPieceService
{
public:
	Board AllValidMove(Board _board, Piece _piece);
	Board MakeMove(int x,int y,Board _board, Piece _piece);
	bool ValidMove(int x, int y, Board _board, Piece _piece);
};

