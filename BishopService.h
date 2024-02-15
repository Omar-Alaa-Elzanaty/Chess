#pragma once
#include<vector>
#include<string>
#include"IPieceService.h"
#include"BishopService.h"
class BishopService :public IPieceService
{

    pair<int, int>king_pos;
    pair<int, int>KingPos(Board* board, Piece* piece) {
        int _xking, _yking;
        char col = piece->name[0];
        string Target;
        Target.push_back(col); Target += "KI ";
        for (int i = 1; i <= 8; i++) {// find king position
            for (int j = 1; j <= 8; j++) {
                if (board->board[i][j]->name == Target) {
                    _xking = i;
                    _yking = j;
                    return { _xking,_yking };

                }
            }
        }
        return { -1,-1 };
    }
    vector<Piece>KingCheck(Board* board, Piece* piece) {
        king_pos = KingPos(board, piece);
        vector<Piece>ret;
        char ops = 'W' + 'B' - piece->name[0];
        //ops = (ops == 'W' ? 'B' : 'W');

        // rook , queen 
        for (int i = 0; i < 4; i++) {
            int x = king_pos.first + Rook().dRow[i];
            int y = king_pos.second + Rook().dColumn[i];
            string Target1, Target2;
            Target1.push_back(ops); Target1 += "QU ";
            Target2.push_back(ops); Target2 += "RO ";
            while (x <= 8 and x and y <= 8 and y) {
                string tmp = board->board[x][y]->name;
                if (tmp[0] != ' ') { // not empty cell
                    if (tmp[0] == ops) {
                        if (tmp == Target1 || tmp == Target2) {
                            ret.push_back(*board->board[x][y]);
                        }
                    }
                    break;
                }
                x += Rook().dRow[i];
                y += Rook().dColumn[i];
            }

        }
        // bishop , queen 
        for (int i = 0; i < 4; i++) {
            int x = king_pos.first + Bishop().dRow[i];
            int y = king_pos.second + Bishop().dColumn[i];
            string Target1, Target2;
            Target1.push_back(ops); Target1 += "QU ";
            Target2.push_back(ops); Target2 += "BI ";
            while (x <= 8 and x and y <= 8 and y) {
                string tmp = board->board[x][y]->name;
                if (tmp[0] != ' ') { // not empty cell
                    if (tmp[0] == ops) {
                        if (tmp == Target1 || tmp == Target2) {
                            ret.push_back(*board->board[x][y]);
                        }
                    }
                    break;
                }
                x += Bishop().dRow[i];
                y += Bishop().dColumn[i];
            }

        }

        //knight
        for (int i = 0; i < 8; i++) {
            int x = king_pos.first + Knight().dRow[i];
            int y = king_pos.second + Knight().dColumn[i];
            string Target1;
            Target1.push_back(ops); Target1 += "KN ";
            if (x <= 0 || y <= 0 || x > 8 || y > 8)continue;
            if (board->board[x][y]->name[0] != ' ') {
                if (board->board[x][y]->name == Target1) {
                    ret.push_back(*board->board[x][y]);
                }
                break;
            }
        }
        //pawn
        if (ops == 'B') { // white king 
            int x = king_pos.first - 1;
            int y = king_pos.second - 1;
            if (x <= 8 and x and y and y <= 8 and board->board[x][y]->name == "BPA ") {
                ret.push_back(*board->board[x][y]);
            }
            y += 2;
            if (x <= 8 and x and y and y <= 8 and board->board[x][y]->name == "BPA ") {
                ret.push_back(*board->board[x][y]);
            }
        }
        else { // Black king
            int x = king_pos.first + 1;
            int y = king_pos.second + 1;
            if (x <= 8 and x and y and y <= 8 and board->board[x][y]->name == "WPA ") {
                ret.push_back(*board->board[x][y]);
            }
            y -= 2;
            if (x <= 8 and x and y and y <= 8 and board->board[x][y]->name == "WPA ") {
                ret.push_back(*board->board[x][y]);
            }
        }

        return ret;
    }
    vector<Piece>KingBlock(Board* board, Piece* piece) {
        king_pos = KingPos(board, piece);
        vector<Piece>ret;
        char ops = piece->name[0];
        ops = (ops == 'W' ? 'B' : 'W');

        // rook , queen 
        for (int i = 0; i < 4; i++) {
            int x = king_pos.first + Rook().dRow[i];
            int y = king_pos.second + Rook().dColumn[i];
            string Target1, Target2;
            Target1.push_back(ops); Target1 += "QU ";
            Target2.push_back(ops); Target2 += "RO ";
            bool BishopInLine = 0;
            while (x <= 8 and x and y <= 8 and y) {
                string tmp = board->board[x][y]->name;
                if (tmp[0] != ' ') { // not empty cell
                    if (tmp[0] == ops) {
                        if (tmp == Target1 || tmp == Target2) {
                            if (BishopInLine)
                                ret.push_back(*board->board[x][y]);
                        }
                        break;
                    }
                    else if (tmp.substr(1) == "BI ")BishopInLine = 1;
                    else break;
                }
                x += Rook().dRow[i];
                y += Rook().dColumn[i];
            }

        }

        // bishop , queen 
        for (int i = 0; i < 4; i++) {
            int x = king_pos.first + Bishop().dRow[i];
            int y = king_pos.second + Bishop().dColumn[i];
            bool BishopInLine = 0;
            string Target1, Target2;
            Target1.push_back(ops); Target1 += "QU ";
            Target2.push_back(ops); Target2 += "BI ";
            while (x <= 8 and x and y <= 8 and y) {
                string tmp = board->board[x][y]->name;
                if (tmp[0] != ' ') { // not empty cell
                    if (tmp[0] == ops) {
                        if (tmp == Target1 || tmp == Target2) {
                            if (BishopInLine)
                                ret.push_back(*board->board[x][y]);
                        }
                        break;
                    }
                    else if (tmp.substr(1) == "BI ")BishopInLine = 1;
                    else break;
                }
                x += Bishop().dRow[i];
                y += Bishop().dColumn[i];
            }

        }

        return ret;
    }
    vector<Piece>king_check, king_block;
    Board GeneralBoard;
    void GetGeneralBoard(Board* board, Piece* piece) {
        GeneralBoard = board;
       /* cout << "\n\nInSide\n\n\n";
        BoardServices().DisplayBoard(&GeneralBoard); cout << "\n\n\n";*/
        //cout << piece->dRow.size() << '\n';
        //cout << "\nDone make copy \n";
        for (int i = 0; i < 4; i++) {
            int x = piece->row +piece->dRow[i];
        //cout << "\n Test \n";
            int y = piece->column + piece->dColumn[i];
        char ops = 'W' + 'B' - piece->name[0];
            while (x <= 8 and x and y and y <= 8) {
                if (GeneralBoard.board[x][y]->name != " .  ") {
                    if (GeneralBoard.board[x][y]->name[0] == ops) {
                        GeneralBoard.board[x][y]->name[3] = '*';
                    }
                    break;
                }
                else  GeneralBoard.board[x][y]->name[1] = '*';
                x += piece->dRow[i];
                y += piece->dColumn[i];
            }
        }
    }
public:
    //virtual bool  CanMove(Board* board, Piece* piece) = 0;
    //virtual Board AllValidMove(Board* board, Piece* piece) = 0;
    //virtual Board MakeMove(int x, int y, Board* board, Piece* piece) = 0;


    bool  CanMove(Board* board, Piece* piece) {
        GetGeneralBoard(board, piece);
        //cout << "\nDone GetGeneralBoard\n";
        king_check = KingCheck(board, piece);
        king_block = KingBlock(board, piece);
        if (king_check.size() > 0 and king_block.size() > 0)return false;

        if (king_check.size() > 1)return false;
        if (king_check.size()) {
            char ops = ('W' + 'B') - (piece->name[0]);
            Piece ch = king_check[0];
            string Mrg; Mrg.push_back(ops); Mrg += "PA ";
            if (GeneralBoard.board[ch.row][ch.column]->name[3] == '*')return true;
            if (ch.name == Mrg) {
                return false;
            }
            Mrg = ""; Mrg.push_back(ops); Mrg += "BI ";
            if (ch.name == Mrg) {
                int i = 0, ok = 0;
                for (; i < 4; i++) {
                    int x = king_pos.first + Bishop().dRow[i];
                    int y = king_pos.second + Bishop().dColumn[i];
                    while (x and y and x <= 8 and y <= 8) {
                        //if (board->board[x][y] == &ch) {/////////////////////////////////////error
                        if (x == ch.row and y==ch.column) {
                            ok = 1; break;
                        }
                        x += Bishop().dRow[i];
                        y += Bishop().dColumn[i];
                    }
                    if (ok)break;
                }
                int x = king_pos.first + Bishop().dRow[i];
                int y = king_pos.second + Bishop().dColumn[i];
                while (x <= 8 and x and y <= 8 and y) {
                    if (GeneralBoard.board[x][y]->name[1] == '*' ||
                        GeneralBoard.board[x][y]->name[3] == '*')return true;
                }
                return false;
            }
            Mrg = ""; Mrg.push_back(ops); Mrg += "KN ";
            if (ch.name == Mrg) {
                int i = 0, ok = 0;
                for (; i < 8; i++) {
                    int x = king_pos.first + Knight().dRow[i];
                    int y = king_pos.second + Knight().dColumn[i];
                    //if (board->board[x][y] == &ch) {////////////////////////////////////////error
                    if (x == ch.row and y == ch.column) {
                        if (GeneralBoard.board[x][y]->name[3] == '*')return true;
                    }
                }
                return false;
            }
            Mrg = ""; Mrg.push_back(ops); Mrg += "QU ";
            if (ch.name == Mrg) {
                int i = 0, ok = 0;
                for (; i < 8; i++) {
                    int x = king_pos.first + Queen().dRow[i];
                    int y = king_pos.second + Queen().dColumn[i];
                    while (x and y and x <= 8 and y <= 8) {
                        //if (board->board[x][y] == &ch) {/////////////////////////////////////error
                        if (x == ch.row and y == ch.column) {
                            ok = 1; break;
                        }
                        x += Queen().dRow[i];
                        y += Queen().dColumn[i];
                    }
                    if (ok)break;
                }
                int x = king_pos.first + Queen().dRow[i];
                int y = king_pos.second + Queen().dColumn[i];
                while (x <= 8 and x and y <= 8 and y) {
                    if (GeneralBoard.board[x][y]->name[1] == '*' ||
                        GeneralBoard.board[x][y]->name[3] == '*')return true;
                }
                return false;
            }
            Mrg = ""; Mrg.push_back(ops); Mrg += "RO ";
            if (ch.name == Mrg) {
                int i = 0, ok = 0;
                for (; i < 4; i++) {
                    int x = king_pos.first + Rook().dRow[i];
                    int y = king_pos.second + Rook().dColumn[i];
                    while (x and y and x <= 8 and y <= 8) {
                        //if (board->board[x][y] == &ch) {/////////////////////////////////////error
                        if (x == ch.row and y == ch.column) {
                            ok = 1; break;
                        }
                        x += Rook().dRow[i];
                        y += Rook().dColumn[i];
                    }
                    if (ok)break;
                }
                int x = king_pos.first + Rook().dRow[i];
                int y = king_pos.second + Rook().dColumn[i];
                while (x <= 8 and x and y <= 8 and y) {
                    if (GeneralBoard.board[x][y]->name[1] == '*' ||
                        GeneralBoard.board[x][y]->name[3] == '*')return true;
                }
                return false;
            }
        }

        else if (king_block.size()) {
            char ops = ('W' + 'B') - (piece->name[0]);
            Piece ch = king_block[0];
            string Mrg; Mrg.push_back(ops); Mrg += "BI ";
            string Mrg2; Mrg2.push_back(ops); Mrg2 += "QU ";
            if (ch.name == Mrg || ch.name == Mrg2) { return true; }
            return false;
        }
        else return true;
    }
    Board AllValidMove(Board* board, Piece* piece) {
        if (!CanMove(board, piece))return *board;
        //cout << "\nDone CanMove\n";
        /*cout << 
            "KKKKKKKKKKKKKKKKKKKing Cheeeeeeeeeeeeeeeeeck!!!! " 
            << king_check.size() << "\n\n";
        cout << king_pos.first << ' ' << king_pos.second << '\n';*/


        if (king_block.size() == 0 and king_check.size() == 0)
            return GeneralBoard;

        Board ret;
        ret = board;
        
        if (king_check.size()) {
            Piece ch = king_check[0];
            string Target; Target.push_back('W' + 'B' - piece->name[0]);
            Target += "PA ";
            string Target2; Target2 += ('W' + 'B' - piece->name[0]);

            Target2 += "KN ";
            if (ch.name == Target || ch.name == Target2) {
                for (int i = 1; i <= 8; i++)for (int j = 1; j <= 8; j++) {
                    //if (ret.board[i][j] == &ch) {/////////////error
                        if (i == ch.row and j == ch.column) {
                        ret.board[i][j]->name[3] = '*';
                        return ret;
                    }
                }
            }

            Target = ""; Target.push_back('W' + 'B' - piece->name[0]);
            Target += "BI ";
            Target2 = ('W' + 'B' - piece->name[0]);
            Target2 += "QU ";
            if (ch.name == Target || ch.name == Target2) {
                int i = 0, ok = 0;
                for (; i < 4; i++) {
                    int x = king_pos.first + Bishop().dRow[i];
                    int y = king_pos.second + Bishop().dColumn[i];
                    while (x and x <= 8 and y and y <= 8) {
                        //if (&ch == board->board[x][y]) {///////////////error
                        if (x == ch.row and y == ch.column) {
                            ok = 1; break;
                        }
                        x += Bishop().dRow[i];
                        y += Bishop().dColumn[i];
                    }
                    if (ok)break;
                }
                int x = king_pos.first + Bishop().dRow[i];
                int y = king_pos.second + Bishop().dColumn[i];
                while (x and x <= 8 and y and y <= 8) {
                    if (GeneralBoard.board[x][y]->name[0] != ' ') {
                        if (GeneralBoard.board[x][y]->name[3] == '*')
                            ret.board[x][y]->name[3] = '*';
                    }
                    else {
                        if (GeneralBoard.board[x][y]->name[1] == '*')
                            ret.board[x][y]->name[1] = '*';
                    }
                    x += Bishop().dRow[i];
                    y += Bishop().dColumn[i];
                }
                return ret;
            }

            Target = ""; Target.push_back('W' + 'B' - piece->name[0]);
            Target += "RO ";
            Target2 = ('W' + 'B' - piece->name[0]);
            Target2 += "QU ";

            if (ch.name == Target || ch.name == Target2) {
                int i = 0, ok = 0;
                for (; i < 4; i++) {
                    int x = king_pos.first + Rook().dRow[i];
                    int y = king_pos.second + Rook().dColumn[i];
                    while (x and x <= 8 and y and y <= 8) {
                        //if (&ch == board->board[x][y]) {///////////////////////////error
                        if (x == ch.row and y == ch.column) {
                            ok = 1; break;
                        }
                        x += Rook().dRow[i];
                        y += Rook().dColumn[i];
                    }
                    if (ok)break;
                }
                int x = king_pos.first + Rook().dRow[i];
                int y = king_pos.second + Rook().dColumn[i];
                while (x and x <= 8 and y and y <= 8) {
                    if (GeneralBoard.board[x][y]->name[0] != ' ') {
                        if (GeneralBoard.board[x][y]->name[3] == '*')
                            ret.board[x][y]->name[3] = '*';
                    }
                    else {
                        if (GeneralBoard.board[x][y]->name[1] == '*')
                            ret.board[x][y]->name[1] = '*';
                    }
                    x += Rook().dRow[i];
                    y += Rook().dColumn[i];
                }
                return ret;
            }
        }

        if (king_block.size()) {
            Piece bl = king_block[0];
            int i = 0, ok = 0;
            for (; i < 4; i++) {
                int x = king_pos.first + Bishop().dRow[i];
                int y = king_pos.second + Bishop().dColumn[i];
                while (x and x <= 8 and y and y <= 8) {
                    //if (&bl == board->board[x][y]) {////////////////////error
                    if (x == bl.row and y == bl.column) {
                        ok = 1; break;
                    }
                    x += Bishop().dRow[i];
                    y += Bishop().dColumn[i];
                }
                if (ok)break;
            }
            int x = king_pos.first + Bishop().dRow[i];
            int y = king_pos.second + Bishop().dColumn[i];
            while (x and x <= 8 and y and y <= 8) {
                if (GeneralBoard.board[x][y]->name[0] != ' ') {
                    if (GeneralBoard.board[x][y]->name[1] != 'B')
                        ret.board[x][y]->name[3] = '*';
                }
                else {
                    ret.board[x][y]->name[1] = '*';
                }
                x += Bishop().dRow[i];
                y += Bishop().dColumn[i];
            }
            return ret;
        }

        return ret;
    }
    Board MakeMove(int x, int y, Board* board, Piece* piece) {
        int xp = piece->row;
        int yp = piece->column;
        board->board[x][y]->Clone(piece);
        board->board[x][y]->row = x;
        board->board[x][y]->column = y;
        Piece* rem = board->board[xp][yp];
        board->board[xp][yp] = new Piece();
        board->board[xp][yp]->row = xp;
        board->board[xp][yp]->column = yp;
        delete rem;
        return *board;
    }
};
