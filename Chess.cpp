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
#include"KnightService.h"
#include"Knight.h"
#include"IKnightService.h"
using namespace std;
int main()
{
<<<<<<< HEAD
	Board* b = new Board;
	Piece* p = new Piece;
	p = b->board[8][2];
	KnightService x;
	Board xx = x.AllValidMove(b,p);
	BoardServices().DisplayBoard(&xx);
	cout << endl;
	cout << x.CanMove(b,p) << endl;
	Board xu = x.MakeMove(6,6,b,p);
	BoardServices().DisplayBoard(&xu);
}
=======
    Board* b = new Board;
    Piece* p = new Piece;
    p = b->board[8][2];
    KnightService x;
    Board xx = x.AllValidMove(b, p);
    BoardServices().DisplayBoard(&xx);
}
>>>>>>> 04c1bf40cf37b932aecb39a134a84ffe87db4f3c
