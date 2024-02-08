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
#include "System.h"
#include"BoardServices.h"
#include"BishopService.h"
<<<<<<< HEAD

=======
#include"KnightService.h"
#include"Knight.h"
#include"IKnightService.h"
#include "PawnServices.h"
#include "RookServices.h"
>>>>>>> e4be1512806cce3c57b6e58de26464d13914ac62
using namespace std;
int main()
{

<<<<<<< HEAD
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
=======
}
>>>>>>> e4be1512806cce3c57b6e58de26464d13914ac62
