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
#include "RookServices.h"
using namespace std;
int main()
{
    Board* b = new Board;
    BoardServices bs;
    Board mb = KnightService().AllValidMove( b, b->board[1][2]);
    bs.DisplayBoard(&mb);
    cout << "\n";
   
    
}