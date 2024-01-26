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
class BoardServices
{
public:
    void DisplayBoard(Board *myBoard) {
        for (int myRow = 1; myRow <= 8; myRow++)
        {
            cout << myRow << " ";
            for (int myColumn = 1; myColumn <= 8; myColumn++)
            {

                cout << myBoard->board[myRow][myColumn]->name << " ";
            }
            cout << "\n";
        }
        cout << "  ";
        for (int i = 0; i < 8; i++) {
            cout << (char)('H' - i) << "    ";
        }
    }
};