#include <bits/stdc++.h>
#include "System.h"

#include"BoardServices.h"
#include"BishopService.h"

using namespace std;
int main()
{


	BoardServices().DisplayBoard(new Board);
	cout << "\n\n\n";
	Board* b = new Board;
	
	Piece* p = b->board[8][3];
	BishopService x;
	
	Board xx = x.AllValidMove(b, p);
	BoardServices().DisplayBoard(&xx);
	//System::Run();
	cout << "\nDone!";
}