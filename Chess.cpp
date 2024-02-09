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
#include "PawnServices.h"
#include "RookServices.h"
using namespace std;
int main()
{
	Board brd;
	BoardServices brds;
	brds.DisplayBoard(&brd); cout << '\n';
	Piece BI = *brd.board[8][3];
	BishopService().MakeMove(6, 5, &brd, &BI);
	brds.DisplayBoard(&brd); cout << '\n';
	//cout << BI.name;
	BI = *brd.board[6][5];
	brd.board[7][4]->name = " .  ";
	Board valid = BishopService().AllValidMove(&brd, &BI);
	brds.DisplayBoard(&valid); cout << '\n';
	//cout << BI.row << ' ' << BI.column << '\n';

}
