#pragma once
#include "board.h";
#include "BoardServices.h";
#include "IPieceService.h";
#include"IKnightService.h"
#include "RookServices.h"
#include "PawnServices.h"
#include"KnightService.h"
#include "BishopService.h";
#include "IQueenService.h";
#include "KingService.h";
#include <conio.h>
#include <iostream> 
class game{
private:
	Board* CurrentBoard = new Board();
	Board ValidMoves;
	string SourcePos;
	string CurrnetPlayer = "White";
	Piece* MovingPiece;
	IPieceService* pieceService;
	BoardServices boardService;
	vector<string>ValidPos;
	pair<int, int>DistPos;
public:

	bool ValidatatePostion(string Pos){
		if (Pos.length() != 2) {
			return false;
		}
		char col = Pos[0], row = Pos[1];

		if (!isalpha(col) || col < 'A' || col > 'H') {// check row
			return false;
		}

		if (!isdigit(row) || row < '1' || row > '8') {// check column
			return false;
		}

		return true;
	}

	bool IsEmpty(string Pos) {
		int col = 8 - (Pos[0] - 'A') ;
		int row = (Pos[1] - '1') + 1;
		
		return CurrentBoard->board[row][col]->name==" .  ";
	}

	bool IsMyPiece(string Pos) {
		int col = 8 - (Pos[0] - 'A') ;
		int row = (Pos[1] - '1') + 1;
		
		return CurrentBoard->board[row][col]->Type == CurrnetPlayer;
	}

	string GetSourcePosition() {
		string Pos;
		cout << endl;
		while (true) {
			cout << "Enter the position of the piece you want to move (e.g., e4): ";
			cin >> Pos;
			
			if (!ValidatatePostion(Pos)) {
				cout << "Invalid position. Please try again." << endl;
				continue;
			}
			
			if (IsEmpty(Pos)) {
				cout << "The selected square is not occupied by a piece." << endl;
				continue;
			}

			if (!IsMyPiece(Pos)) {
				cout << "This is not your piece" << endl;
				continue;
			}
			
			return Pos;
		}
	}

	pair<int,int> GetDistPosition() {
		while (true) {
			boardService.DisplayBoard(&ValidMoves);
			string Move;

			cout << endl;
			cout << "Valid moves are highlighted. Enter one of them (e.g., e4): , or -1 move to another piece ";
			cin >> Move;
			
			if (Move == "-1")
				return make_pair(0, 0);

			int col = 8 - (Move[0] - 'A');
			int row = (Move[1] - '1') + 1;
			if (ValidMoves.board[row][col]->name == " *  " or ValidMoves.board[row][col]->name[3] == '*') {
				return make_pair(row, col);
			}
			else {
				cout << "Invalid move.Please choose a highlighted square or -1 to move to another piece. " << endl;
			}
		}
	}
	Piece* GetMovingPiece() {
		int col = 8 - (SourcePos[0] - 'A');
		int row = (SourcePos[1] - '1') + 1;

		return CurrentBoard->board[row][col];
	}
	void Init_IPieceService() {
		string name = MovingPiece->name;

		if (name == "BRO " or name == "WRO ") {
			pieceService = new RookServices();
		}

		if (name == "BKN " or name == "WKN ") {
			pieceService = new KnightService();
		}

		if (name == "BBI " or name == "WBI ") {
			pieceService = new BishopService();
		}

		if (name == "BQU " or name == "WQU ") {
			pieceService = new IQueenService();
		}

		if (name == "BPA " or name == "WPA ") {
			pieceService = new PawnServices();
		}

		if (name == "BKI " or name == "WKI ") {
			pieceService = new KingService();
		}
	}
	
	void SwitchPlayer() {
		if (CurrnetPlayer == "White")
			CurrnetPlayer = "Black";
		else
			CurrnetPlayer = "White";
	}

	bool anyMove() {
		for (int myRow = 1; myRow <= 8; myRow++)
		{
			for (int myColumn = 1; myColumn <= 8; myColumn++)
			{
				if (ValidMoves.board[myRow][myColumn]->name != CurrentBoard->board[myRow][myColumn]->name)
				{
					return true;
				}
			}
			
		}
		return false;
	}

	void play() {
		while (true) {
			system("cls");
			cout << "              " << CurrnetPlayer << " Move" << endl << endl;;
			boardService.DisplayBoard(CurrentBoard);

			SourcePos = GetSourcePosition();
			
			MovingPiece = GetMovingPiece();

			Init_IPieceService();

			ValidMoves = pieceService->AllValidMove(CurrentBoard, MovingPiece);
			
			if (!pieceService->CanMove(CurrentBoard, MovingPiece)) {
				cout << "Invalid Piece" << endl;
				continue;
			}
			
			system("cls");


			DistPos = GetDistPosition();

			if (DistPos.first==0)continue;
			
			pieceService->MakeMove(DistPos.first, DistPos.second, CurrentBoard, MovingPiece);

			SwitchPlayer();
		}
	}
};

