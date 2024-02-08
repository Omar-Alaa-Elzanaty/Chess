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
	int* dRow, * dColumn;
	Piece() {
		name = " .  ";
	}

<<<<<<< HEAD
	Piece* operator=(const Piece*& cur) {
=======
	/*Piece* operator=(const Piece*& cur) {
>>>>>>> e4be1512806cce3c57b6e58de26464d13914ac62
		Piece *ret = new Piece;
		ret->name = cur->name;
		ret->Type = cur->Type;
		ret->row = cur->row;
		ret->column = cur->column;
		ret->dRow = cur->dRow;
		ret->dColumn = cur->dColumn;
<<<<<<< HEAD
=======
		return ret;
	}*/
	Piece* Clone(Piece* p) {
		Piece* ret = new Piece;
		ret->name = p->name;
		ret->Type = p->Type;
		ret->row = p->row;
		ret->column = p->column;
		//ret->dRow = p->dRow;
		//ret->dColumn= p->dColumn;
		//ret->dRow = p->dRow;
		ret->dRow = new int[sizeof(p->dRow) / p->dRow[0]];
		for (int i = 0; i < sizeof(p->dRow) / p->dRow[0]; i++) {
			ret->dRow[i] = p->dRow[i];
		}
		//ret->dColumn = p->dColumn;
		ret->dRow = new int[sizeof(p->dColumn) / p->dColumn[0]];
		for (int i = 0; i < sizeof(p->dColumn) / p->dColumn[0]; i++) {
			ret->dColumn[i] = p->dColumn[i];
		}
>>>>>>> e4be1512806cce3c57b6e58de26464d13914ac62
		return ret;
	}
};