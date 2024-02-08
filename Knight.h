#pragma once
#include "Piece.h"
<<<<<<< HEAD
#include <iostream>
class Knight :public Piece
{
public:
    Knight() {
=======
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
class Knight :public Piece
{
public:
	Knight() {
>>>>>>> e4be1512806cce3c57b6e58de26464d13914ac62
        this->dRow = new int[9];
        this->dColumn = new int[9];
        dRow[0] = 1; dColumn[0] = 2;
        dRow[1] = -1; dColumn[1] = -2;
        dRow[2] = -2; dColumn[2] = -1;
        dRow[3] = 1; dColumn[3] = -2;
        dRow[4] = 2; dColumn[4] = -1;
        dRow[5] = -2; dColumn[5] = 1;
        dRow[6] = 2; dColumn[6] = 1;
        dRow[7] = -1; dColumn[7] = 2;
<<<<<<< HEAD
    }
};  
=======
	}
};
>>>>>>> e4be1512806cce3c57b6e58de26464d13914ac62
