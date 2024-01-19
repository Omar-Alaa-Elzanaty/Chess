#include <bits/stdc++.h>
#include "KingServices.h"

using namespace std;

class System
{

public:
	static void Run() {
		King king;
		auto WhitePlayerService = KingServices(king);

		WhitePlayerService.CheckMove(x, y);
	}

};

