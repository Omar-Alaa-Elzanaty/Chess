#pragma once
#include "IPieceService.h"
class PawnServices : public IPieceService
{
public:
	pair<int, int> GetKing(Board* myBoard, Piece* myPiece)
	{
		char color = myPiece->name[0];
		string myKing = "XKI ";
		myKing[0] = color;
		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				if (myBoard->board[i][j]->name == myKing)
				{
					return { i, j };
				}
			}
		}
		return { 0,0 };
	}
	vector<pair<int, int>> Check(Board* myBoard, Piece* myPiece)
	{
		vector<pair<int, int>> CheckPos;

		char opponentColor = (myPiece->name[0] == 'W' ? 'B' : 'W');
		string oRook = "XRO ", oBishop = "XBI ", oQueen = "XQU ", oKnight = "XKN ", oPawn = "XPA ";
		oRook[0] = opponentColor; oBishop[0] = opponentColor; oQueen[0] = opponentColor; oKnight[0] = opponentColor;
		oPawn[0] = opponentColor;

		pair<int, int> myKingPos = GetKing(myBoard, myPiece);
		int _xKing = myKingPos.first, _yKing = myKingPos.second, x, y;


		//rook and queen
		Rook* tempRook = new Rook;
		for (int i = 0; i < 4; i++) {
			x = _xKing + tempRook->dRow[i];
			y = _yKing + tempRook->dColumn[i];
			while (x and x < 9 and y and y < 9) {
				if (myBoard->board[x][y]->name == oRook || myBoard->board[x][y]->name == oQueen) {
					CheckPos.push_back({ x,y });
					break;
				}
				else if (myBoard->board[x][y]->name[0] != ' ')
					break;
				x += tempRook->dRow[i];
				y += tempRook->dColumn[i];
			}
		}

		//queen and bishop
		Bishop* tempBishop = new Bishop;
		for (int i = 0; i < 4; i++)
		{
			x = _xKing + tempBishop->dRow[i];
			y = _yKing + tempBishop->dColumn[i];
			while (x and x < 9 and y and y < 9) {
				if (myBoard->board[x][y]->name == oBishop || myBoard->board[x][y]->name == oQueen)
				{
					CheckPos.push_back({ x,y });
					break;
				}
				else if (myBoard->board[x][y]->name[0] != ' ')
					break;
				x += tempBishop->dRow[i];
				y += tempBishop->dColumn[i];
			}
		}

		//Knight 
		for (int i = 0; i < 8; i++) {
			x = _xKing + Knight().dRow[i];
			y = _yKing + Knight().dColumn[i];
			if (x and x < 9 and y and y < 9) {
				if (myBoard->board[x][y]->name == oKnight)
				{
					CheckPos.push_back({ x,y });
					break;
				}
				else if (myBoard->board[x][y]->name[0] != ' ')
					break;
			}
		}

		x = _xKing;
		y = _yKing;
		if (opponentColor == 'B') //black pawn
		{
			x--;
			y--;
			if (x and x < 9 and y and y < 9 and myBoard->board[x][y]->name == "BPA ")
				CheckPos.push_back({ x,y });
			y += 2;
			if (x and x < 9 and y and y < 9 and myBoard->board[x][y]->name == "BPA ")
				CheckPos.push_back({ x,y });
		}
		else //white pawn
		{
			x = _xKing + 1;
			y = _yKing + 1;
			if (x and x < 9 and y and y < 9 and myBoard->board[x][y]->name == "WPA ")
				CheckPos.push_back({ x,y });
			y -= 2;
			if (x and x < 9 and y and y < 9 and myBoard->board[x][y]->name == "WPA ")
				CheckPos.push_back({ x,y });
		}

		return CheckPos;
	}
	vector<Piece*> Block(Board* myBoard, Piece* myPiece)
	{
		int _xKing = GetKing(myBoard, myPiece).first;
		int _yKing = GetKing(myBoard, myPiece).second;
		vector<Piece*>Blocks;

		char opponentColor = (myPiece->name[0] == 'W' ? 'B' : 'W');
		string  oBishop = "XBI ", oQueen = "XQU ", oRook = "XRO ";
		oBishop[0] = opponentColor; oQueen[0] = opponentColor; oRook[0] = opponentColor;
		Bishop* tempBishop = new Bishop;

		int x = _xKing, y = _yKing;
		bool FoundPawn = 0;
		for (int i = 0; i < 4; i++) {
			x = _xKing + tempBishop->dRow[i];
			y = _yKing + tempBishop->dColumn[i];
			while (x and x < 9 and y and y < 9) {
				if (x == myPiece->row and y == myPiece->column) {
					FoundPawn = 1;
				}
				else if ((myBoard->board[x][y]->name == oBishop || myBoard->board[x][y]->name == oQueen) and FoundPawn) {
					Blocks.push_back(myBoard->board[x][y]);
					break;
				}
				else if (myBoard->board[x][y]->name != " . ") {
					break;
				}
				x += tempBishop->dRow[i];
				y += tempBishop->dColumn[i];
			}
		}
		x = _xKing; y = _yKing;
		FoundPawn = 0;
		Rook* tempRook = new Rook;
		for (int i = 0; i < 4; i++) {
			x = _xKing + tempRook->dRow[i];
			y = _yKing + tempRook->dColumn[i];
			while (x and x < 9 and y and y < 9) {
				if (x == myPiece->row and y == myPiece->column) {
					FoundPawn = 1;
				}
				else if ((myBoard->board[x][y]->name == oRook || myBoard->board[x][y]->name == oQueen) and FoundPawn) {
					Blocks.push_back(myBoard->board[x][y]);
					break;
				}
				x += tempRook->dRow[i];
				y += tempRook->dColumn[i];
			}
		}
		return Blocks;
	}
	vector<vector<string>> GetMyMoves(Board* myBoard, Piece* myPiece)
	{
		vector<vector<string>>tempBoard(9, vector<string>(9));
		Piece* tempPawn = new Pawn;
		tempPawn = myPiece;

		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				tempBoard[i][j] = myBoard->board[i][j]->name;
			}
		}
		int x = myPiece->row, y = myPiece->column;
		char opponentColor = (myPiece->name[0] == 'W' ? 'B' : 'W');
		if (myPiece->name == "WPA ")
		{
			if (x > 1) {
				if (myBoard->board[x - 1][y]->name[0] == ' ') {
					tempBoard[x - 1][y][1] = '*';
					if (myBoard->board[x - 2][y]->name[0] == ' ' and myPiece->row == 7) {
						tempBoard[x - 2][y][1] = '*';
					}
				}

				if (y < 8 and tempBoard[x - 1][y + 1][0] == opponentColor) {
					tempBoard[x - 1][y + 1][1] = '*';
				}
				if (y > 1 and tempBoard[x - 1][y - 1][0] == opponentColor) {
					tempBoard[x - 1][y - 1] = '*';
				}
			}


		}
		else {
			if (x < 8) {
				if (myBoard->board[x + 1][y]->name[0] == ' ') {
					tempBoard[x + 1][y][1] = '*';
					if (myBoard->board[x + 2][y]->name[0] == ' ' and myPiece->row==2) {
						tempBoard[x + 2][y][1] = '*';
					}
				}
				if (y < 8 and tempBoard[x + 1][y + 1][0] == opponentColor) {
					tempBoard[x + 1][y][1] = '*';
				}
				if (y > 1 and tempBoard[x + 1][y - 1][0] == opponentColor) {
					tempBoard[x + 1][y - 1] = '*';
				}
			}

		}
		return tempBoard;
	}
	bool CanMove(Board* myBoard, Piece* myPiece)
	{
		vector<pair<int, int>>myChecks = Check(myBoard, myPiece);
		vector<Piece*>myBlocks = Block(myBoard, myPiece);
		vector<vector<string>>tempBoard = GetMyMoves(myBoard, myPiece);
		int _xKing = GetKing(myBoard, myPiece).first;
		int _yKing = GetKing(myBoard, myPiece).second;

		if (myChecks.size() > 1 || myBlocks.size() > 1)
			return 0;

		char opponentColor = (myPiece->name[0] == 'W' ? 'B' : 'W');
		string oRook = "XRO ", oBishop = "XBI ", oQueen = "XQU ", oKnight = "XKN ", oPawn = "XPA ";
		oRook[0] = opponentColor; oBishop[0] = opponentColor; oQueen[0] = opponentColor; oKnight[0] = opponentColor;
		oPawn[0] = opponentColor;

		bool validPos = 0;
		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				if (tempBoard[i][j][0] == ' ' and tempBoard[i][j][1] == '*') {
					validPos = 1;
					break;
				}
				else if (tempBoard[i][j][0] == opponentColor and tempBoard[i][j][3] == '*') {
					validPos = 1;
					break;
				}
			}
		}
		if (!validPos) {
			return 0;
		}
		int myRow = myPiece->row, myCol = myPiece->column;

		if (myChecks.size()) {
			Piece* temp = myBoard->board[myChecks[0].first][myChecks[0].second];
			if (temp->name == oPawn || temp->name == oKnight) {
				return 0;
			}

			if (tempBoard[temp->row][temp->column][3] == '*')
				return 1;

			if (temp->name == oRook) {
				int idx = -1;
				for (int i = 0; i < 4; i++) {
					int x = _xKing + Rook().dRow[i];
					int y = _yKing + Rook().dColumn[i];
					while (x and x < 9 and y and y < 9) {
						if (x == temp->row and y == temp->column) {
							idx = i;
							break;
						}
						x += Rook().dRow[i];
						y += Rook().dColumn[i];
					}
					if (idx > -1) {
						break;
					}
				}

				if (idx > -1) {
					int x = _xKing + Rook().dRow[idx];
					int y = _yKing + Rook().dColumn[idx];
					while (x and x < 9 and y and y < 9) {
						if (tempBoard[x][y][1] == '*')
							return 1;
						x += Rook().dRow[idx];
						y += Rook().dColumn[idx];
					}
				}
				return 0;
			}
			else if (temp->name == oBishop) {
				int idx = -1;
				for (int i = 0; i < 4; i++) {
					int x = _xKing + Bishop().dRow[i];
					int y = _yKing + Bishop().dColumn[i];
					while (x and x < 9 and y and y < 9) {
						if (x == temp->row and y == temp->column) {
							idx = i;
							break;
						}
						x += Bishop().dRow[i];
						y += Bishop().dColumn[i];
					}
					if (idx > -1) {
						break;
					}
				}

				if (idx > -1) {
					int x = _xKing + Bishop().dRow[idx];
					int y = _yKing + Bishop().dColumn[idx];
					while (x and x < 9 and y and y < 9) {
						if (tempBoard[x][y][1] == '*')
							return 1;
						x += Bishop().dRow[idx];
						y += Bishop().dColumn[idx];
					}
				}
				return 0;
			}
			else if (temp->name == oQueen) {
				int idx = -1;
				for (int i = 0; i < 8; i++) {
					int x = _xKing + Queen().dRow[i];
					int y = _yKing + Queen().dColumn[i];
					while (x and x < 9 and y and y < 9) {
						if (x == temp->row and y == temp->column) {
							idx = i;
							break;
						}
						x += Queen().dRow[i];
						y += Queen().dColumn[i];
					}
					if (idx > -1) {
						break;
					}
				}

				if (idx > -1) {
					int x = _xKing + Queen().dRow[idx];
					int y = _yKing + Queen().dColumn[idx];
					while (x and x < 9 and y and y < 9) {
						if (tempBoard[x][y][1] == '*' || tempBoard[x][y][3] == '*')
							return 1;
						x += Queen().dRow[idx];
						y += Queen().dColumn[idx];
					}
				}
				return 0;
			}
		}

		if (myBlocks.size()) {
			if (myBlocks[0]->name == oBishop)
				return 0;
			if (myBlocks[0]->column == _yKing and myCol == _yKing and myRow > min(_xKing, myBlocks[0]->row) and myRow < max(_xKing, myBlocks[0]->row))
				return 1;
			return 0;
		}

		return 1;
	}

	Board AllValidMove(Board* myBoard, Piece* myPiece)
	{
		Board newBoard = *myBoard;
		vector<pair<int, int>>myChecks = Check(myBoard, myPiece);
		vector<Piece*>myBlocks = Block(myBoard, myPiece);
		vector<vector<string>>tempBoard = GetMyMoves(myBoard, myPiece);
		char opponentColor = (myPiece->name[0] == 'W' ? 'B' : 'W');
		string oRook = "XRO ", oBishop = "XBI ", oQueen = "XQU ";
		oRook[0] = opponentColor; oBishop[0] = opponentColor; oQueen[0] = opponentColor;
		int _xKing = GetKing(myBoard, myPiece).first;
		int _yKing = GetKing(myBoard, myPiece).second;

		if (!myChecks.size() and !myBlocks.size()) {
			for (int i = 1; i < 9; i++) {
				for (int j = 1; j < 9; j++) {
					newBoard.board[i][j]->name = tempBoard[i][j];
				}
			}
		}
		else if (myChecks.size()) {
			Piece* tempPiece = myBoard->board[myChecks[0].first][myChecks[0].second];
			int idx = -1, x, y;
			if (tempPiece->name == oRook) {
				for (int i = 0; i < 4; i++) {
					x = _xKing + Rook().dRow[i];
					y = _yKing + Rook().dColumn[i];
					while (x and x < 9 and y and y < 9) {
						if (x == myChecks[0].first and y == myChecks[0].second) {
							idx = i;
							break;
						}
						x += Rook().dRow[i];
						y += Rook().dColumn[i];
					}
					if (idx > -1) {
						break;
					}
				}
				if (idx > -1) {
					x = _xKing + Rook().dRow[idx];
					y = _yKing + Rook().dColumn[idx];
					while (x and x < 9 and y and y < 9) {
						if (tempBoard[x][y][1] == '*') {
							newBoard.board[x][y]->name[1] = '*';
						}
						else if (tempBoard[x][y][3] == '*') {
							newBoard.board[x][y]->name[3] = '*';
							break;
						}
						else {
							break;
						}
						x += Rook().dRow[idx];
						y += Rook().dColumn[idx];
					}
				}
			}
			else if (tempPiece->name == oBishop) {
				for (int i = 0; i < 4; i++) {
					x = _xKing + Bishop().dRow[i];
					y = _yKing + Bishop().dColumn[i];
					while (x and x < 9 and y and y < 9) {
						if (x == myChecks[0].first and y == myChecks[0].second) {
							idx = i;
							break;
						}
						x += Bishop().dRow[i];
						y += Bishop().dColumn[i];
					}
					if (idx > -1) {
						break;
					}
				}
				if (idx > -1) {
					x = _xKing + Bishop().dRow[idx];
					y = _yKing + Bishop().dColumn[idx];
					while (x and x < 9 and y and y < 9) {
						if (tempBoard[x][y][1] == '*') {
							newBoard.board[x][y]->name[1] = '*';
						}
						else if (tempBoard[x][y][3] == '*') {
							newBoard.board[x][y]->name[3] = '*';
							break;
						}
						else {
							break;
						}
						x += Bishop().dRow[idx];
						y += Bishop().dColumn[idx];
					}
				}
			}
			else if (tempPiece->name == oQueen) {
				for (int i = 0; i < 8; i++) {
					x = _xKing + Queen().dRow[i];
					y = _yKing + Queen().dColumn[i];
					while (x and x < 9 and y and y < 9) {
						if (x == myChecks[0].first and y == myChecks[0].second) {
							idx = i;
							break;
						}
						x += Queen().dRow[i];
						y += Queen().dColumn[i];
					}
					if (idx > -1) {
						break;
					}
				}
				if (idx > -1) {
					x = _xKing + Queen().dRow[idx];
					y = _yKing + Queen().dColumn[idx];
					while (x and x < 9 and y and y < 9) {
						if (tempBoard[x][y][1] == '*') {
							newBoard.board[x][y]->name[1] = '*';
						}
						else if (tempBoard[x][y][3] == '*') {
							newBoard.board[x][y]->name[3] = '*';
							break;
						}
						else {
							break;
						}
						x += Queen().dRow[idx];
						y += Queen().dColumn[idx];
					}
				}
			}
		}
		else {
			Piece* tempPiece = myBlocks[0];
			int idx = -1, myRow = myPiece->row, myCol = myPiece->column;
			if (tempPiece->name == oRook) {
				for (int i = 0; i < 4; i++) {
					int x = myRow + Rook().dRow[i];
					int y = myCol + Rook().dColumn[i];
					while (x and x < 9 and y and y < 9) {
						if (x == tempPiece->row and y == tempPiece->column) {
							idx = i;
							break;
						}
						x += Rook().dRow[i];
						y += Rook().dColumn[i];
					}
					if (idx > -1) {
						break;
					}
				}
				if (idx > -1) {
					int x = myRow + Rook().dRow[idx];
					int y = myCol + Rook().dColumn[idx];
					while (x and x < 9 and y and y < 9) {
						if (tempBoard[x][y][1] == '*') {
							newBoard.board[x][y]->name[1] = '*';
						}
						else if (tempBoard[x][y][3] == '*') {
							newBoard.board[x][y]->name[3] = '*';
							break;
						}
						else {
							break;
						}
						x += Rook().dRow[idx];
						y += Rook().dColumn[idx];
					}
				}
			}
			else if (tempPiece->name == oQueen) {
				for (int i = 0; i < 9; i++) {
					int x = myRow + Queen().dRow[i];
					int y = myCol + Queen().dColumn[i];
					while (x and x < 9 and y and y < 9) {
						if (x == tempPiece->row and y == tempPiece->column) {
							idx = i;
							break;
						}
						x += Queen().dRow[i];
						y += Queen().dColumn[i];
					}
					if (idx > -1) {
						break;
					}
				}
				if (idx > -1) {
					int x = myRow + Queen().dRow[idx];
					int y = myCol + Queen().dColumn[idx];
					while (x and x < 9 and y and y < 9) {
						if (tempBoard[x][y][1] == '*') {
							newBoard.board[x][y]->name[1] = '*';
						}
						else if (tempBoard[x][y][3] == '*') {
							newBoard.board[x][y]->name[3] = '*';
							break;
						}
						else {
							break;
						}
						x += Queen().dRow[idx];
						y += Queen().dColumn[idx];
					}
				}
			}
		}
		return newBoard;
	}

	Board MakeMove(int x, int y, Board* myBoard, Piece* myPiece)
	{
		Board newBoard = *myBoard;
		int prevX = myPiece->row;
		int prevY = myPiece->column;
		if ((myPiece->name == "WPA " and x > 1) || (myPiece->name == "BPA " and x<8)) {
			newBoard.board[x][y] = new Pawn;
			newBoard.board[x][y]->name = myPiece->name;
			newBoard.board[x][y]->Type = myPiece->Type;
			newBoard.board[x][y]->row = x;
			newBoard.board[x][y]->column = y;
			myBoard->board[x][y] = new Pawn;
			myBoard->board[x][y]->name = myPiece->name;
			myBoard->board[x][y]->Type = myPiece->Type;
			myBoard->board[x][y]->row = x;
			myBoard->board[x][y]->column = y;
		}
		else {
			if (myPiece->name == "WPA ") {
				if (x == 1) {
					cout << "promote the pawn\nenter :\n";
					cout << "\t1 : Queen\t\n\t2 : Rook\t\n\t3 : Knight\t\n\t4 : Bishop\t\n\t5 : Pawn\n";
					int choice;
					cin >> choice;
					if (choice == 1) {
						newBoard.board[x][y] = new Queen;
						newBoard.board[x][y]->row = x;
						newBoard.board[x][y]->column = y;
						newBoard.board[x][y]->name = "WQU ";
						newBoard.board[x][y]->Type = myPiece->Type;
						myBoard->board[x][y] = new Queen;
						myBoard->board[x][y]->name = "WQU ";
						myBoard->board[x][y]->Type = myPiece->Type;
						myBoard->board[x][y]->row = x;
						myBoard->board[x][y]->column = y;

					}
					else if (choice == 2) {
						newBoard.board[x][y] = new Rook;
						newBoard.board[x][y]->row = x;
						newBoard.board[x][y]->column = y;
						newBoard.board[x][y]->name = "WRO ";
						newBoard.board[x][y]->Type = myPiece->Type;
						myBoard->board[x][y] = new Rook;
						myBoard->board[x][y]->name = "WRO ";
						myBoard->board[x][y]->Type = myPiece->Type;
						myBoard->board[x][y]->row = x;
						myBoard->board[x][y]->column = y;
					}
					else if (choice == 3) {
						newBoard.board[x][y] = new Knight;
						newBoard.board[x][y]->row = x;
						newBoard.board[x][y]->column = y;
						newBoard.board[x][y]->name = "WKN ";
						newBoard.board[x][y]->Type = myPiece->Type;
						myBoard->board[x][y] = new Knight;
						myBoard->board[x][y]->name = "WKN ";
						myBoard->board[x][y]->Type = myPiece->Type;
						myBoard->board[x][y]->row = x;
						myBoard->board[x][y]->column = y;
					}
					else if (choice == 4) {
						newBoard.board[x][y] = new Bishop;
						newBoard.board[x][y]->row = x;
						newBoard.board[x][y]->column = y;
						newBoard.board[x][y]->name = "WBI ";
						newBoard.board[x][y]->Type = myPiece->Type;
						myBoard->board[x][y] = new Bishop;
						myBoard->board[x][y]->name = "WBI ";
						myBoard->board[x][y]->Type = myPiece->Type;
						myBoard->board[x][y]->row = x;
						myBoard->board[x][y]->column = y;
					}
				}
			}
			else {
				if (x == 8) {
					cout << "promote the pawn\nenter :\n";
					cout << "\t1 : Queen\t\n\t2 : Rook\t\n\t3 : Knight\t\n\t4 : Bishop\t\n\t5 : Pawn\n";
					int choice;
					cin >> choice;
					if (choice == 1) {
						newBoard.board[x][y] = new Queen;
						newBoard.board[x][y]->row = x;
						newBoard.board[x][y]->column = y;
						newBoard.board[x][y]->name = "BQU ";
						newBoard.board[x][y]->Type = myPiece->Type;
						myBoard->board[x][y] = new Queen;
						myBoard->board[x][y]->name = "BQU ";
						myBoard->board[x][y]->Type = myPiece->Type;
						myBoard->board[x][y]->row = x;
						myBoard->board[x][y]->column = y;
					}
					else if (choice == 2) {
						newBoard.board[x][y] = new Rook;
						newBoard.board[x][y]->row = x;
						newBoard.board[x][y]->column = y;
						newBoard.board[x][y]->name = "BRO ";
						newBoard.board[x][y]->Type = myPiece->Type;
						myBoard->board[x][y] = new Rook;
						myBoard->board[x][y]->name = "BRO ";
						myBoard->board[x][y]->Type = myPiece->Type;
						myBoard->board[x][y]->row = x;
						myBoard->board[x][y]->column = y;
					}
					else if (choice == 3) {
						newBoard.board[x][y] = new Knight;
						newBoard.board[x][y]->row = x;
						newBoard.board[x][y]->column = y;
						newBoard.board[x][y]->name = "BKN ";
						newBoard.board[x][y]->Type = myPiece->Type;
						myBoard->board[x][y] = new Knight;
						myBoard->board[x][y]->name = "BKN ";
						myBoard->board[x][y]->Type = myPiece->Type;
						myBoard->board[x][y]->row = x;
						myBoard->board[x][y]->column = y;
					}
					else if (choice == 4) {
						newBoard.board[x][y] = new Bishop;
						newBoard.board[x][y]->row = x;
						newBoard.board[x][y]->column = y;
						newBoard.board[x][y]->name = "BBI ";
						newBoard.board[x][y]->Type = myPiece->Type;
						myBoard->board[x][y] = new Bishop;
						myBoard->board[x][y]->name = "BBI ";
						myBoard->board[x][y]->Type = myPiece->Type;
						myBoard->board[x][y]->row = x;
						myBoard->board[x][y]->column = y;
					}
				}
			}
		}	
		myBoard->board[prevX][prevY] = new Piece;
		myBoard->board[prevX][prevY]->row = prevX;
		myBoard->board[prevX][prevY]->column = prevY;
		newBoard.board[prevX][prevY] = new Piece;
		newBoard.board[prevX][prevY]->row = prevX;
		newBoard.board[prevX][prevY]->column = prevY;
		return newBoard;
	}

};

