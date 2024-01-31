

#pragma once
#include"IPieceService.h"
class RookServices : public IPieceService
{
private:
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
		return {0,0};
	}

	vector<pair<int, int>> Check(Board* myBoard, Piece* myPiece)
	{
		vector<pair<int, int>> CheckPos;

		char opponentColor = (myPiece->name[0] == 'W' ? 'B' : 'W');
		string oRook = "XRO ", oBishop = "XBI ", oQueen = "XQU ", oKnight = "XKN ", oPawn = "XPA ";
		oRook[0] = opponentColor; oBishop[0] = opponentColor; oQueen[0] = opponentColor; oKnight[0] = opponentColor;
		oPawn[0] = opponentColor;

		pair<int, int> myKingPos = GetKing(myBoard, myPiece);
		int _xKing = myKingPos.first, _yKing = myKingPos.second,x,y;


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
		Knight* tempKnight = new Knight;
		for (int i = 0; i < 8; i++) {
			x = _xKing + tempKnight->dRow[i];
			y = _yKing + tempKnight->dColumn[i];
			if (myBoard->board[x][y]->name == oKnight)
			{
				CheckPos.push_back({ x,y });
				break;
			}
			else if (myBoard->board[x][y]->name[0] != ' ')
				break;
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
		string  oBishop = "XBI ", oQueen = "XQU ";
	    oBishop[0] = opponentColor; oQueen[0] = opponentColor;
		Bishop* tempBishop = new Bishop;

		int x = _xKing, y = _yKing;
		bool FoundRook = 0;
		for (int i = 0; i < 4; i++) {
			x = _xKing + tempBishop->dRow[i];
			y = _yKing + tempBishop->dColumn[i];
			while (x and x < 9 and y and y < 9) {
				if (x == myPiece->row and y == myPiece->column) {
					FoundRook = 1;
				}
				else if ((myBoard->board[x][y]->name == oBishop || myBoard->board[x][y]->name == oQueen) and FoundRook) {
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
		return Blocks;
	}
	vector<Piece*>RookBlocks(Board* myBoard, Piece* myPiece)
	{
		int _xKing = GetKing(myBoard, myPiece).first;
		int _yKing = GetKing(myBoard, myPiece).second;
		vector<Piece*>Blocks;

		char opponentColor = (myPiece->name[0] == 'W' ? 'B' : 'W');
		string oRook = "XRO ", oQueen = "XQU ";
		oRook[0] = opponentColor; oQueen[0] = opponentColor;
		Rook* tempRook = new Rook;

		int x = _xKing, y = _yKing;
		bool FoundRook = 0;
		for (int i = 0; i < 4; i++) {
			x = _xKing + tempRook->dRow[i];
			y = _yKing + tempRook->dColumn[i];
			while (x and x < 9 and y and y < 9) {
				if (x==myPiece->row and y==myPiece->column) {
					FoundRook = 1;
				}
				else if ((myBoard->board[x][y]->name == oRook || myBoard->board[x][y]->name == oQueen) and FoundRook) {
					Blocks.push_back(myBoard->board[x][y]);
					break;
				}
				else if (myBoard->board[x][y]->name != " . ") {
					break;
				}
				x += tempRook->dRow[i];
				y += tempRook->dColumn[i];
			}
		}
		return Blocks;

	}
	vector<vector<string>>GetMyMoves(Board* myBoard, Piece* myPiece)
	{
		vector<vector<string>>tempBoard(9, vector<string>(9));
		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				tempBoard[i][j] = myBoard->board[i][j]->name;
			}
		}
		char opponentColor = (myPiece->name[0] == 'W' ? 'B' : 'W');

		int _xRook = myPiece->row , _yRook = myPiece->column;

		Rook* tempRook = new Rook;
		for (int i = 0; i < 4; i++)
		{
			int x = _xRook + tempRook->dRow[i];
			int y = _xRook + tempRook->dColumn[i];
			while (x and x < 9 and y and y < 9) {
				if (tempBoard[x][y][0] == opponentColor) {
					tempBoard[x][y][3] = '*';
					break;
				}
				else if (tempBoard[x][y][0] == ' ') {
					tempBoard[x][y][1] = '*';
				}
				else {
					break;
				}
				x+= tempRook->dRow[i];
				y+= tempRook->dColumn[i];
			}
		}
		return tempBoard;

	}
	public:
	//CanMove(Board* myBoard , Piece* myPiece) : bool
	bool CanMove(Board* myBoard, Piece* myPiece)
	{
		vector<pair<int, int>>myChecks = Check(myBoard, myPiece);
		vector<Piece*>myBlocks = Block(myBoard, myPiece);
		vector<Piece*>myRookBlocks = RookBlocks(myBoard, myPiece);

		if (myChecks.size() > 1 || myBlocks.size() || myRookBlocks.size()>1)
			return 0;

		char opponentColor = (myPiece->name[0] == 'W' ? 'B' : 'W');
		string oRook = "XRO ", oBishop = "XBI ", oQueen = "XQU ", oKnight = "XKN ", oPawn = "XPA ";
		oRook[0] = opponentColor; oBishop[0] = opponentColor; oQueen[0] = opponentColor; oKnight[0] = opponentColor;
		oPawn[0] = opponentColor;

		vector<vector<string>>tempBoard = GetMyMoves(myBoard, myPiece);
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


		int _xKing = GetKing(myBoard, myPiece).first;
		int _yKing = GetKing(myBoard, myPiece).second;

		if(myChecks.size()){
			Piece* temp = myBoard->board[myChecks[0].first][myChecks[0].second];
			if (temp->name == oPawn || temp->name == oKnight) {
				return 0;
			}

			if (temp->name == oRook) {
				int idx = -1;
				for (int i = 0; i < 4; i++) {
					int x = _xKing + Rook().dRow[i];
					int y = _yKing + Rook().dColumn[i];
					while (x and x < 9 and y and y < 9) {
						if (myBoard->board[x][y] == temp) {
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
						if (tempBoard[x][y][1] == '*' || tempBoard[x][y][3] == '*')
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
						if (myBoard->board[x][y] == temp) {
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
						if (tempBoard[x][y][1] == '*' || tempBoard[x][y][3] == '*')
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
						if (myBoard->board[x][y] == temp) {
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

		if (myRookBlocks.size())
			return 1;

		if (!myChecks.size() and validPos)
			return 1;
		else
			return 0;
	}
	Board AllValidMove(Board* myBoard, Piece* myPiece)
	{
		Board newBoard = *myBoard; 
		vector<vector<string>>myMoves = GetMyMoves(myBoard, myPiece);
		vector<pair<int, int>>myChecks = Check(myBoard, myPiece);
		vector<Piece*>myRookBlocks = RookBlocks(myBoard, myPiece);

		int _xKing = GetKing(myBoard, myPiece).first;
		int _yKing = GetKing(myBoard, myPiece).second;

		char opponentColor = (myPiece->name[0] == 'W' ? 'B' : 'W');
		string oRook = "XRO ", oBishop = "XBI ", oQueen = "XQU ";
		oRook[0] = opponentColor; oBishop[0] = opponentColor; oQueen[0] = opponentColor;

		if (myChecks.size() == 0 and myRookBlocks.size() == 0) {
			for (int i = 1; i < 9; i++) {
				for (int j = 1; j < 9; j++) {
					newBoard.board[i][j]->name = myMoves[i][j];
				}
			}			
		}
		else if (myChecks.size()) {
			Piece* tempPiece = myBoard->board[myChecks[0].first][myChecks[0].second];
			int idx = -1 , x , y;
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
						if (myMoves[x][y][1] == '*'){
							newBoard.board[x][y]->name[1] = '*';
						}
						else if (myMoves[x][y][3] == '*') {
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
						if (myMoves[x][y][1] == '*') {
							newBoard.board[x][y]->name[1] = '*';
						}
						else if (myMoves[x][y][3] == '*') {
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
						if (myMoves[x][y][1] == '*') {
							newBoard.board[x][y]->name[1] = '*';
						}
						else if (myMoves[x][y][3] == '*') {
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
		else if (myRookBlocks.size()) {
			Piece* tempPiece = myRookBlocks[0];
			int idx = -1, myRow = myPiece->row , myCol = myPiece->column;
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
						if (myMoves[x][y][1] == '*') {
							newBoard.board[x][y]->name[1] = '*';
						}
						else if (myMoves[x][y][3] == '*') {
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
						if (myMoves[x][y][1] == '*') {
							newBoard.board[x][y]->name[1] = '*';
						}
						else if (myMoves[x][y][3] == '*') {
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
		newBoard.board[x][y] = new Rook;
		newBoard.board[x][y]->name = myPiece->name;
		newBoard.board[x][y]->Type = myPiece->Type;
		newBoard.board[x][y]->row = x;
		newBoard.board[x][y]->row = y;

		newBoard.board[myPiece->row][myPiece->column] = new Piece;
		newBoard.board[myPiece->row][myPiece->column]->row = myPiece->row;
		newBoard.board[myPiece->row][myPiece->column]->column = myPiece->column;

		return newBoard;
	}
};
