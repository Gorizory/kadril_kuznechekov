#ifndef KADRIL_KUZNECHEKOV_HEADER_H
#define KADRIL_KUZNECHEKOV_HEADER_H

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

enum checker {
    EMPTY = 0,
    WHITE = 1,
    BLACK = 2,
};

class Cell {
private:
    checker ch;

public:
    explicit Cell(checker);

    void setChecker(checker);

    checker getChecker();
};

class Board {
private:
    vector<Cell> board;

public:
    explicit Board(vector<checker>);

    ~Board();

    vector<Cell> getBoard();

    void printBoard();

    bool checkCellEmpty(unsigned);

    void setCell(unsigned, checker);
};

Board openVertex(unsigned, unsigned, Board);

void formVertex(Board, function<void(unsigned, unsigned, Board)>);

#endif //KADRIL_KUZNECHEKOV_HEADER_H
