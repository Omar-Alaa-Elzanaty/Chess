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
    Board* b = new Board;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            cout << b->board[i][j] << ' ';
        cout << endl;
    }
}