#pragma once
#include "Piece.h"
class King :public Piece{
public:

    King() {
        this->dRow.resize(9);
        this->dColumn.resize(9);
        dRow[0] = 0; dColumn[0] = 1;
        dRow[1] = 0; dColumn[1] = -1;
        dRow[2] = 1; dColumn[2] = 0;
        dRow[3] = 1; dColumn[3] = -1;
        dRow[4] = 1; dColumn[4] = 1;
        dRow[5] = -1; dColumn[5] = 0;
        dRow[6] = -1; dColumn[6] = 1;
        dRow[7] = -1; dColumn[7] = -1;
    }
};

