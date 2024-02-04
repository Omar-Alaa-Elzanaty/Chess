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
#include"KnightService.h"
#include"Knight.h"
#include"IKnightService.h"
#include "RookServices.h"
using namespace std;
int main()
{
	Board board;
	BoardServices BS;
	BS.DisplayBoard(&board); cout << '\n';
	KnightService BIS;
	Piece* BIP = board.board[8][2];
	Board Allv = BIS.AllValidMove(&board, BIP);
	BS.DisplayBoard(&Allv); cout << '\n';
	BIS.MakeMove(6, 3, &board, BIP);
	//BS.DisplayBoard(&Allv); cout << '\n';

}
