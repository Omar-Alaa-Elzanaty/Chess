#pragma once
#include "IPieceService.h"
#include "Board.h"
class IQueenService:public IPieceService {
	Piece* Queen;
	pair<int, int>KingPos;
public:
	bool isMyPiece(Board board ,int x,int y) {
		//cout << Queen->Type << ' ' << board.board[x][y]->Type << endl;
		return Queen->Type == board.board[x][y]->Type;
	}

	bool IsValidCell(int x, int y) {
		return ((x >= 1 and x <= 8) and (y >= 1 and y <= 8));
	}

	bool IsEmptyCell(int x, int y, Board CurrentBoard) {
		return CurrentBoard.board[x][y]->name == " .  ";
	}

	bool IsOnLeftDiagonal(int x, int y) {
		return x - y == KingPos.first - KingPos.second;
	}

	bool IsOnRightDiagonal(int x, int y) {
		return x + y == KingPos.first + KingPos.second;
	}

	bool IsOnCheckLine(int x, int y, string _IsCheck) {
		if (_IsCheck == "") {
			return true;
		}
		else {
			if (_IsCheck == "Up") {
				return (y == KingPos.second and x > KingPos.first);
			}
			else if (_IsCheck == "Down") {
				return (y == KingPos.second and x < KingPos.first);
			}
			else if (_IsCheck == "Right") {
				return (x == KingPos.first and y > KingPos.second);
			}
			else if (_IsCheck == "Left") {
				return (x == KingPos.first and y < KingPos.second);
			}
			else if (_IsCheck == "DownLeft") {
				return x < KingPos.first&& y < KingPos.second&& IsOnLeftDiagonal(x, y);
			}
			else if (_IsCheck == "UpLeft") {
				return x > KingPos.first && y < KingPos.second&& IsOnLeftDiagonal(x, y);
			}
			else if (_IsCheck == "DownRight") {
				return x < KingPos.first&& y > KingPos.second && IsOnRightDiagonal(x, y);
			}
			else {
				return x > KingPos.first && y > KingPos.second && IsOnRightDiagonal(x, y);
			}
		}
	}

	void SetKingPos(Board* board) {
		string King = ((Queen->Type == "Black") ? "BKI " : "WKI ");
		for (int i = 1;i <= 8;i++)
		{
			for (int j = 1;j <= 8;j++)
			{
				if (board->board[i][j]->name == King) {
					KingPos = { i,j };
					return;
				}
			}
		}
	}

	string IsCheck(Board* board) {
		string opponent1 = ((Queen->Type == "Black") ? "BRO " : "WRO ");
		string opponent2 = ((Queen->Type == "Black") ? "BQu " : "WQu ");
		// CheckRight
		for (int i = KingPos.second + 1; i <= 8; i++) {
			if (board->board[KingPos.first][i]->name != " .  ")
			{
				if (board->board[KingPos.first][i]->name == opponent1 || board->board[KingPos.first][i]->name == opponent2) {
					return "Right";
				}
				else {
					break;
				}
			}
		}
		// CheckLeft
		for (int i = KingPos.second - 1; i >= 1; i--) {
			if (board->board[KingPos.first][i]->name != " .  ")
			{
				if (board->board[KingPos.first][i]->name == opponent1 || board->board[KingPos.first][i]->name == opponent2) {
					return "Left";
				}
				else {
					break;
				}
			}
		}
		// CheckUp
		for (int i = KingPos.first + 1; i <= 8; i++) {
			if (board->board[i][KingPos.second]->name != " .  ")
			{
				if (board->board[i][KingPos.second]->name == opponent1 || board->board[i][KingPos.second]->name == opponent2) {
					return "Up";
				}
				else {
					break;
				}
			}
		}
		// CheckDown
		for (int i = KingPos.first - 1; i >= 1; i--) {
			if (board->board[i][KingPos.second]->name != " .  ")
			{
				if (board->board[i][KingPos.second]->name == opponent1 || board->board[i][KingPos.second]->name == opponent2) {
					return "Up";
				}
				else {
					break;
				}
			}
		}

		opponent2 = ((Queen->Type == "Black") ? "BBI " : "WBI ");

		//Check DownLeft diagonale

		for (int i = KingPos.first - 1, j = KingPos.second - 1; i >= 1 && j >= 1; i--, j--) {
			if (board->board[i][j]->name != " .  ")
			{
				if (board->board[i][j]->name == opponent1 || board->board[i][j]->name == opponent2) {
					return "DownLeft";
				}
				else {
					break;
				}
			}
		}

		//Check DownRight diagonale

		for (int i = KingPos.first - 1, j = KingPos.second + 1; i >= 1 && j <= 8; i--, j++) {
			if (board->board[i][j]->name != " .  ")
			{
				if (board->board[i][j]->name == opponent1 || board->board[i][j]->name == opponent2) {
					return "DownRight";
				}
				else {
					break;
				}
			}
		}

		//Check UpLeft diagonale

		for (int i = KingPos.first + 1, j = KingPos.second - 1; i <= 8 && j >= 1; i++, j--) {
			if (board->board[i][j]->name != " .  ")
			{
				if (board->board[i][j]->name == opponent1 || board->board[i][j]->name == opponent2) {
					return "UpLeft";
				}
				else {
					break;
				}
			}
		}

		//Check UpRight diagonale

		for (int i = KingPos.first + 1, j = KingPos.second + 1; i <= 8 && j <= 8; i++, j++) {
			if (board->board[i][j]->name != " .  ")
			{
				if (board->board[i][j]->name == opponent1 || board->board[i][j]->name == opponent2) {
					return "UpRight";
				}
				else {
					break;
				}
			}
		}

		// Check for knight attacks
		opponent2 = ((Queen->Type == "Black") ? "BHO " : "WHO ");
		int dx[] = { -2, -2, -1, -1, 1, 1, 2, 2 };
		int dy[] = { -1, 1, -2, 2, -2, 2, -1, 1 };
		for (int i = 0; i < 8; i++) {
			int x = KingPos.first + dx[i];
			int y = KingPos.first + dy[i];
			if (x >= 0 && x < 8 && y >= 0 && y < 8 && board->board[x][y]->name == opponent2) {
				return "knight";
			}
		}
		return "";
	}

	Board MakeMove(int x, int y, Board* board, Piece* piece) {
		int xp = piece->row;
		int yp = piece->column;
		board->board[x][y]->Clone(piece);
		board->board[x][y]->row = x;
		board->board[x][y]->column = y;
		Piece* rem = board->board[xp][yp];
		board->board[xp][yp] = new Piece();
		board->board[xp][yp]->row = xp;
		board->board[xp][yp]->column = yp;
		delete rem;
		return *board;
	}

	int _x, _y;
	bool  CanMove(Board* board, Piece* piece) {
		string _IsCheck = IsCheck(board);

		bool _IsOnCheckLine = IsOnCheckLine(_x, _y, _IsCheck);

		return (_IsOnCheckLine);
	}

	void clone(Board &CurrentBoard,Board *board) {
		for (int i = 1;i <= 8;i++) {
			for (int j = 1;j <= 8;j++) {
				CurrentBoard.board[i][j]->name = board->board[i][j]->name;
				CurrentBoard.board[i][j]->Type = board->board[i][j]->Type;
			}
		}
	}
	Board AllValidMove(Board* board, Piece* piece) {
		Queen = piece;
		
		SetKingPos(board);

		Board CurrentBoard ;

		clone(CurrentBoard, board);

		for (int i = 0;i < 8;i++) {
			int cnt = 1;
			pair<int, int>Pos = { (cnt * piece->dRow[i]) + piece->row,(cnt * piece->dColumn[i]) + piece->column };

			_x = Pos.first;_y = Pos.second;
			while (IsValidCell(Pos.first, Pos.second)) {

				if (!IsEmptyCell(Pos.first, Pos.second, CurrentBoard)) {
					// Capture Move
					cout << Pos.first << ' ' << Pos.second << ' ' << Queen->Type << ' ' << CurrentBoard.board[Pos.first][Pos.second]->Type << endl;
					if (!isMyPiece(CurrentBoard, Pos.first, Pos.second) and CanMove(board, piece)) {
						CurrentBoard.board[Pos.first][Pos.second]->name[3] = '*';
					}
					break;
				}
				// Non Capture Move
				if (CanMove(board, piece)) {
					CurrentBoard.board[Pos.first][Pos.second]->name = " *  ";
				}
				cnt++;
				Pos = { (cnt * piece->dRow[i]) + piece->row,(cnt * piece->dColumn[i]) + piece->column };
			}
		}

		return CurrentBoard;
	}

};
