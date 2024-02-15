#pragma once
#include "Piece.h"
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
class Bishop :public Piece
{
public:
	Bishop() {
		this->dRow.resize(4);
		this->dColumn.resize(4);
		dRow[0] = 1; dRow[1] = 1;
		dRow[2] = -1; dRow[3] = -1;

		dColumn[0] = 1; dColumn[1] = -1;
		dColumn[2] = 1; dColumn[3] = -1;
	}
};