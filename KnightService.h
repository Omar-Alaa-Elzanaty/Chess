#pragma once
#include "IPieceService.h"
#include "King.h"
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
class KnightService :public IPieceService
{
public:
	//virtual bool  CanMove(Board* board, Piece* piece) = 0;
	//virtual Board AllValidMove(Board* board, Piece* piece) = 0;
	//virtual Board MakeMove(int x, int y, Board* board, Piece* piece) = 0;
	pair<int, int>kingpos;
	pair<int, int>pos(Board* board, Piece* piece) {
		int xking, yking;
		char col = piece->name[0]; string Target;
		Target.push_back(col); Target += "KI "; 
		for (int i = 1; i <= 8; i++) {// find king position
			for (int j = 1; j <= 8; j++) {
				if (board->board[i][j]->name == Target) {
					xking = i;
					yking = j;
					return { xking,yking };
				}
			}
		}return { -1,-1 };
	}
	bool inboard(int idx1, int idx2) {
		if (idx1 > 8 or idx1 < 1 or idx2>8 or idx2 < 1)return false;
		return true;
	}
	vector<pair<int, int>>kish(Board* board, Piece* piece) {
		kingpos = pos(board, piece);//+
		string DiffrentColor = "0";
		vector<pair<int, int>>kishplace;
		if (piece->Type == "Black")DiffrentColor = "W";
		else if (piece->Type == "White")DiffrentColor = "B";
		// my king and opponent rock or queen {
		for (int i = kingpos.second; i <= 8; i++) {
			if (board->board[kingpos.first][i]->name == (DiffrentColor + "RO ") or board->board[kingpos.first][i]->name == (DiffrentColor + "QU ")) {
				kishplace.emplace_back(kingpos.first, i);
				return kishplace;
			}
			else if (board->board[kingpos.first][i]->name == " .  ")continue;
			else break;
		}
		for (int i = kingpos.second; i >= 1; i--) {
			if (board->board[kingpos.first][i]->name == (DiffrentColor + "RO ") or board->board[kingpos.first][i]->name == (DiffrentColor + "QU ")) {
				kishplace.emplace_back(kingpos.first, i);
				return kishplace;
			}
			else if (board->board[kingpos.first][i]->name == " .  ")continue;
			else break;
		}
		for (int i = kingpos.first; i <= 8; i++) {
			if (board->board[i][kingpos.second]->name == (DiffrentColor + "RO ") or board->board[i][kingpos.second]->name == (DiffrentColor + "QU ")) {
				kishplace.emplace_back(i, kingpos.second);
				return kishplace;
			}
			else if (board->board[i][kingpos.second]->name == " .  ")continue;
			else break;
		}
		for (int i = kingpos.first; i >= 1; i--) {
			if (board->board[i][kingpos.second]->name == (DiffrentColor + "RO ") or board->board[i][kingpos.second]->name == (DiffrentColor + "QU ")) {
				kishplace.emplace_back(i, kingpos.second);
				return kishplace;
			}
			else if (board->board[i][kingpos.second]->name == " .  ")continue;
			else break;
		}
		// }
		// 
		// my king and opponent bishop or queen{
		int idxx = kingpos.first; int idxy = kingpos.second;
		while (idxx < 9 and idxy < 9) {
			idxx++; idxy++;
			if (idxx < 9 and idxy < 9) {
				if (board->board[idxx][idxy]->name == (DiffrentColor + "BI ") or (board->board[idxx][idxy]->name == (DiffrentColor + "QU "))) {
					kishplace.emplace_back(idxx, idxy);
					return kishplace;
				}
				else if (board->board[idxx][idxy]->name == " .  ")continue;
				else break;
			}
			else {
				break;
			}
		}
		idxx = kingpos.first; idxy = kingpos.second;
		while (idxx > 0 and idxy > 0) {
			idxx--; idxy--;
			if (idxx > 0 and idxy > 0) {
				if (board->board[idxx][idxy]->name == (DiffrentColor + "BI ") or board->board[idxx][idxy]->name == (DiffrentColor + "QU ")) {
					kishplace.emplace_back(idxx, idxy);
					return kishplace;
				}
				else if (board->board[idxx][idxy]->name == " .  ")continue;
				else break;
			}
			else {
				break;
			}
		}
		idxx = kingpos.first; idxy = kingpos.second;
		while (idxx > 0 and idxy < 9) {
			idxx--; idxy++;
			if (idxx > 0 and idxy < 9) {
				if (board->board[idxx][idxy]->name == (DiffrentColor + "BI ") or board->board[idxx][idxy]->name == (DiffrentColor + "QU ")) {
					kishplace.emplace_back(idxx, idxy);
					return kishplace;
				}
				else if (board->board[idxx][idxy]->name == " .  ")continue;
				else break;
			}
			else break;
		}
		idxx = kingpos.first; idxy = kingpos.second;
		while (idxx < 9 and idxy > 0) {
			idxx++; idxy--;
			if (idxx < 9 and idxy > 0) {
				if (board->board[idxx][idxy]->name == (DiffrentColor + "BI ") or board->board[idxx][idxy]->name == (DiffrentColor + "QU ")) {
					kishplace.emplace_back(idxx, idxy);
					return kishplace;
				}
				else if (board->board[idxx][idxy]->name == " .  ")continue;
				else break;
			}
			else break;
		}
		// }
		//
		// my king and opponent knight {
		idxx = kingpos.first; idxy = kingpos.second;
		for (int i = 0; i < 8; i++) {
			int newx = kingpos.first + Knight().dRow[i];
			int newy = kingpos.second + Knight().dColumn[i];
			if (inboard(newx, newy)) {
				if (board->board[newx][newy]->name == (DiffrentColor + "KN ")) {
					kishplace.emplace_back(newx, newy);
					return kishplace;
				}
			}
		}
		// }
		//
		// my king and opponent pawn {
		idxx = kingpos.first - 1; idxy = kingpos.second - 1;
		if (inboard(idxx, idxy)) {
			if (DiffrentColor == "B") {
				if (board->board[idxx][idxy]->name == (DiffrentColor + "PA ")) {
					kishplace.emplace_back(idxx, idxy);
					return kishplace;
				}
			}
		}
		idxx = kingpos.first - 1; idxy = kingpos.second + 1;
		if (inboard(idxx, idxy)) {
			if (DiffrentColor == "B") {
				if (board->board[idxx][idxy]->name == (DiffrentColor + "PA ")) {
					kishplace.emplace_back(idxx, idxy);
					return kishplace;
				}
			}
		}
		idxx = kingpos.first + 1; idxy = kingpos.second - 1;
		if (inboard(idxx, idxy)) {
			if (DiffrentColor == "W") {
				if (board->board[idxx][idxy]->name == (DiffrentColor + "PA ")) {
					kishplace.emplace_back(idxx, idxy);
					return kishplace;
				}
			}
		}
		idxx = kingpos.first + 1; idxy = kingpos.second + 1;
		if (inboard(idxx, idxy)) {
			if (DiffrentColor == "W") {
				if (board->board[idxx][idxy]->name == (DiffrentColor + "PA ")) {
					kishplace.emplace_back(idxx, idxy);
					return kishplace;
				}
			}
		}
		//mror
		idxx = kingpos.first; idxy = kingpos.second + 1;
		if (inboard(idxx, idxy)) {
			if (board->board[idxx][idxy]->name == (DiffrentColor + "PA ")) {
				kishplace.emplace_back(idxx, idxy);
				return kishplace;
			}
		}
		idxx = kingpos.first; idxy = kingpos.second - 1;
		if (inboard(idxx, idxy)) {
			if (board->board[idxx][idxy]->name == (DiffrentColor + "PA ")) {
				kishplace.emplace_back(idxx, idxy);
				return kishplace;
			}
		}
		// }
		return kishplace;
	}vector<pair<int,int>>canplace;
	Board AllValidMove(Board* board,Piece* piece){
		Knight* kn = new Knight;
		int idxx = piece->row;int idxy = piece->column;
		set<pair<int,int>>se;
		for (int i = 0; i < 8; i++) {
			idxx = piece->row + kn->dRow[i]; idxy = piece->column + kn->dColumn[i];
			if (inboard(idxx,idxy)) {
				se.emplace(idxx,idxy);
			}
		}
		Board show = *board;
		vector<pair<int, int>>kishplace = kish(board, piece);
		if (kishplace.size() == 0) {
			for (int i = 0; i < 8; i++) {
				idxx = piece->row + Knight().dRow[i], idxy = piece->column + Knight().dColumn[i];
				if (inboard(idxx,idxy) and board->board[idxx][idxy]->name[0] != piece->Type[0]) {
					canplace.emplace_back(idxx,idxy);
					show.board[idxx][idxy]->name = " *  ";
				}
			}
			// show normal place for knight
		}
		else {
			kingpos = pos(board,piece);
			idxx = piece->row,idxy = piece->column;
			string validway = "0";
			for (int i = kingpos.first; i <= 8; i++) {
				for (int j = kingpos.second; j <= 8; j++) {
					if (i == idxx and j == idxy) {
						validway = "downright";
						break;
					}
				}
			}
			for (int i = kingpos.first; i >= 1; i--) {
				for (int j = kingpos.second; j >= 1; j--) {
					if (i == idxx and j == idxy) {
						validway = "upleft";
						break;
					}
				}
			}
			for (int i = kingpos.first; i <= 8; i++) {
				if (i == idxx and kingpos.second == idxy) {
					validway = "down";
					break;
				}
			}
			for (int i = kingpos.first; i >= 1; i--) {
				if (i == idxx and kingpos.second == idxy) {
					validway = "up";
					break;
				}
			}
			for (int i = kingpos.second; i <= 8; i++) {
				if (idxx == kingpos.first and i == idxy) {
					validway = "right";
					break;
				}
			}
			for (int i = kingpos.second; i >= 1; i--) {
				if (idxx == kingpos.first and i == idxy) {
					validway = "left";
					break;
				}
			}
			for (int i = kingpos.first; i <= 8; i++) {
				for (int j = kingpos.second; j >= 1; j--) {
					if (i == idxx and j == idxy) {
						validway = "downleft";
						break;
					}
				}
			}
			for (int i = kingpos.first; i >= 1; i--) {
				for (int j = kingpos.second; j <= 8; j++) {
					if (i == idxx and j == idxy) {
						validway = "upright";
						break;
					}
				}
			}
			if (validway == "downright") {
				for (int i = kingpos.first; i <= idxx; i++) {
					for (int j = kingpos.second; j <= idxy; j++) {
						if (se.find({ i,j }) != se.end()) {
							canplace.emplace_back(i, j);
							show.board[i][j]->name = " *  ";
						}
					}
				}
			}
			else if (validway == "upleft") {
				for (int i = kingpos.first; i >= idxx; i--) {
					for (int j = kingpos.second; j >= idxy; j--) {
						if (se.find({ i,j }) != se.end()) {
							canplace.emplace_back(i, j);
							show.board[i][j]->name = " *  ";
						}
					}
				}
			}
			else if (validway == "downleft") {
				for (int i = kingpos.first; i <= idxx; i++) {
					for (int j = kingpos.second; j >= idxy; j--) {
						if (se.find({ i,j }) != se.end()) {
							canplace.emplace_back(i, j);
							show.board[i][j]->name = " *  ";
						}
					}
				}
			}
			else if (validway == "upright") {
				for (int i = kingpos.first; i >= idxx; i--) {
					for (int j = kingpos.second; j <= idxy; j++) {
						if (se.find({ i,j }) != se.end()) {
							canplace.emplace_back(i, j);
							show.board[i][j]->name = " *  ";
						}
					}
				}
			}
			else if (validway == "up") {
				for (int i = kingpos.first; i >= idxx; i--) {
					if (se.find({ i,kingpos.second }) != se.end()) {
						canplace.emplace_back(i, kingpos.second);
						show.board[i][kingpos.second]->name = " *  ";
					}
				}
			}
			else if (validway == "down") {
				for (int i = kingpos.first; i <= idxx; i++) {
					if (se.find({ i,kingpos.second }) != se.end()) {
						canplace.emplace_back(i, kingpos.second);
						show.board[i][kingpos.second]->name = " *  ";
					}
				}
			}
			else if (validway == "right") {
				for (int i = kingpos.second; i <= idxy; i++) {
					if (se.find({ kingpos.first,i }) != se.end()) {
						canplace.emplace_back(kingpos.first, i);
						show.board[kingpos.first][i]->name = " *  ";
					}
				}
			}
			else if (validway == "left") {
				for (int i = kingpos.second; i >= idxy; i--) {
					if (se.find({ kingpos.first,i }) != se.end()) {
						canplace.emplace_back(kingpos.first, i);
						show.board[kingpos.first][i]->name = " *  ";
					}
				}
			}
			// if you can save the king ok save him
			// if you cant so you cant move
		}cout << "valid place are (*)" << endl;
		return show;
	}vector<pair<int, int>>knightplace;
	bool CanMove(Board* board, Piece* piece) {
		Knight* kn = new Knight;
		int idxx = piece->row; int idxy = piece->column;
		for (int i = 0; i < 8; i++) {
			idxx = piece->row + kn->dRow[i]; idxy = piece->column + kn->dColumn[i];
			if (inboard(idxx, idxy)) {
				knightplace.emplace_back(idxx, idxy);
			}
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < canplace.size(); j++) {
				if (knightplace[i].first == canplace[j].first and knightplace[i].second == canplace[j].second) {
					return true;
				}
			}
		}return false;
	}
	Board MakeMove(int x, int y,Board* board, Piece* piece){
		Board temp = *board;
		if (CanMove(board,piece)){
			bool put = 0;
			bool put2 = 0;
			for (int i = 0; i < knightplace.size(); i++) {
				if (knightplace[i].first == x and knightplace[i].second == y) {
					put2 = 1;
					break;
				}
			}
			for (int i = 0; i < canplace.size(); i++) {
				if (canplace[i].first == x and canplace[i].second == y) {
					put = 1;
					break;
				}
			}
			if (put and put2) {
				int prevRow = piece->row;
				int prevCol = piece->column;
				temp.board[x][y] = piece;
				temp.board[x][y]->row = x;
				temp.board[x][y]->column = y;
				piece = new Piece;
				piece->row = prevRow;
				piece->column = prevCol;
				temp.board[prevRow][prevCol] = piece;
				board->board[x][y] = temp.board[x][y];
				board->board[prevRow][prevCol] = temp.board[prevRow][prevCol];				
				cout << "your knight have moved" << endl;
				return temp;
			}
			else {
				cout << "your knight cant move" << endl;
			}
		}
		else {
			cout << "your knight cant move" << endl;
		}
	}
};