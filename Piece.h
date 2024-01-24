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
	Piece operator=(const Piece*& cur) {
		Piece ret;
		ret.name = name;
		ret.Type = Type;
		ret.row = row;
		ret.column = column;
		ret.dRow = dRow;
		ret.dColumn = dColumn;
		return ret;
	}
};