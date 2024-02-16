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
#include"BoardServices.h"
#include"IPieceService.h"
#include"BishopService.h"
#include"KnightService.h"
#include"Knight.h"
#include"IKnightService.h"
#include "PawnServices.h"
#include "KingService.h"
#include "RookServices.h"
using namespace std;
class System{


public:

	static bool Valid_input(char x, char y) {
		return (x >= '1' and x <= '9' and y >= 'A' and y <= 'H');
	}

	static void Run() {
		BishopService* BISer = new BishopService;
		KingService* KISer = new KingService;
		KnightService* KNSer = new KnightService;
		RookServices* ROSer = new RookServices;
		PawnServices* PASer = new PawnServices;
		//another color
		//cout << "033[1m\033[37m";
		Board MainBoard;
		int turn = 1, GameIsRunning = 1;
		while (GameIsRunning) {
			cout << (turn ? "White" : "Black") << " player\n\n";
			BoardServices().DisplayBoard(&MainBoard);
			cout << "Chose piece [x , y] : ";
			char Ch_x, Ch_y;
			cin >> Ch_x >> Ch_y;
			cout << '\n' << '\n';
			if (!Valid_input(Ch_x, Ch_y)) {
				cout << "Invalid possition\n\n";
				continue;
			}
			Ch_x -= '0';// reset to base 1
			Ch_y -= 'A';// reset to base 1
			Ch_y = 8 - Ch_y;
			//cout << (int)Ch_x << ' ' << (int)Ch_y << '\n';
			//continue;
			Piece* Ch_p = MainBoard.board[Ch_x][Ch_y];
			if (Ch_p->name[0] != (turn ? 'W' : 'B')) {
				cout << "Invalid piece\n\n";
				continue;
			}
			IPieceService* Serviece = PASer;
			if (Ch_p->name.substr(1, 2) == "BI") {
				Serviece = BISer;
			}
			else if (Ch_p->name.substr(1, 2) == "KI") {
				Serviece = KISer;
			}
			else if (Ch_p->name.substr(1, 2) == "KN") {
				Serviece = KNSer;
			}
			else if (Ch_p->name.substr(1, 2) == "PA") {
				Serviece = PASer;
			}
			else if (Ch_p->name.substr(1, 2) == "RO") {
				Serviece = ROSer;
			}
			else if (Ch_p->name.substr(1, 2) == "QU") {
				//Serviece = QUSer; // yalaa ya  ameeeeeeeeeeeeer
			}
			else {
				cout << "Invalid piece\n\n";
				continue;
			}
			bool CanMove = Serviece->CanMove(&MainBoard, Ch_p);
			if (!CanMove) {
				cout << "U can't move this piece \nchosse another piece\n\n";
				continue;
			}
			Board ValidPos = Serviece->AllValidMove(&MainBoard, Ch_p);
			cout << "\n\n";
			BoardServices().DisplayBoard(&ValidPos);
			cout << "\n\n";
			int op = 3;
			while (op >= 3) {
				cout << "Chosse \n1 : Chose move possition\n2 : change piece\nyour chosse : ";
				cin >> op;
				if (op == 1) {
					char newx, newy;
					cout << "Chose poss [ x , y ]"; cin >> newx >> newy;
					if (Valid_input(newx, newy)) {
						newx -= '0';
						newy -= 'A';// reset to base 1
						newy = 8 - newy;
						if (MainBoard.board[newx][newy]->name[0] != (turn ? 'W' : 'B') ||
							MainBoard.board[newx][newy]->name[3] != '*') {
							cout << "NOT VALID POSSITION\n\n";
						}
						else {
							Serviece->MakeMove(newx, newy, &MainBoard, Ch_p);
						}
					}
				}
				else if (op == 2) {
					break;
				}
				else {
					op = 3; continue;
				}
			}

			ValidPos.Clear();   // to remove all pointers 

			turn ^= 1;
			for (int i = 1; i < 9; i++) {
				for (int j = 1; j < 9; j++) {
					//if(MainBoard.board[i][j])   // check if game is finish of is running

				}
			}
		}
		cout << (turn ? "Black" : "White") << " is win !!\n\n";
		//Reset color
		cout << "\033[0m";
	}
};

