#include <bits/stdc++.h>
#include "System.h"

#include"BoardServices.h"
#include"BishopService.h"

using namespace std;
int main()
{

	Board* b = new Board;
	
	Piece* p = b->board[8][3];
	BishopService x;
	
	//cout << "\nDone1!\n";
	Board xx = x.AllValidMove(b, p);
	BoardServices().DisplayBoard(&xx);
	cout << "\n\n\n";
	x.MakeMove(7, 4, b, p);
	BoardServices().DisplayBoard(b);
	cout << "\n\n\n";
	p = b->board[7][4];
	//Board xxx = x.AllValidMove(b, p);
	//BoardServices().DisplayBoard(&xxx);
	//System::Run();
	//cout << "\nDone!\n";
}