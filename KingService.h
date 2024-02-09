#include<iostream>
#include"IPieceService.h"
using namespace std;

class KingService : public IPieceService {

    vector<Piece>KingCheck(Board * board, Piece * piece,int xx,int yy) {
        pair<int, int>king_pos = make_pair(xx, yy);
            vector<Piece>ret;
            char opsc = piece->name[0];
            opsc = (opsc == 'W' ? 'B' : 'W');
            string ops; ops.push_back(opsc);
            // rook , queen 
            for (int i = 0; i < 4; i++) {
                int x = king_pos.first + Rook().dRow[i];
                int y = king_pos.second + Rook().dColumn[i];
                while (x <= 8 and x and y <= 8 and y) {
                    string tmp = board->board[x][y]->name;
                    if (tmp[0] != ' ') { // not empty cell
                        if (tmp[0] == ops[0]) {
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
                        if (tmp[0] == ops[0]) {
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
            if (ops == "B") { // white king 
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
public:
	bool  CanMove(Board* board, Piece* piece) {
        for (int i = 0; i < 8; i++) {
            int x = piece->row + piece->dRow[i];
            int y = piece->column+ piece->dColumn[i];
            if (x > 8 || x < 1 || y < 1 || y>8)continue;
            int sz = KingCheck(board, piece, piece->row, piece->column).size();
            if (sz == 0)return 1;
        }
        return 0;
	}
    Board AllValidMove(Board* board, Piece* piece) {
        Board ret = *board;////////////////////////////////error
        for (int i = 0; i < 8; i++) {
            int x = piece->row + piece->dRow[i];
            int y = piece->column + piece->dColumn[i];
            if (x > 8 || x < 1 || y < 1 || y>8)continue;
            int sz = KingCheck(board, piece, piece->row, piece->column).size();
            if (sz != 0)continue;
            string &nm = ret.board[x][y]->name;
            if (nm[0] == ' ')nm[1] = '*';
            else nm[3] = '*';
        }
        return ret;
    }
    Board MakeMove(int x, int y, Board* board, Piece* piece) {///////////////error


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