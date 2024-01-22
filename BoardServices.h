#pragma once
#include "Board.h"
#include <iostream>
using namespace std;
class BoardServices
{
public:
	void DisplayBoard(Board* myBoard) {
		for (int myRow = 1; myRow <= 8; myRow++)
		{
			cout << myRow << " ";
			for (int myColumn = 1; myColumn <= 8; myColumn++) 
			{
				if (myBoard->board[myRow][myColumn] == nullptr)
				{
					cout << ".   ";
				}
				else
				{
					cout <<myBoard->board[myRow][myColumn]->name << " ";
				}
			}
			cout << "\n";
		}
		cout << "  ";
		for (int i = 0; i < 8; i++) {
			cout << (char)('H' - i) << "   ";
		}
	}
};

