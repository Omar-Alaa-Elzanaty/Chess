#pragma once
#include "Board.h"
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
using namespace std;
class IPieceService
{
public:
	virtual bool  CanMove(Board* board, Piece* piece) = 0;
	virtual Board AllValidMove(Board* board, Piece* piece) = 0;
	virtual Board MakeMove(int x, int y, Board* board, Piece* piece) = 0;
};