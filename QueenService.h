#pragma once
#include "IPieceService.h"
#include "Board.h"
class QueenService:public IPieceService{
public:

	bool IsValidCell(int x, int y) {
		return ((x >= 0 and x < 8) and (y >= 0 and y < 8));
	}

	bool IsEmptyCell(int x, int y,Board CurrentBoard) {
		return CurrentBoard.board[x][y]->name == " .  ";
	}

	Board AllValidMove(Board* board, Piece* piece) {
		Board CurrentBoard =*board;
		for (int i = 0;i < 8;i++) {
			for (int j = 0;j < 8;j++) {
				cout << CurrentBoard.board[i][j] << ' ';
			}
			cout << endl;
		}
		for (int i = 0;i < 8;i++) {
			int cnt = 1;
			pair<int, int>Pos = { (cnt * piece->dRow[i]) + piece->row,(cnt * piece->dColumn[i]) + piece->column };
			while (IsValidCell(Pos.first, Pos.second)) {
				if (!IsEmptyCell(Pos.first,Pos.second,CurrentBoard)) {
					CurrentBoard.board[Pos.first][Pos.second]->name[3] = '*';
					break;
				}
				CurrentBoard.board[Pos.first][Pos.second]->name = " *  ";
				cnt++;
				Pos= { (cnt * piece->dRow[i]) + piece->row,(cnt * piece->dColumn[i]) + piece->column };
			}
		}
		return CurrentBoard;
	}

	Board MakeMove(int x, int y, Board* board, Piece* piece) {
		Board tmp;
		return tmp;
	}
	bool  CanMove(Board* board, Piece* piece) {
		return false;
	}
};

