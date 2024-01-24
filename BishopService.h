#pragma once
#include<vector>
#include"IPieceService.h"
#include"BishopService.h"
class BishopService :public IPieceService
{
	
    pair<int, int>king_pos;
    pair<int, int>KingPos(Board* board, Piece* piece) {
        int _xking, _yking;
        char col = piece->name[0];
        for (int i = 1; i <= 8; i++) {// find king position
            for (int j = 1; j <= 8; j++) {
                if (board->board[i][j]->name == (col + "KI ")) {
                    _xking = i;
                    _yking = j;
                    break;
                }
            }
        }
        return { _xking,_yking };
    }
    vector<Piece>KingCheck(Board* board, Piece* piece) {
        king_pos = KingPos(board, piece);
        vector<Piece>ret;
        char ops = piece->name[0];
        ops = (ops == 'W' ? 'B' : 'W');

        // rook , queen 
        for (int i = 0; i < 4; i++) {
            int x = king_pos.first + Rook().dRow[i];
            int y = king_pos.second + Rook().dColumn[i];
            while (x <= 8 and x and y <= 8 and y) {
                string tmp = board->board[x][y]->name;
                if (tmp[0] != ' ') { // not empty cell
                    if (tmp[0] == ops) {
                        if (tmp == ops + "QU " || tmp == ops + "RO ") {
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
            while (x <= 8 and x and y <= 8 and y) {
                string tmp = board->board[x][y]->name;
                if (tmp[0] != ' ') { // not empty cell
                    if (tmp[0] == ops) {
                        if (tmp == ops + "QU " || tmp == ops + "BI ") {
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
            if (board->board[x][y]->name[0] != ' ') {
                if (board->board[x][y]->name == ops + "KN ") {
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
            bool BishopInLine = 0;
            while (x <= 8 and x and y <= 8 and y) {
                string tmp = board->board[x][y]->name;
                if (tmp[0] != ' ') { // not empty cell
                    if (tmp[0] == ops) {
                        if (tmp == ops + "QU " || tmp == ops + "RO ") {
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
            while (x <= 8 and x and y <= 8 and y) {
                string tmp = board->board[x][y]->name;
                if (tmp[0] != ' ') { // not empty cell
                    if (tmp[0] == ops) {
                        if (tmp == ops + "QU " || tmp == ops + "BI ") {
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
        char ops = 'W' + 'B' - piece->name[0];
        for (int i = 0; i < 4; i++) {
            int x = piece->row + piece->dRow[i];
            int y = piece->column + piece->dColumn[i];
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
        king_check = KingCheck(board, piece);
        king_block = KingBlock(board, piece);
        if (king_check.size() > 0 and king_block.size() > 0)return false;

        if (king_check.size() > 1)return false;
        if (king_check.size()) {
            char ops = ('W' + 'B') - (piece->name[0]);
            Piece ch = king_check[0];
            if (GeneralBoard.board[ch.row][ch.column]->name[3] == '*')return true;
            if (ch.name == ops + "PA ") {
                return false;
            }
            else if (ch.name == ops + "BI ") {
                int i = 0,ok=0;
                for (; i < 4; i++) {
                    int x = king_pos.first + Bishop().dRow[i];
                    int y = king_pos.second + Bishop().dColumn[i];
                    while (x and y and x <= 8 and y <= 8) {
                        if (board->board[x][y] == &ch) {/////////////////////////////////////error
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
            else if (ch.name == ops + "KN ") {
                int i = 0, ok = 0;
                for (; i < 8; i++) {
                    int x = king_pos.first + Knight().dRow[i];
                    int y = king_pos.second + Knight().dColumn[i];
                    if (board->board[x][y] == &ch) {////////////////////////////////////////error
                        if (GeneralBoard.board[x][y]->name[3] == '*')return true;
                    }
                }
                return false;
            }
            else if (ch.name == ops + "QU ") {
                int i = 0, ok = 0;
                for (; i < 8; i++) {
                    int x = king_pos.first + Queen().dRow[i];
                    int y = king_pos.second + Queen().dColumn[i];
                    while (x and y and x <= 8 and y <= 8) {
                        if (board->board[x][y] == &ch) {/////////////////////////////////////error
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
            else if (ch.name == ops + "RO ") {
                int i = 0, ok = 0;
                for (; i < 4; i++) {
                    int x = king_pos.first + Rook().dRow[i];
                    int y = king_pos.second + Rook().dColumn[i];
                    while (x and y and x <= 8 and y <= 8) {
                        if (board->board[x][y] == &ch) {/////////////////////////////////////error
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
            if (ch.name == ops + "BI " || ch.name == ops + "QU ") { return true; }
            return false;
        }
        else return true;
    }
    Board AllValidMove(Board* board, Piece* piece) {
        //CanMove(board, piece);
        GetGeneralBoard(board, piece);
        return GeneralBoard;
    }
    Board MakeMove(int x, int y, Board* board, Piece* piece) {
        return GeneralBoard;
    }
};

