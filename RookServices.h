

#pragma once
#include"IPieceService.h"
class RookServices : public IPieceService
{
private:
	vector<pair<int, int>>PossiblePos;
	pair<int, int> GetKing(Board* myBoard, Piece* myPiece)
	{
		char color = myPiece->name[0];
		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				if (myBoard->board[i][j]->name == color + "KI ")
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
		string oRook = opponentColor + "RO ";
		string oBishop = opponentColor + "BI ";
		string oKnight = opponentColor + "KN ";
		string oQueen = opponentColor + "QU ";
		string oPawn = opponentColor + "PA ";

		pair<int, int> myKingPos = GetKing(myBoard, myPiece);
		int _xKing = myKingPos.first, _yKing = myKingPos.second;


		//rook and queen
		for (int i = _xKing - 1; i > 0; i--) {
			if (myBoard->board[i][_yKing]->name == opponentColor + "RO " || myBoard->board[i][_yKing]->name == opponentColor + "QU ")
			{
				CheckPos.push_back({ i,_yKing });
				break;
			}
			else if (myBoard->board[i][_yKing]->name[0] != ' ')
				break;
		}

		for (int i = _xKing + 1; i < 9; i++) {
			if (myBoard->board[i][_yKing]->name == oRook || myBoard->board[i][_yKing]->name == oQueen)
			{
				CheckPos.push_back({ i,_yKing });
				break;
			}
			else if (myBoard->board[i][_yKing]->name[0] != ' ')
				break;
		}

		for (int j = _yKing - 1; j > 0; j--) {
			if (myBoard->board[_xKing][j]->name == oRook || myBoard->board[_xKing][j]->name == oQueen)
			{
				CheckPos.push_back({ _xKing,j });
				break;
			}
			else if (myBoard->board[_xKing][j]->name[0] != ' ')
				break;
		}

		for (int j = _yKing + 1; j < 9; j++) {
			if (myBoard->board[_xKing][j]->name == oRook || myBoard->board[_xKing][j]->name == oQueen)
			{
				CheckPos.push_back({ _xKing,j });
				break;
			}
			else if (myBoard->board[_xKing][j]->name[0] != ' ')
				break;
		}

		//queen and bishop
		int x = _xKing - 1, y = _yKing - 1;
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
		for (int i = 1; i < 9; i++) {
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

	vector<Piece*> KingBlock(Board* myBoard, Piece* myPiece)
	{
		int _xKing = GetKing(myBoard, myPiece).first;
		int _yKing = GetKing(myBoard, myPiece).second;
		vector<Piece*>Blocks;

		char opponentColor = (myPiece->name[0] == 'W' ? 'B' : 'W');
		string oBishop = opponentColor + "BI ";
		string oQueen = opponentColor + "QU ";
		Bishop* tempBishop = new Bishop;

		int x = _xKing, y = _yKing;
		bool FoundRook = 0;
		for (int i = 0; i < 4; i++) {
			x = _xKing + tempBishop->dRow[i];
			y = _yKing + tempBishop->dColumn[i];
			while (x and x < 9 and y and y < 9) {
				if (myBoard->board[x][y]->name == myPiece->name) {
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

	vector<pair<int, int>> GetAllMoves(Board* myBoard, Piece* myPiece) {
		char opponentColor = (myPiece->name[0] == 'W' ? 'B' : 'W');
		vector<pair<int, int>> myMoves;
		for (int i = 0; i < 4; i++) {
			int x = myPiece->row + Rook().dRow[i];
			int y = myPiece->column + Rook().dColumn[i];
			while (x and x < 9 and y and y < 9) {
				if (myBoard->board[x][y]->name[0]==' ' || myBoard->board[x][y]->name[0] == opponentColor) {
					myMoves.push_back({ x,y });
				}
				else {
					break;
				}
				x+= Rook().dRow[i];
				y+= Rook().dColumn[i];
			}
		}
		return myMoves;
	}
public:
	bool CanMove(Board* board, Piece* piece)
	{
		vector<pair<int, int>>myKingChecks = Check(board,piece);
		vector<Piece*>myBlocks = KingBlock(board, piece);

		if (myBlocks.size() > 1 || myKingChecks.size() > 1)
			return 0;

		if (myBlocks.size() &&  myKingChecks.size())
			return 0;
		
		char opponentColor = (piece->name[0] == 'W' ? 'B' : 'W');
		string oRook = opponentColor + "RO ";
		string oBishop = opponentColor + "BI ";
		string oKnight = opponentColor + "KN ";
		string oQueen = opponentColor + "QU ";
		string oPawn = opponentColor + "PA ";
		int _xRook = piece->row, _yRook = piece->column;

		if (myBlocks.size() == 1) {
			if (myBlocks[0]->name == oBishop) {
				return 0;
			}
			else
			{
				int x = _xRook, y = _yRook;
				Rook* tempRook = new Rook;
				for (int i = 0; i < 4; i++) {
					x = _xRook + tempRook->dRow[i];
				    y = _yRook + tempRook->dColumn[i];
					while (x and x<9 and y and y<9) {
						if(x == myBlocks[0]->row and y == myBlocks[0]->column){
							return 1;
						}
						x += tempRook->dRow[i];
						y += tempRook->dColumn[i];
					}
				}
				return 0;
			}
		}
		if (myKingChecks.size()){
			vector<vector<Piece>>myTempBoard;
			for (int i = 1; i < 9; i++)
			{
				for (int j = 1; j < 9; j++) {
					myTempBoard[i][j] = *(board->board[i][j]);
				}
			}

			Rook* tempRook = new Rook;
			int x = _xRook, y = _yRook;
			for (int i = 0; i < 4; i++) {
				x = _xRook + tempRook->dRow[i];
				y = _yRook + tempRook->dColumn[i];
				while (x and x < 9 and y and y < 9) {
					if (board->board[x][y]->name[0]== opponentColor) {
						myTempBoard[x][y].name[3] = '*';
						break;
					}
					else if (board->board[x][y]->name == " . ") {
						myTempBoard[x][y].name[1] = '*';
					}
					else {
						break;
					}
					x += tempRook->dRow[i];
					y += tempRook->dColumn[i];
				}
			}


			int idxRow = myKingChecks[0].first, idxCol = myKingChecks[0].second;
			x = _xRook;
			y = _yRook;
			int idxXKing = GetKing(board, piece).first;
			int idxYKing = GetKing(board, piece).second;

			if (board->board[idxRow][idxCol]->name == oRook) {
				for (int i = 0; i < 4; i++) {
					x = idxXKing+tempRook->dRow[i];
					y = idxYKing +tempRook->dColumn[i];
					while (x and x < 9 and y and y < 9) {
						if (myTempBoard[x][y].name[0] != ' ') {
							if (myTempBoard[x][y].name[3] == '*') {
								return 1;
							}
						}
						x += tempRook->dRow[i];
						y += tempRook->dColumn[i];
					}
				}
				return 0;
			}

			x = _xRook;y = _yRook;

		    if(board->board[idxRow][idxCol]->name == oBishop) {
				Bishop* tempBishop = new Bishop;
				for (int i = 0; i < 4; i++) {
					x = idxXKing + tempBishop->dRow[i];
					y = idxYKing + tempBishop->dColumn[i];
					while (x and x < 9 and y and y < 9) {
						if (myTempBoard[x][y].name[0] != ' ') {
							if (myTempBoard[x][y].name[3] == '*') {
								return 1;
							}
						}
						x += tempBishop->dRow[i];
						y += tempBishop->dColumn[i];
					}
				}
				return 0;
			}

			x = _xRook; y = _yRook;

		    if (board->board[idxRow][idxCol]->name == oKnight) {
				return 0;
			}

			x = _xRook; y = _yRook;

			if (board->board[idxRow][idxCol]->name == oQueen) {
				Queen* tempQueen = new Queen;
				for (int i = 0; i < 8; i++) {
					x = idxXKing + tempQueen->dRow[i];
					y = idxYKing + tempQueen->dColumn[i];
					while (x and x < 9 and y and y < 9) {
						if (myTempBoard[x][y].name[0] != ' ') {
							if (myTempBoard[x][y].name[3] == '*') {
								return 1;
							}
						}
						x += tempQueen->dRow[i];
						y += tempQueen->dColumn[i];
					}
				}
				return 0;
			}

			if (board->board[idxRow][idxCol]->name == oPawn) {
				return 0;
			}
					
		}
	}

	Board AllValidMove(Board* myBoard, Piece* myPiece) {//not functioning properly 
		Board myTempBoard = *myBoard;
		if (CanMove(myBoard, myPiece)) 
		{
			vector<pair<int, int>>myKingChecks = Check(myBoard, myPiece);
			vector<Piece*>myBlocks = KingBlock(myBoard, myPiece);

			vector<pair<int, int>>myMoves;
			vector<pair<int, int>>myValidMoves = GetAllMoves(myBoard, myPiece);

			char opponentColor = (myPiece->name[0] == 'W' ? 'B' : 'W');
			string oRook = opponentColor + "RO ";
			string oBishop = opponentColor + "BI ";
			string oKnight = opponentColor + "KN ";
			string oQueen = opponentColor + "QU ";
			string oPawn = opponentColor + "PA ";

			if (myKingChecks.size()) {
				int ox = myKingChecks[0].first, oy = myKingChecks[0].second;
				int idxXKing = GetKing(myBoard, myPiece).first;
				int idxYKing = GetKing(myBoard, myPiece).second;

				if (myBoard->board[ox][oy]->name == oRook) {
					Rook* tempRook = new Rook;
					for (int i = 0; i < 4; i++) {
						int x = idxXKing + tempRook->dRow[i];
						int y = idxYKing + tempRook->dColumn[i];
						vector<pair<int, int>>temp;
						bool ok = 0;
						while (x and x < 9 and y and y < 9) {
							temp.push_back({ x,y });
							if (x == ox and y == oy) {
								ok = 1;
								break;
							}
							x += tempRook->dRow[i];
							y+= tempRook->dColumn[i];
						}
						if (ok) {
							myMoves = temp;
							break;
						}
						else {
							temp.clear();
						}
					}
				}
				else if (myBoard->board[ox][oy]->name == oBishop){
					Bishop* tempBishop = new Bishop;
					for (int i = 0; i < 4; i++) {
						int x = idxXKing + tempBishop->dRow[i];
						int y = idxYKing + tempBishop->dColumn[i];
						vector<pair<int, int>>temp;
						bool ok = 0;
						while (x and x < 9 and y and y < 9) {
							temp.push_back({ x,y });
							if (x == ox and y == oy) {
								ok = 1;
								break;
							}
							x += tempBishop->dRow[i];
							y += tempBishop->dColumn[i];
						}
						if (ok) {
							myMoves = temp;
							break;
						}
						else {
							temp.clear();
						}
					}
				}
				else if (myBoard->board[ox][oy]->name == oQueen){
					Queen* tempQueen = new Queen;
					for (int i = 0; i < 9; i++) {
						int x = idxXKing + tempQueen->dRow[i];
						int y = idxYKing + tempQueen->dColumn[i];
						vector<pair<int, int>>temp;
						bool ok = 0;
						while (x and x < 9 and y and y < 9) {
							temp.push_back({ x,y });
							if (x == ox and y == oy) {
								ok = 1;
								break;
							}
							x += tempQueen->dRow[i];
							y += tempQueen->dColumn[i];
						}
						if (ok) {
							myMoves = temp;
							break;
						}
						else {
							temp.clear();
						}
					}
				}
				for (int i = 0; i < myValidMoves.size(); i++) {
					for (int j = 0; j < myMoves.size(); j++) {
						if (myValidMoves[i] == myMoves[j]) {
							if (myTempBoard.board[myValidMoves[i].first][myValidMoves[i].second]->name[0] == ' ')
								myTempBoard.board[myValidMoves[i].first][myValidMoves[i].second]->name[1] = '*';
							else if(myTempBoard.board[myValidMoves[i].first][myValidMoves[i].second]->name[0]==opponentColor)
								myTempBoard.board[myValidMoves[i].first][myValidMoves[i].second]->name[3] = '*';

						}
					}
				}
				return myTempBoard;
		    }
			if (myBlocks.size()) {
				Queen* tempQueen = new Queen;
				for (int i = 0; i < 9; i++) {
					int x = myPiece->row + tempQueen->dRow[i];
					int y = myPiece->column + tempQueen->dColumn[i];
					vector<pair<int, int>>temp;
					bool ok = 0;
					while (x and x < 9 and y and y < 9) {
						temp.push_back({ x,y });
						if (x == myBlocks[0]->row and y == myBlocks[0]->column) {
							ok = 1;
							break;
						}
						x += tempQueen->dRow[i];
						y += tempQueen->dColumn[i];
					}
					if (ok) {
						myMoves = temp;
						break;
					}
					else {
						temp.clear();
					}
				}
				for (int i = 0; i < myValidMoves.size(); i++) {
					for (int j = 0; j < myMoves.size(); j++) {
						if (myValidMoves[i] == myMoves[j]) {
							if (myTempBoard.board[myValidMoves[i].first][myValidMoves[i].second]->name[0] == ' ')
								myTempBoard.board[myValidMoves[i].first][myValidMoves[i].second]->name = " * ";
							else if (myTempBoard.board[myValidMoves[i].first][myValidMoves[i].second]->name[0] == opponentColor)
								myTempBoard.board[myValidMoves[i].first][myValidMoves[i].second]->name[3] = '*';
						}
					}
				}
				return myTempBoard;
			}

			for (int i = 0; i < myValidMoves.size(); i++) {
				if (myTempBoard.board[myValidMoves[i].first][myValidMoves[i].second]->name[0]==' ')
					myTempBoard.board[myValidMoves[i].first][myValidMoves[i].second]->name = " * ";
				else if (myTempBoard.board[myValidMoves[i].first][myValidMoves[i].second]->name[0] == opponentColor)
					myTempBoard.board[myValidMoves[i].first][myValidMoves[i].second]->name[3] = '*';
			}
		}
		return myTempBoard;
	}

	Board MakeMove(int x, int y, Board* myBoard, Piece* piece)
	{
		
	}
};

