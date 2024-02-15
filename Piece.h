#pragma once
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <cmath>
#include <complex>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <bitset>
using namespace std;
class Piece
{
public:
	string name;
	string Type;
	int row, column;
	vector<int> dRow, dColumn;
	Piece() {
		name = " .  ";
	}

	/*Piece* operator=(const Piece*& cur) {
		Piece *ret = new Piece;
		ret->name = cur->name;
		ret->Type = cur->Type;
		ret->row = cur->row;
		ret->column = cur->column;
		ret->dRow = cur->dRow;
		ret->dColumn = cur->dColumn;
		return ret;
	}*/


	/*void operator=(const Piece* cur) {
		this->name = cur->name;
		this->Type = cur->Type;
		this->row = cur->row;
		this->column = cur->column;
		this->dRow = cur->dRow;
		this->dColumn = cur->dColumn;
	}*/


	void Clone(Piece* p) {
		//Piece* ret = new Piece;
		this->name = p->name;
		this->Type = p->Type;
		this->row = p->row;
		this->column = p->column;
		this->dRow = p->dRow;
		this->dColumn = p->dColumn;
		//return ret;
	}
};