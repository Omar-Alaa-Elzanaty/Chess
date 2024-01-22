#pragma once
#include<string>

using namespace std;

class Piece
{
public:
	string name;
	string Type;
	int row, column;
	int* dRow, dColumn;
	Piece(string name, bool color, int row, int column);

};