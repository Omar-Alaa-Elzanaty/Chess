#pragma once
#include<string>

using namespace std;

class Piece
{
public:
	string name;
	string Type;
	int row, column;
	int* dRow,* dColumn;
	Piece() {
		name = " .  ";
	}

	Piece* operator=(const Piece*& cur) {
		Piece *ret = new Piece;
		ret->name = cur->name;
		ret->Type = cur->Type;
		ret->row = cur->row;
		ret->column = cur->column;
		ret->dRow = cur->dRow;
		ret->dColumn = cur->dColumn;
		return ret;
	}
};