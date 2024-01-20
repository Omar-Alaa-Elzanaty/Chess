#pragma once
class IPieceService
{
public:
	bool CheckMove(int row, int column);
	void Move(int row, int column);
	void DisplayValidMoves();
};

