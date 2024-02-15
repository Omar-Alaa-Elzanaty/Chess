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
#include "Piece.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
using namespace std;
class Board
{
private:
	const int _rows = 9;
	const int _columns = 9;
public:
	string _black = "Black";
	string _white = "White";
	vector<vector<Piece*>>board;
	Board() :board(_rows, vector<Piece*>(_columns, nullptr))
	{
		board[1][1] = new Rook;
		board[1][1]->name = "BRO ";
		board[1][8] = new Rook;
		board[1][8]->name = "BRO ";

		board[1][2] = new Knight;
		board[1][2]->name = "BKN ";
		board[1][7] = new Knight;
		board[1][7]->name = "BKN ";

		board[1][3] = new Bishop;
		board[1][3]->name = "BBI ";
		board[1][6] = new Bishop;
		board[1][6]->name = "BBI ";

		board[1][4] = new Queen;
		board[1][4]->name = "BQU ";

		board[1][5] = new King;
		board[1][5]->name = "BKI ";

		for (int i = 1; i <= 8; i++) {
			board[1][i]->Type = _black;
			board[1][i]->row = 1;
			board[1][i]->column = i;
		}

		for (int i = 1; i <= 8; i++) {
			break;
			board[2][i] = new Pawn;
			board[2][i]->name = "BPA ";
			board[2][i]->Type = _black;
			board[2][i]->row = 2;
			board[2][i]->column = i;
		}

		board[8][1] = new Rook;
		board[8][1]->name = "WRO ";
		board[8][8] = new Rook;
		board[8][8]->name = "WRO ";

		board[8][2] = new Knight;
		board[8][2]->name = "WKN ";
		board[8][7] = new Knight;
		board[8][7]->name = "WKN ";

		board[8][3] = new Bishop;
		board[8][3]->name = "WBI ";
		board[8][6] = new Bishop;
		board[8][6]->name = "WBI ";

		board[8][4] = new Queen;
		board[8][4]->name = "WQU ";

		board[8][5] = new King;
		board[8][5]->name = "WKI ";

		for (int i = 1; i <= 8; i++) {
			board[8][i]->Type = _white;
			board[8][i]->row = 8;
			board[8][i]->column = i;
		}

		for (int i = 1; i <= 8; i++) {
			break;
			board[7][i] = new Pawn;
			board[7][i]->name = "WPA ";
			board[7][i]->Type = _white;
			board[7][i]->row = 7;
			board[7][i]->column = i;
		}
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				if (board[i][j] == nullptr){
					board[i][j] = new Piece;
				}
			}
		}
			
	}

	void operator=(Board* newBoard) {
		//Board ret;
		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				this->board[i][j]->Clone(newBoard->board[i][j]);
				// = Piece().Clone(newBoard->board[i][j]);
			}
		}
		//return ret;
	}
	void operator=(Board newBoard) {
		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				board[i][j]->Clone(newBoard.board[i][j]);
				//ret.board[i][j] = newBoard.board[i][j]->Clone(newBoard.board[i][j]);
			}
		}
	}
};